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
#include "../utils/utils.h"
#include "../factory.h"
#include "../main_window/mainwindow.h"

#include <iostream>


using namespace QGamaCore;


// Inicialization of the private instance pointer to null.
ProjectsManagerImpl* ProjectsManagerImpl::self = 0;

// inicialization of the private counter of pointers
int ProjectsManagerImpl::pointersCount = 0;


/*
 ___          _        _      __  __                            ___            _
| _ \_ _ ___ (_)___ __| |_ __|  \/  |__ _ _ _  __ _ __ _ ___ _ |_ _|_ __  _ __| |
|  _/ '_/ _ \| / -_) _|  _(_-< |\/| / _` | ' \/ _` / _` / -_) '_| || '  \| '_ \ |
|_| |_| \___// \___\__|\__/__/_|  |_\__,_|_||_\__,_\__, \___|_||___|_|_|_| .__/_|
           |__/                                    |___/                 |_|

*/
/** Constructor.
  *
  * Initializes the reference to QGamaCore::Settings.
  */
ProjectsManagerImpl::ProjectsManagerImpl() :
    settings(Factory::getSettings())
{
}


/*
 _         _
(_)_ _  __| |_ __ _ _ _  __ ___
| | ' \(_-<  _/ _` | ' \/ _/ -_)
|_|_||_/__/\__\__,_|_||_\__\___|

*/
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


/*
         _
 _ _ ___| |___ __ _ ___ ___
| '_/ -_) / -_) _` (_-</ -_)
|_| \___|_\___\__,_/__/\___|

*/
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


/*

 /\/|__          _        _      __  __                            ___            _
|/\/ _ \_ _ ___ (_)___ __| |_ __|  \/  |__ _ _ _  __ _ __ _ ___ _ |_ _|_ __  _ __| |
   |  _/ '_/ _ \| / -_) _|  _(_-< |\/| / _` | ' \/ _` / _` / -_) '_| || '  \| '_ \ |
   |_| |_| \___// \___\__|\__/__/_|  |_\__,_|_||_\__,_\__, \___|_||___|_|_|_| .__/_|
              |__/                                    |___/                 |_|

*/
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


/*
                 ___          _        _
 _ _  _____ __ _| _ \_ _ ___ (_)___ __| |_
| ' \/ -_) V  V /  _/ '_/ _ \| / -_) _|  _|
|_||_\___|\_/\_/|_| |_| \___// \___\__|\__|
                           |__/

*/
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
    // get the pointer to the main window widget
    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

    // get the project home directory
    QDir directory(projectLocation);

    // create it if doesn't exist
    if (!directory.exists(directory.absolutePath()))
        directory.mkpath(directory.path());

    // if it deals of a single network project
    if (projectType=="SingleNetworkProject") {
        // create the project structure, inform about potencial problems
        if (!directory.mkdir(projectName) || !directory.mkpath(projectName+"/Network") || !directory.mkpath(projectName+"/Solutions")) {
            QMessageBox::critical( mw, QObject::tr("Project could not be created!"), QObject::tr("Probably there were insufficient permisions to create the project structure in the specified directory."));
            return false;
        }

        // create project file, inform about potencial problems
        QFile file(directory.absolutePath()+"/"+projectName+"/"+projectName+".qgp");
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical( mw, QObject::tr("Project could not be created!"), QObject::tr("Probably there were insufficient permisions to create the project structure in the specified directory."));
            return false;
        }

        // initialize its xml content
        QDomDocument projectDocument("qgamaproject");

        QDomElement projectElement = projectDocument.createElement("qgamaprojectfile");
        projectElement.setAttribute("name",projectName);
        projectElement.setAttribute("type",projectType);
        projectDocument.appendChild(projectElement);

        QDomElement networksElement = projectDocument.createElement("networks");
        projectElement.appendChild(networksElement);

        QDomElement settingsElement = projectDocument.createElement("settings");
        projectElement.appendChild(settingsElement);

        QDomElement solutionsElement = projectDocument.createElement("solutions");
        projectElement.appendChild(solutionsElement);

        // write into file
        QTextStream ts(&file);
        ts << projectDocument.toString();

        // close the file
        file.close();
    }

    return true;
}


