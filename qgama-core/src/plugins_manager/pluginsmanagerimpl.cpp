/****************************************************************************
**
**    QGamaCore GUI C++ Library (QGamaCoreLib)
**    Copyright (C) 2010  Jiri Novak <jiri.novak.2@fsv.cvut.cz>
**
**    This file is part of the QGamaCore GUI C++ Library.
**
**    This library is free software; you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation; either version 3 of the License, or
**    (at your option) any later version.
**
**    This library is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this library; if not, write to the Free Software
**    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
****************************************************************************/

#include <QtGui>

#include "pluginsmanagerimpl.h"
#include "pluginsmanagerdialog.h"
#include "plugininterface.h"
#include "../utils/applicationcomponentproviderimpl.h"
#include "../main_window/mainwindow.h"
#include "../factory.h"

using namespace QGamaCore;


// Inicialization of the private instance pointer to null.
PluginsManagerImpl* PluginsManagerImpl::self = 0;

// inicialization of the private counter of pointers
int PluginsManagerImpl::pointersCount = 0;

enum { Enabled, NotEnabled };


/* ===============================================================================================================*/
/** Implicit constructor.
  *
  * Set's the plugin directory according to the application settings, store the filenames found in that directory.
  */
PluginsManagerImpl::PluginsManagerImpl() :
    settings(Factory::getSettings()),
    acp(Factory::getApplicationComponentProvider())
{
    updateDirAndFiles();
}


/* ===============================================================================================================*/
/**
  *
  */
void PluginsManagerImpl::updateDirAndFiles()
{
    // get the directory from application settings
    pluginsDir = QDir(settings->get("plugins/directory").toString());

    // getting file names from the plugin directory
    fileNames = pluginsDir.entryList(QDir::Files);
}


/* ===============================================================================================================*/
/** Method returning a pointer to QGamaCore::PluginManagerImpl object.
  *
  * On the first call the instance is created, sequentially pointers to this instance are returned.
  * Also a counter of pointers is hold.
  */
PluginsManagerImpl* PluginsManagerImpl::instance() {
    if (self == 0)
        self = new PluginsManagerImpl();

    pointersCount++;

    return self;
}


/* ===============================================================================================================*/
/** Actions that have to be done on the release.
  *
  * Descreases counter of pointers by one and if it dealed the last reference, deletes dynamicaly
  * created structures, that's object on the address by private instance pointer, set's the
  * pointer to null.
  */
void PluginsManagerImpl::release()
{
    pointersCount--;

    if (pointersCount == 0) {
      delete self;
      self = 0;
  }
}


/* ===============================================================================================================*/
/** Class destructor.
  *
  */
PluginsManagerImpl::~PluginsManagerImpl()
{
    qDebug() << "PluginsManagerImpl - Destruktor";

    // unload plugins
    unloadPlugins();

    qDebug() << "PluginsManagerImpl - Destruktor - plugins unloaded";

    Factory::releaseSettings(settings);
    Factory::releaseApplicationComponentProvider(acp);
}


/* ===============================================================================================================*/
/**
  *
  * \param[in]  name    The name of the plugin we want to load.
  */
void PluginsManagerImpl::loadPlugin(const QString &name)
{
    // if requested plugin is available in the pluginDir and wasn't already loaded
    if (fileNames.contains(name) && plugins.value(name)==0) {
        // load requested plugin
        QPluginLoader *loader = new QPluginLoader(pluginsDir.absoluteFilePath(name));
        PluginInterface *plugin = qobject_cast<PluginInterface*> (loader->instance());
        qDebug() << "PluginsManagerImpl::loadPlugin(" << name << ")";

        // if the load and cast were successful
        if (plugin) {
            qDebug() << "successfull";

            // we will add it to the map of loaded plugins
            plugins.insert(name,loader);
            plugin->init(acp);

            // add entry to the PluginManagerDialog
            PluginsManagerDialog *pmd = acp->getPluginsManagerDialog();
            if (settings->get("plugins/enabledPlugins").toStringList().contains(name))
                pmd->addLoadedPlugin(name,Enabled,plugin);
            else
                pmd->addLoadedPlugin(name,NotEnabled,plugin);

            // if the plugin was supposed to be enabled we will initialize it
            if (settings->get("plugins/enabledPlugins").toStringList().contains(name))
                populateMenus(plugin);
        }
        // otherwise delete allocated elements
        else {
            qDebug() << "unsuccessfull";
            delete loader;
            plugins.remove(name);
        }
   }
}


/* ===============================================================================================================*/
/**
  *
  * \param[in]  name    The name of the plugin we want to unload.
  */
