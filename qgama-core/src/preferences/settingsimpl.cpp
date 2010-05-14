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

#include "settingsimpl.h"

using namespace QGamaCore;


// inicialization of the private instance pointer to null.
SettingsImpl* SettingsImpl::self = 0;

// inicialization of the private counter of references
int SettingsImpl::pointersCount = 0;


/* ===============================================================================================================*/
/** Implicit constructor.
  *
  * Initializes QSettings object, loads everything stored there into the inner map and sets default path to the plugins directory.
  */
SettingsImpl::SettingsImpl() :
    applicationSettings("Jiri_Novak","QGamaCore")
{
    // read all the settings into the inner map
    loadAll();

    // setting plugin directory to the standard application bin/plugins folder if it's empty
    if (this->get("plugins/directory").toString().isEmpty()) {
        this->set("plugins/directory",QString(qApp->applicationDirPath()+"/plugins"));
        this->saveValue("plugins/directory");
    }
}


/* ===============================================================================================================*/
/** Method returning a pointer to QGamaCore::PluginManagerImpl object.
  *
  * On the first call the instance is created, sequentially pointers to this instance are returned.
  * Also a counter of pointers is hold.
  */
SettingsImpl* SettingsImpl::instance() {
    if (self == 0) {
        self = new SettingsImpl();
    }
    pointersCount++;

    return self;
}


/* ===============================================================================================================*/
/** Actions that have to be done on the release.
  *
  * Saves everything stored in the inner map into QSettings. Descreases counter of pointers by one
  * and if it dealed the last reference, deletes dynamicaly created structures, that's object
  * on the address by private instance pointer, set's the pointer to null.
  */
void SettingsImpl::release()
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
  * Saves everything stored in the inner map into QSettings.
  */
SettingsImpl::~SettingsImpl()
{
    // save all the settings from the inner map
    saveAll();

    qDebug() << "SettingsImpl - Destruktor";
}


/* ===============================================================================================================*/
/** Saves value referenced with the specified key from the inner map into the persistent storage (QSettings).
  *
  * @param[in] key  The key for the value desired to save.
  */
void SettingsImpl::saveValue(const QString &key)
{
    applicationSettings.setValue(key,get(key));
}


/* ===============================================================================================================*/
/** Loads value referenced with the specified key from the persistent storage (QSettings) into the inner map.
  *
  * @param[in] key  The key for the value desired to load.
  */
void SettingsImpl::loadValue(const QString &key)
{
    set(key,applicationSettings.value(key));
}


/* ===============================================================================================================*/
/** Saves all the values from the inner map into the persistent storage (QSettings).
  *
  */
void SettingsImpl::saveAll()
{
    // clear everything
    applicationSettings.clear();

    // commit all values at once
    for (QMap<QString,QVariant>::iterator i=settings.begin(); i!=settings.end(); ++i) {
        // skip those marked as temporary
        if (!i.key().startsWith("temporary"))
            saveValue(i.key());
    }
}


/* ===============================================================================================================*/
/** Loads all the values from the persistent storage (QSettings) into the inner map.
  *
  */
void SettingsImpl::loadAll()
{
    QStringList keys = applicationSettings.allKeys();
    for (QStringList::iterator i=keys.begin(); i!=keys.end(); ++i) {
        loadValue(*i);
    }
}