/*
                    ___          _        _
 ___ _ __  ___ _ _ | _ \_ _ ___ (_)___ __| |_
/ _ \ '_ \/ -_) ' \|  _/ '_/ _ \| / -_) _|  _|
\___/ .__/\___|_||_|_| |_| \___// \___\__|\__|
    |_|                       |__/

*/
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
    ProjectsTreeWidget *ptw = qobject_cast<ProjectsTreeWidget*> (Utils::findWidget("treeWidget_Projects"));

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

        // read the project specifications
        if (readFilesFromProjectXml(project)) {
            // create treewidget's item
            ptw->addProjectItem(projectName, projectLocation, markAsActive);
            ptw->addFileItems(project);
        }

        // save the project to be opened next time program is executed
        QStringList openedProjects = settings->get("projects/openedProjects").toStringList();
        if (!openedProjects.contains(project->getProjectFilePath())) {
            openedProjects.append(project->getProjectFilePath());
            settings->set("projects/openedProjects",openedProjects);
        }

        // get the pointer to the main window widget
        MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

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
        ptw->setProjectItemActive(projectName, projectLocation);
    }

    return true;
}


/*
    _             ___          _        _
 __| |___ ___ ___| _ \_ _ ___ (_)___ __| |_
/ _| / _ (_-</ -_)  _/ '_/ _ \| / -_) _|  _|
\__|_\___/__/\___|_| |_| \___// \___\__|\__|
                            |__/

*/
/**
  *
  */
