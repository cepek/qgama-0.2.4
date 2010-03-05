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

#ifndef PLUGINSMANAGERIMPL_H
#define PLUGINSMANAGERIMPL_H

#include <QMap>
#include <QDir>
#include <QStringList>
#include <QPluginLoader>

#include "pluginsmanager.h"
#include "pluginsmanagerdialog.h"
#include "plugininterface.h"
#include "../preferences/settings.h"


namespace QGamaCore {

    /** Implementation class of QGamaCore::PluginsManager.
      *
      * It's written as a singleton. Handles all actions which can be done with plugins (loading, unloading, showing,
      * hiding).
      */
    class PluginsManagerImpl : public PluginsManager
    {
        private:
            /// Pointer to the QGamaCore::PluginManagerImpl object.
            static PluginsManagerImpl *self;                     // singleton

            PluginsManagerImpl();                                // forbidden

            /// Private operator= (singleton implementation).
            PluginsManagerImpl& operator=(PluginsManagerImpl&);  // forbidden

            /// Private copy constructor (singleton implementation).
            PluginsManagerImpl(const PluginsManagerImpl&);       // forbidden

            /// Reference to QGamaCore::Settings.
            QGamaCore::Settings &settings;

            void populateMenus(QGamaCore::PluginInterface *plugin);
            void unPopulateMenus(QGamaCore::PluginInterface *plugin);

        public:
            /** Method returning a pointer to QGamaCore::PluginManagerImpl object.
              *
              * On the first call the instance is created, sequentially pointers to this instance are returned.
              */
            static PluginsManagerImpl& instance() {
                if (self == 0)
                    self = new PluginsManagerImpl();
                return *self;
            }

            /** Class destructor.
              *
              * Deletes dynamicaly created structures, that's object on the address by private instance pointer, set's the pointer
              * to null.
              */
            ~PluginsManagerImpl() { if (self != 0) { delete self; self = 0; } }  // destructor

            void loadPlugin(const QString &name);
            void enablePlugin(const QString &name);
            void disablePlugin(const QString &name);
            void unloadPlugin(const QString &name);
            void loadPlugins();
            void enablePlugins();
            void disablePlugins();
            void unloadPlugins();

            PluginInterface* plugin(const QString &key);
    }; // class PluginsManagerImpl

} // namespace QGamaCore


#endif // PLUGINSMANAGERIMPL_H
