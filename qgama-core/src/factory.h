#ifndef FACTORY_H
#define FACTORY_H

#include "preferences/settingsimpl.h"
#include "preferences/settings.h"
#include "plugins_manager/pluginsmanager.h"
#include "plugins_manager/pluginsmanagerimpl.h"
#include "projects_manager/projectsmanager.h"
#include "projects_manager/projectsmanagerimpl.h"


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
    };

} // namespace QGamaCore

#endif // FACTORY_H
