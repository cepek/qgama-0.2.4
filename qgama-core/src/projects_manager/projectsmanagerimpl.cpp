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

#include <QtGui>
#include <QDomDocument>

#include "projectsmanagerimpl.h"
#include "projectstreewidget.h"
#include "../../../config.h"
#include "../utils/applicationcomponentprovider.h"
#include "../factory.h"
#include "../main_window/mainwindow.h"
#include "file.h"

#include <iostream>


using namespace QGamaCore;


// Inicialization of the private instance pointer to null.
ProjectsManagerImpl* ProjectsManagerImpl::self = 0;

// inicialization of the private counter of pointers
int ProjectsManagerImpl::pointersCount = 0;


/* ===============================================================================================================*/
/** Constructor.
  *
  * Initializes the reference to QGamaCore::Settings.
  */
ProjectsManagerImpl::ProjectsManagerImpl() :
    settings(Factory::getSettings())
{
}


/* ===============================================================================================================*/
/** Method returning a pointer to QGamaCore::ProjectsManagerImpl object.
  *
  * On the first call the instance is created, sequentially pointers to this instance are returned.
  * Also a counter of pointers is hold.
  */
ProjectsManagerImpl* ProjectsManagerImpl::instance() {
    if (self == 0) {
        self = new ProjectsManagerImpl();
    }
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
void ProjectsManagerImpl::release()
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
ProjectsManagerImpl::~ProjectsManagerImpl()
{
    Factory::releaseSettings(settings);

    // delete projects list
    for (int i=0; i<projectsCount(); i++)
        delete projects[i];

    std::cout << "ProjectsManagerImpl - Destruktor" << std::endl;
}


/* ===============================================================================================================*/
/** Creates the structure of a new project.
  *
  * That consists of creating the project directory in the user home (or at the other directory specified in preferences),
  * subdirectories for networks, settings and solutions and corresponding project file.
  *
  * \param[in] projectType         The type of the project to be created.
  * \param[in] projectName         The name of the project to be created.
  * \param[in] projectLocation     The location where the project directory will be created.
  *
  * \return                        True or False, dependent whether the action was successfull or not.
  */
bool ProjectsManagerImpl::newProject(const QString &projectType, const QString &projectName, const QString &projectLocation)
{
    // call the static function of Project to create the corresponding project structure
    return Project::createProjectStructure(projectType, projectName, projectLocation);
}


/* ===============================================================================================================*/
/** Opens a project based on the information included in specified project file.
  *
  * \param[in] projectFilePath     The absolute path to the project file (*.qgp)
  * \param[in] markAsActive        Specifier, whether the project should be marked as active after its opening. Default is true.
  *
  * \return                        True or False, dependent whether the action was successfull or not.
  */
bool ProjectsManagerImpl::openProject(const QString &projectFilePath, bool markAsActive)
{
    // get the pointer to the projects tree widget
    ProjectsTreeWidget *ptw = ApplicationComponentProvider::getProjectsTreeWidget();

    // get the project location and name from the projectFile absolute path
    QStringList path = projectFilePath.split("/");
    QString projectLocation;
    QString projectName;
    for (int i=0; i<path.size()-1; ++i) {
        if (i==path.size()-2) {
            projectName = path[i];
            continue;
        }
        projectLocation.append(path[i]+"/");
    }

    // if wasn't already opened, process its projectFile and open it
    if (!isProjectOpened(projectName,projectLocation)) {
        // create a new project and append it to the list of projects
        Project *project = new Project(projectName,projectLocation,projectFilePath);
        projects.append(project);

        // create project's treewidget item
        ptw->addProjectItem(project);
        ptw->addFileItems(project, false);

        // mark opened project as active if desired
        if (markAsActive)
            setActiveProject(projectName, projectLocation);

        // save the project to be opened next time program is executed
        QStringList openedProjects = settings->get("projects/openedProjects").toStringList();
        if (!openedProjects.contains(project->getProjectFilePath())) {
            openedProjects.append(project->getProjectFilePath());
            settings->set("projects/openedProjects",openedProjects);
        }

        // get the pointer to the main window widget
        MainWindow *mw = ApplicationComponentProvider::getMainWindow();

        // increase the counter of the opened projects
        mw->increaseProjectsCount();

        // remove the project from the list of the last five recently opened projects
        QStringList recentlyOpenedProjects = settings->get("projects/recentlyOpenedProjects").toStringList();
        if (recentlyOpenedProjects.contains(project->getProjectFilePath())) {
            recentlyOpenedProjects.removeAt(recentlyOpenedProjects.indexOf(project->getProjectFilePath()));
            settings->set("projects/recentlyOpenedProjects",recentlyOpenedProjects);

            // and "commit" the change
            mw->updateRecentlyOpenedProjects();
        }
    }

    // if was already opened
    else {
        setActiveProject(projectName, projectLocation);
    }

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsManagerImpl::closeProject(Project* project)
{
    // get the pointer to the projects tree widget
    ProjectsTreeWidget *ptw = ApplicationComponentProvider::getProjectsTreeWidget();

    // delete the project tree widget entries
    ptw->deleteProjectItem(project->getName(), project->getLocation());

    // get the pointer to the main window widget
    MainWindow *mw = ApplicationComponentProvider::getMainWindow();

    // close all projects networks
    QList<File>& networks = project->getNetworks();
    for (int i=0; i<networks.size(); i++) {
        mw->closeFile(networks[i].getPath());
    }

    // save the project to be opened next time program is executed
    QStringList openedProjects = settings->get("projects/openedProjects").toStringList();
    for (int i=0; i<openedProjects.size(); i++) {
        if (openedProjects[i]==project->getProjectFilePath()) {
            openedProjects.removeAt(i);
            break;
        }
    }
    if (openedProjects.size()>0) {
        settings->set("projects/openedProjects",openedProjects);
    }
    else {
        settings->del("projects/openedProjects");
        settings->del("projects/activeProject");
    }

    // save the project to the list of the last five recently opened projects
    QStringList recentlyOpenedProjects = settings->get("projects/recentlyOpenedProjects").toStringList();
    if (!recentlyOpenedProjects.contains(project->getProjectFilePath())) {
        if (recentlyOpenedProjects.size()==5) {
            recentlyOpenedProjects.removeAt(0);
        }
        recentlyOpenedProjects.append(project->getProjectFilePath());
        settings->set("projects/recentlyOpenedProjects",recentlyOpenedProjects);
    }
    else {
        int index = recentlyOpenedProjects.indexOf(project->getProjectFilePath());
        recentlyOpenedProjects.removeAt(index);
        recentlyOpenedProjects.append(project->getProjectFilePath());
    }

    // and "commit" the change
    mw->updateRecentlyOpenedProjects();

    // delete the project
    for (int i=0; i<projects.size(); i++) {
        if (projects[i]==project) {
            projects.removeAt(i);
        }
    }
    delete project;

    // if it wasn't the last project, change the focus to the preceding one
    int n = projects.size();
    if (n!=0) {
        setActiveProject(projects[n-1]->getName(), projects[n-1]->getLocation());
    }

    // increase the counter of the opened projects
    mw->decreaseProjectsCount();
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsManagerImpl::closeActiveProject()
{
    // close active project
    closeProject(getActiveProject());
}


/* ===============================================================================================================*/
/**
  *
  */
Project* ProjectsManagerImpl::getActiveProject()
{
    // return active project if found, otherwise return 0
    for (int i=0; i<projects.size(); i++) {
        if (projects[i]->isActive()) {
            return projects[i];
        }
    }

    return 0;
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsManagerImpl::setActiveProject(const QString &projectName, const QString &projectLocation, bool slotCall)
{
    // get the pointer to the projects tree widget
    ProjectsTreeWidget *ptw = ApplicationComponentProvider::getProjectsTreeWidget();

    // set all inactive but the one specified in function parameters
    for (int i=0; i<projects.size(); i++) {
        if (projects[i]->getName()==projectName && projects[i]->getLocation()==projectLocation) {
            projects[i]->setActive(true);
         }
        else
            projects[i]->setActive(false);
    }

    // save the active project into program settings
    QStringList data;
    data.append(projectName);
    data.append(projectLocation);
    settings->set("projects/activeProject",data);

    // if this function wasn't called from projectsTreeWidget event, commit the change there
    if (!slotCall)
        ptw->setProjectItemActive(projectName, projectLocation);
}


/* ===============================================================================================================*/
/**
  *
  */
Project* ProjectsManagerImpl::getProject(const QString &name, const QString &location)
{
    // return the project with the specified name and location if found, otherwise return 0
    for (int i=0; i<projects.size(); ++i) {
        if (projects[i]->getName() == name && projects[i]->getLocation() == location)
            return projects[i];
    }

    return 0;
}


/* ===============================================================================================================*/
/**
  *
  */
bool ProjectsManagerImpl::isProjectOpened(const QString &name, const QString &location)
{
    // return true if the project with the specified name is already opened and false if not
    for (int i=0; i<projects.size(); ++i) {
        if (projects[i]->getName() == name && projects[i]->getLocation() == location)
            return true;
    }

    return false;
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsManagerImpl::updateProjectFilesEntries()
{
    // update project file XMLs for every opened project
    for (int i=0; i<projectsCount(); i++) {
        projects[i]->updateProjectFileEntries();
    }
}
