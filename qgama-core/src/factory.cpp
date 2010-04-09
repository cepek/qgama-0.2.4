#include "factory.h"

#include "preferences/settingsimpl.h"
#include "preferences/settings.h"
#include "plugins_manager/pluginsmanager.h"
#include "plugins_manager/pluginsmanagerimpl.h"
#include "projects_manager/projectsmanager.h"
#include "projects_manager/projectsmanagerimpl.h"

#include <iostream>

using namespace QGamaCore;


/**
  *
  */
Settings* Factory::getSettings()
{
    return SettingsImpl::instance();
}


/**
  *
  */
void Factory::releaseSettings(Settings* &settings)
{
    if (settings!=0) {
        settings->release();
        settings=0;
    }
}


/**
  *
  */
ProjectsManager* Factory::getProjectsManager()
{
    return ProjectsManagerImpl::instance();
}


/**
  *
  */
void Factory::releaseProjectsManager(ProjectsManager* &projectsManager)
{
    if (projectsManager!=0) {
        projectsManager->release();
        projectsManager=0;
    }
}


/**
  *
  */
PluginsManager* Factory::getPluginsManager()
{
    return PluginsManagerImpl::instance();
}


/**
  *
  */
void Factory::releasePluginsManager(PluginsManager* &pluginsManager)
{
    if (pluginsManager!=0) {
        pluginsManager->release();
        pluginsManager=0;
    }
}
