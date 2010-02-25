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

#ifndef PLUGINMANAGERIMPL_H
#define PLUGINMANAGERIMPL_H

#include <QMap>
#include <QDir>
#include <QStringList>
#include <QPluginLoader>

#include "pluginmanager.h"
#include "pluginmanagerdialog.h"
#include "plugininterface.h"
#include "../preferences/qgamasettings.h"


namespace QGamaCore {

    /** Implementation class of QGamaCore::PluginManager.
      *
      * It's written as a singleton. Handles all actions which can be done with plugins (loading, unloading, showing,
      * hiding).
      */
    class PluginManagerImpl : public PluginManager
    {
        private:
            /// Pointer to the QGamaCore::PluginManagerImpl object.
            static PluginManagerImpl *self;                     // singleton

            PluginManagerImpl();                                // forbidden

            /// Private operator= (singleton implementation).
            PluginManagerImpl& operator=(PluginManagerImpl&);   // forbidden

            /// Private copy constructor (singleton implementation).
            PluginManagerImpl(const PluginManagerImpl&);        // forbidden

            /// Reference to QGamaCore::QGamaSettings.
            QGamaSettings &settings;

            void populateMenus(QGamaCore::PluginInterface *plugin);
            void unPopulateMenus(QGamaCore::PluginInterface *plugin);

        public:
            /** Method returning a pointer to QGamaCore::PluginManagerImpl object.
              *
              * On the first call the instance is created, sequentially pointers to this instance are returned.
              */
            static PluginManagerImpl& instance() {
                if (self == 0)
                    self = new PluginManagerImpl();
                return *self;
            }

            /** Class destructor.
              *
              * Deletes dynamicaly created structures, that's object on the address by private instance pointer, set's the pointer
              * to null.
              */
            ~PluginManagerImpl() { if (self != 0) { delete self; self = 0; } }  // destructor

            void loadPlugin(const QString &name);
            void enablePlugin(const QString &name);
            void disablePlugin(const QString &name);
            void unloadPlugin(const QString &name);
            void loadPlugins();
            void enablePlugins();
            void disablePlugins();
            void unloadPlugins();

            PluginInterface* plugin(const QString &key);
    }; // class PluginManagerImpl

} // namespace QGamaCore


#endif // PLUGINMANAGERIMPL_H
