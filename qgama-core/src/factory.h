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

#ifndef QGAMACORE__FACTORY_H
#define QGAMACORE__FACTORY_H

#include "preferences/settingsimpl.h"
#include "preferences/settings.h"
#include "plugins_manager/pluginsmanager.h"
#include "plugins_manager/pluginsmanagerimpl.h"
#include "projects_manager/projectsmanager.h"
#include "projects_manager/projectsmanagerimpl.h"
#include "utils/applicationcomponentprovider.h"
#include "utils/applicationcomponentproviderimpl.h"


namespace QGamaCore {

    /**
      *
      */
    class Factory
    {
        private:
            Factory();

        public:
            // settings
            static Settings* getSettings();
            static void releaseSettings(Settings* &settings);

            // projects manager
            static ProjectsManager* getProjectsManager();
            static void releaseProjectsManager(ProjectsManager* &projectsManager);

            // plugins manager
            static PluginsManager* getPluginsManager();
            static void releasePluginsManager(PluginsManager* &pluginsManager);

            // application component provider
            static ApplicationComponentProvider* getApplicationComponentProvider();
            static void releaseApplicationComponentProvider(ApplicationComponentProvider* &applicationComponentProvider);
    };

} // namespace QGamaCore

#endif // QGAMACORE__FACTORY_H
