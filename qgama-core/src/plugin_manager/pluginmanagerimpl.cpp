/*
    QGamaCore GUI C++ Library (QGamaCoreLib)
    Copyright (C) 2010  Jiri Novak <jiri.novak.2@fsv.cvut.cz>

    This file is part of the QGamaCore GUI C++ Library.

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <QPluginLoader>
#include <QStringListIterator>
#include <QObject>
#include <QDir>
#include <iostream>

#include "pluginmanagerimpl.h"
#include "pluginmanagerdialog.h"
#include "plugininterface.h"
#include "../utils/utils.h"
#include "../preferences/qgamasettingsimpl.h"
#include "../main_window/mainwindow.h"
#include "../preferences/qgamasettings.h"

using namespace QGamaCore;


// Inicialization of the private instance pointer to null.
PluginManagerImpl* PluginManagerImpl::self = 0;


/** Implicit constructor.
  *
  * Set's the plugin directory according to the application settings, store the filenames found in that directory.
  */
PluginManagerImpl::PluginManagerImpl() : settings(QGamaSettingsImpl::instance())
{
    // get the directory from application settings
    pluginsDir = QDir(settings.get("plugins/directory").toString());

    // getting file names from the plugin directory
    fileNames = pluginsDir.entryList(QDir::Files);
}


/**
  *
  * \param[in]  name    The name of the plugin we want to load.
  */
void PluginManagerImpl::loadPlugin(const QString &name)
{
    // if requested plugin is available in the pluginDir and wasn't already loaded
    if (fileNames.contains(name) && plugins.value(name)==0) {
        // load requested plugin
        QPluginLoader *loader = new QPluginLoader(pluginsDir.absoluteFilePath(name));
        PluginInterface *plugin = qobject_cast<PluginInterface*> (loader->instance());

        // if the load and cast were successful
        if (plugin) {
            // we will add it to the map of loaded plugins
            plugins.insert(name,loader);

            // add entry to the PluginManagerDialog
            PluginManagerDialog *pmd = dynamic_cast<PluginManagerDialog*> (Utils::findTopLevelWidget("PluginManagerDialog"));
            if (settings.get("plugins/enabledPlugins").toStringList().contains(name))
                pmd->addLoadedPlugin(name,Enabled,plugin);
            else
                pmd->addLoadedPlugin(name,NotEnabled,plugin);

            // if the plugin was supposed to be enabled we will initialize it
            if (settings.get("plugins/enabledPlugins").toStringList().contains(name))
                populateMenus(plugin);
        }
        // otherwise delete allocated elements
        else {
            delete loader;
            plugins.remove(name);
        }
   }
}


/**
  *
  * \param[in]  name    The name of the plugin we want to unload.
  */
void PluginManagerImpl::unloadPlugin(const QString &name)
{
    // if requested plugin is loaded
    if (plugins.value(name)!=0) {
        // disable plugin
        disablePlugin(name);

        // unload the plugin
        plugins.value(name)->unload();

        // delete correspondent pluginLoader
        delete plugins.value(name);
        plugins.remove(name);
    }
}


/**
  *
  */
void PluginManagerImpl::loadPlugins()
{
    for (QStringList::iterator i=fileNames.begin(); i!=fileNames.end(); ++i) {
        loadPlugin(*i);
    }
}


/**
  *
  */
void PluginManagerImpl::unloadPlugins()
{
    for (QStringList::iterator i=fileNames.begin(); i!=fileNames.end(); ++i) {
        unloadPlugin(*i);
    }
}


/**
  *
  */
void PluginManagerImpl::populateMenus(PluginInterface *plugin)
{
    if (!plugin->items().isEmpty()) {
        QStringList items = plugin->items();

        for (QStringList::iterator i=items.begin(); i!=items.end(); ++i) {
            QStringList item = (*i).split("|");
            QString menuName = item.value(0);
            QString actionName = item.value(1);
            QString groupName = item.value(2);
            int priority = item.value(3).toInt();
            QString receiver = item.value(4);
            QString shortcutKeys = item.value(5);

            // finding the correspondent menu
            MainWindow *mw = dynamic_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));
            QMenu *menu = mw->findChild<QMenu*>("menu_" + menuName);

            menu->addSeparator();
            QAction *action = new QAction(" "+actionName,menu);
            action->setIcon(plugin->icon());
            action->setIconVisibleInMenu(true);
            action->setShortcut(QKeySequence::fromString(shortcutKeys));
            action->setData(groupName+"|"+priority);
            menu->addAction(action);

            QStringList slot = receiver.split("->");
            if (slot.value(0) == "this")
                QObject::connect(action,SIGNAL(triggered()),plugin,"1"+slot.value(1).toAscii());
            else {
                QObject *object = dynamic_cast<QObject*> (Utils::findTopLevelWidget(slot.value(0)));
                QObject::connect(action,SIGNAL(triggered()),object,"1"+slot.value(1).toAscii());
            }
        }
        /*
        // getting the name of the menu we want to add and of the action before which we want to put it
        QString menuName = menuSpecification.at(0);
        QString actionBeforeName = menuSpecification.at(1);

        // finding the correspondent action
        MainWindow *mw = dynamic_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

        QListIterator<QAction*> ii(mw->menuBar()->actions());
        while (ii.hasNext()) {
            QString ss = ii.next()->text();
            if (ss.remove(ss.indexOf("&",0),1) == actionBeforeName)
                break;
        }

        // creating new menu entry and putting it to the desired position
        QMenu *menu = mw->menuBar()->addMenu(menuName);
        mw->menuBar()->insertMenu(ii.next(),menu);

        // adding individual menu items
        QStringListIterator jj(plugin->menuItems());
        while (jj.hasNext()) {
            QString name = jj.next();
            QAction *action = new QAction(name,menu);
            menu->addAction(action);

            //QObject::connect(action,);
        }
        */
    }
}


/**
  *
  */
void PluginManagerImpl::unPopulateMenus(PluginInterface *plugin)
{
    /*
    if (!plugin->menuSpecification().isEmpty() && !plugin->menuItems().isEmpty()) {
        QStringList menuSpecification = plugin->menuSpecification();

        // getting the name of the menu we want to add and of the action before which we want to put it
        QString menuName = menuSpecification.at(0);
        QString actionBeforeName = menuSpecification.at(1);

        // finding the correspondent action
        MainWindow *mw = dynamic_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

        QStringList items = plugin->menuItems();
        QList<QAction*> actions = mw->actions();
        for (QList<QAction*>::iterator i=actions.begin(); i!=actions.end(); ++i) {
            std::cout << (*i)->text().toStdString() << std::endl;
            //if (items.contains((*i)->text())) {
            //    mw->removeAction(*i);
            //}
        }

        mw->update();
        //mw->menuBar()->removeAction(menuName);
    }
    */
}


/**
  *
  */
void PluginManagerImpl::enablePlugin(const QString &name)
{

}


/**
  *
  */
void PluginManagerImpl::disablePlugin(const QString &name)
{

}


/**
  *
  */
void PluginManagerImpl::enablePlugins()
{

}


/**
  *
  */
void PluginManagerImpl::disablePlugins()
{

}


/** Returns pointer to the plugin with the specified name if exists or null if does not.
  *
  * @param[in] key  Name of the plugin we want to access.
  * @return         Pointer to the plugin with the specified name if exists or null if does not.
  */
PluginInterface* PluginManagerImpl::plugin(const QString &key)
{
    if (plugins.contains(key))
        return qobject_cast<PluginInterface*> (plugins.value(key)->instance());
    else
        return 0;
}