void ProjectsManagerImpl::closeProject(Project* project)
{
    std::cout << "closeProject START" << std::endl;

    // get the pointer to the projects tree widget
    ProjectsTreeWidget *ptw = qobject_cast<ProjectsTreeWidget*> (Utils::findWidget("treeWidget_Projects"));

    // delete the project tree widget entries
    ptw->deleteProjectItem(project->getName(), project->getLocation());

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

    // get the pointer to the main window widget
    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

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


/*
    _               _      _   _         ___          _        _
 __| |___ ___ ___  /_\  __| |_(_)_ _____| _ \_ _ ___ (_)___ __| |_
/ _| / _ (_-</ -_)/ _ \/ _|  _| \ V / -_)  _/ '_/ _ \| / -_) _|  _|
\__|_\___/__/\___/_/ \_\__|\__|_|\_/\___|_| |_| \___// \___\__|\__|
                                                   |__/

*/
/**
  *
  */
void ProjectsManagerImpl::closeActiveProject()
{
    std::cout << "closeActiveProject START" << std::endl;

    closeProject(getActiveProject());

    std::cout << "closeActiveProject STOP" << std::endl;
}


/*
          _     _      _   _         ___          _        _
 __ _ ___| |_  /_\  __| |_(_)_ _____| _ \_ _ ___ (_)___ __| |_
/ _` / -_)  _|/ _ \/ _|  _| \ V / -_)  _/ '_/ _ \| / -_) _|  _|
\__, \___|\__/_/ \_\__|\__|_|\_/\___|_| |_| \___// \___\__|\__|
|___/                                          |__/

*/
/**
  *
  */
Project* ProjectsManagerImpl::getActiveProject()
{
    std::cout << "getActiveProject START" << std::endl;

    for (int i=0; i<projects.size(); i++) {
        if (projects[i]->isActive()) {
            return projects[i];
        }
    }

    return 0;
}


/*
         _     _      _   _         ___          _        _
 ___ ___| |_  /_\  __| |_(_)_ _____| _ \_ _ ___ (_)___ __| |_
(_-</ -_)  _|/ _ \/ _|  _| \ V / -_)  _/ '_/ _ \| / -_) _|  _|
/__/\___|\__/_/ \_\__|\__|_|\_/\___|_| |_| \___// \___\__|\__|
                                              |__/

*/
/**
  *
  */
void ProjectsManagerImpl::setActiveProject(const QString &projectName, const QString &projectLocation, bool slotCall)
{
    for (int i=0; i<projects.size(); i++) {
        if (projects[i]->getName()==projectName && projects[i]->getLocation()==projectLocation) {
            projects[i]->setActive(true);
         }
        else
            projects[i]->setActive(false);
    }

    QStringList data;
    data.append(projectName);
    data.append(projectLocation);
    settings->set("projects/activeProject",data);

    if (!slotCall) {
        // get the pointer to the projects tree widget
        ProjectsTreeWidget *ptw = qobject_cast<ProjectsTreeWidget*> (Utils::findWidget("treeWidget_Projects"));

        // "commit" changes in the projectsTreeWidget
        ptw->setProjectItemActive(projectName, projectLocation);
    }
}


/*
                 ___ _ _
 _ _  _____ __ _| __(_) |___
| ' \/ -_) V  V / _|| | / -_)
|_||_\___|\_/\_/|_| |_|_\___|

*/
/**
  *
  */
bool ProjectsManagerImpl::newFile(const QString &fileToCreate, const QString &fileType)
{
    QStringList aux = fileToCreate.split("/");
    QString fileName = aux.value(aux.size()-1);
    QString fileCategory = aux.value(aux.size()-2).toLower();
    QString projectName = aux.value(aux.size()-3);
    QString projectLocation;
    for (int i=0; i<aux.size()-3; i++)
        projectLocation.append(aux[i]+"/");

    // get the pointer to the main window widget
    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

    // create the file, inform about potencial problems
    QFile file(fileToCreate);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical( mw, QObject::tr("File could not be created!"), QObject::tr("Probably there were insufficient permisions to create the file in the specified directory."));
        return false;
    }

    // close the file
    file.close();

    // find the apropriate project
    Project* project = getProject(projectName,projectLocation);

    // if was found
    if (project != 0) {       
        // get the pointer to the projects tree widget
        ProjectsTreeWidget *ptw = qobject_cast<ProjectsTreeWidget*> (Utils::findWidget("treeWidget_Projects"));

        // add the file to the list of files mantained by project class
        if (fileCategory == "networks") {
            project->addNetwork(fileName+"|"+fileType+"|true");
        }
        else if (fileCategory == "settings") {
            project->addSetting(fileName+"|true");
        }

        // add it to the project's xml and display it in projectstreewidget
        if (writeFileToProjectXml(fileName, fileCategory, fileType, project->getProjectFilePath()))
            ptw->addFileItems(project);

        // open the project
        mw->openFile(fileToCreate);
    }

    return true;
}


/**
  *
  */