void PluginsManagerImpl::unloadPlugin(const QString &name)
{ 
    // if requested plugin is loaded
    PluginInterface *plugin = getPlugin(name);
    QStringList enabledPlugins = settings->get("plugins/enabledPlugins").toStringList();

    if (plugin!=0) {
        // disable plugin
        if (enabledPlugins.contains(plugin->name()))
            disablePlugin(name);

        // unload the plugin
        plugins.value(name)->unload();

        // delete correspondent pluginLoader
        delete plugins.value(name);
        plugins.remove(name);
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void PluginsManagerImpl::loadPlugins()
{
    for (QStringList::iterator i=fileNames.begin(); i!=fileNames.end(); ++i) {
        loadPlugin(*i);
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void PluginsManagerImpl::unloadPlugins()
{
    for (QStringList::iterator i=fileNames.begin(); i!=fileNames.end(); ++i) {
        unloadPlugin(*i);
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void PluginsManagerImpl::populateMenus(PluginInterface *plugin)
{
    qDebug() << "PluginsManagerImpl::populateMenus() START";

    if (!plugin->items().isEmpty()) {
        // finding the correspondent menu
        MainWindow *mw = acp->getMainWindow();
        QMenu *menu = mw->findChild<QMenu*>("menu_Tools");

        QStringList items = plugin->items();
        for (QStringList::iterator i=items.begin(); i!=items.end(); ++i) {
            QStringList item = (*i).split("|");
            QString actionName = item.value(0);
            QString groupName = item.value(1);
            int priority = item.value(2).toInt();
            QString slot = item.value(3);
            QString shortcutKeys = item.value(4);

            menu->addSeparator();
            QAction *action = new QAction(" "+actionName,menu);
            action->setIcon(plugin->icon());
            action->setIconVisibleInMenu(true);
            action->setShortcut(QKeySequence::fromString(shortcutKeys));
            action->setData(groupName+"|"+priority);
            menu->addAction(action);

            QObject::connect(action,SIGNAL(triggered()),plugin,"1"+slot.toAscii());
        }
        mw->updateToolsMenu();
    }

    qDebug() << "PluginsManagerImpl::populateMenus() STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void PluginsManagerImpl::unPopulateMenus(PluginInterface *plugin)
{
    if (!plugin->items().isEmpty()) {
        // finding the correspondent menu
        MainWindow *mw = acp->getMainWindow();
        QMenu *menu = mw->findChild<QMenu*>("menu_Tools");

        QStringList items = plugin->items();
        for (QStringList::iterator i=items.begin(); i!=items.end(); ++i) {
            QStringList item = (*i).split("|");
            QString actionName = item.value(0);
            QString groupName = item.value(1);
            int priority = item.value(2).toInt();
            QString slot = item.value(3);

            QList<QAction*> actions = menu->actions();
            QAction *action = 0;
            for (int i=0; i<actions.size(); i++) {
                if (actions[i]->text() == " "+actionName && actions[i]->data().toString() == groupName+"|"+priority) {
                   action = actions[i];
                   QObject::disconnect(action,SIGNAL(triggered()),plugin,"1"+slot.toAscii());
                   menu->removeAction(action);
                }
            }
        }

        mw->updateToolsMenu();
    }

}


/* ===============================================================================================================*/
/**
  *
  */
void PluginsManagerImpl::enablePlugin(const QString &name)
{
    PluginInterface *plugin = getPlugin(name);
    Q_ASSERT(plugin!=0 && "plugin pointer is 0!");

    populateMenus(plugin);
}


/* ===============================================================================================================*/
/**
  *
  */
void PluginsManagerImpl::disablePlugin(const QString &name)
{
    PluginInterface *plugin = getPlugin(name);
    Q_ASSERT(plugin!=0 && "plugin pointer is 0!");

    unPopulateMenus(plugin);
}


/* ===============================================================================================================*/
/**
  *
  */
void PluginsManagerImpl::enablePlugins()
{
    for (QStringList::iterator i=fileNames.begin(); i!=fileNames.end(); ++i) {
        enablePlugin(*i);
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void PluginsManagerImpl::disablePlugins()
{
    for (QStringList::iterator i=fileNames.begin(); i!=fileNames.end(); ++i) {
        disablePlugin(*i);
    }
}


/* ===============================================================================================================*/
/** Returns pointer to the plugin with the specified name if exists or null if does not.
  *
  * @param[in] key  Name of the plugin we want to access.
  * @return         Pointer to the plugin with the specified name if exists or null if does not.
  */
PluginInterface* PluginsManagerImpl::getPlugin(const QString &key)
{
    if (plugins.contains(key))
        return qobject_cast<PluginInterface*> (plugins.value(key)->instance());
    else
        return 0;
}
