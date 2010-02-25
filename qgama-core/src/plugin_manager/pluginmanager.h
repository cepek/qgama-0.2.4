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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QPluginLoader>
#include <QDir>
#include <QString>
#include <QStringList>

#include "plugininterface.h"


namespace QGamaCore {

    /** Abstract class defining basic interface which plugin manager has to implement.
      *
      */
    class PluginManager
    {
        protected:
            /// Directory, from which the plugins are loaded.
            QDir pluginsDir;

            /// Names of all available plugins in that directory.
            QStringList fileNames;

            /// Map storing pointers to all of the plugins in plugin's directory.
            QMap<QString,QPluginLoader*> plugins;

        public:
            virtual void loadPlugin(const QString &name) = 0;
            virtual void enablePlugin(const QString &name) = 0;
            virtual void disablePlugin(const QString &name) = 0;
            virtual void unloadPlugin(const QString &name) = 0;

            virtual void loadPlugins() = 0;
            virtual void enablePlugins() = 0;
            virtual void disablePlugins() = 0;
            virtual void unloadPlugins() = 0;

            virtual PluginInterface* plugin(const QString &key) = 0;
    }; // class PluginManager
} // namespace QGamaCore

#endif // PLUGINMANAGER_H