bool ProjectsManagerImpl::writeFileToProjectXml(const QString &fileName, const QString &fileCategory, const QString &fileType, const QString &projectFilePath)
{
    // get the pointer to the main window widget
    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

    // open the project file
    QFile file(projectFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical( mw, QObject::tr("Project file could not be opened!"), QObject::tr("Check out if it has set sufficient permissions to read from it."));
        return false;
    }

    // initialize the document content from it
    QDomDocument projectDocument("qgamaproject");
    projectDocument.setContent(&file);
    file.close();

    // get main project element
    QDomElement projectElement = projectDocument.documentElement();

    // get category elements
    QDomNode categoryNode = projectElement.firstChild();
    while (!categoryNode.isNull()) {
        QDomElement categoryElement = categoryNode.toElement();

        if (categoryElement.tagName() == fileCategory) {
            if (fileCategory == "networks") {
                QDomElement fileElement = projectDocument.createElement("network");
                fileElement.setAttribute("type",fileType);
                fileElement.setAttribute("name",fileName);
                fileElement.setAttribute("opened","true");
                categoryElement.appendChild(fileElement);
            }
            else if (fileCategory == "settings") {
                QDomElement fileElement = projectDocument.createElement("setting");
                fileElement.setAttribute("name",fileName);
                fileElement.setAttribute("opened","true");
                categoryElement.appendChild(fileElement);
            }
            else if (fileCategory == "solutions") {
                QDomElement fileElement = projectDocument.createElement("solution");
                fileElement.setAttribute("name",fileName);
                fileElement.setAttribute("opened","true");
                categoryElement.appendChild(fileElement);
            }
        }

        categoryNode =  categoryNode.nextSibling();
    }

    // open the project file
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical( mw, QObject::tr("Project file could not be opened!"), QObject::tr("Check out if it has set sufficient permissions to write to it."));
        return false;
    }

    // "commit" it to the file
    QTextStream ts(&file);
    ts << projectDocument.toString();

    // close the file
    file.close();

    return true;
}


/**
  *
  */
bool ProjectsManagerImpl::readFilesFromProjectXml(Project *project)
{
    // get the pointer to the main window widget
    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

    // open the project file
    QFile file(project->getProjectFilePath());
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical( mw, QObject::tr("Project file could not be opened!"), QObject::tr("Check out if it has set sufficient permissions to read from it."));
        return false;
    }

    // initialize the document content from it
    QDomDocument projectDocument("qgamaproject");
    projectDocument.setContent(&file);
    file.close();

    // get main project element
    QDomElement projectElement = projectDocument.documentElement();

    // get category elements
    QDomNode categoryNode = projectElement.firstChild();
    while (!categoryNode.isNull()) {
        QDomElement categoryElement = categoryNode.toElement();

        if (categoryElement.tagName() == "networks") {
            QDomNode networksNode = categoryElement.firstChild();

            while (!networksNode.isNull()) {
                QDomElement networksElement = networksNode.toElement();

                project->addNetwork(networksElement.attribute("name")+"|"+networksElement.attribute("type")+"|"+networksElement.attribute("opened"));

                networksNode = networksNode.nextSibling();
            }
        }

        else if (categoryElement.tagName() == "settings") {
            QDomNode settingsNode = categoryElement.firstChild();

            while (!settingsNode.isNull()) {
                QDomElement settingsElement = settingsNode.toElement();

                project->addSetting(settingsElement.attribute("name")+"|"+settingsElement.attribute("opened"));

                settingsNode = settingsNode.nextSibling();
            }
        }


        else if (categoryElement.tagName() == "solutions") {
            QDomNode solutionsNode = categoryElement.firstChild();

            while (!solutionsNode.isNull()) {
                QDomElement solutionsElement = solutionsNode.toElement();

                project->addSolution(solutionsElement.attribute("name")+"|"+solutionsElement.attribute("opened"));

                solutionsNode = solutionsNode.nextSibling();
            }
        }

        categoryNode = categoryNode.nextSibling();
    }

    // open the project file
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical( mw, QObject::tr("Project file could not be opened!"), QObject::tr("Check out if it has set sufficient permissions to write to it."));
        return false;
    }

    // "commit" it to the file
    QTextStream ts(&file);
    ts << projectDocument.toString();

    // close the file
    file.close();

    return true;
}


/**
  *
  */
Project* ProjectsManagerImpl::getProject(const QString &name, const QString &location)
{
    for (int i=0; i<projects.size(); ++i) {
        if (projects[i]->getName() == name && projects[i]->getLocation() == location)
            return projects[i];
    }

    return 0;
}


/**
  *
  */
bool ProjectsManagerImpl::isProjectOpened(const QString &name, const QString &location)
{
    for (int i=0; i<projects.size(); ++i) {
        if (projects[i]->getName() == name && projects[i]->getLocation() == location)
            return true;
    }

    return false;
}
