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

#include <QWidget>
#include <QContextMenuEvent>
#include <QAction>
#include <QCursor>
#include <QMenu>
#include <QTreeWidgetItem>

#include "projectstreewidget.h"
#include "../utils/utils.h"
#include "../main_window/mainwindow.h"
#include "../factory.h"

#include <iostream>

using namespace QGamaCore;


/*
 ___          _        _      _____          __      ___    _          _
| _ \_ _ ___ (_)___ __| |_ __|_   _| _ ___ __\ \    / (_)__| |__ _ ___| |_
|  _/ '_/ _ \| / -_) _|  _(_-< | || '_/ -_) -_) \/\/ /| / _` / _` / -_)  _|
|_| |_| \___// \___\__|\__/__/ |_||_| \___\___|\_/\_/ |_\__,_\__, \___|\__|
           |__/                                              |___/

*/
/** Constructor.
  *
  */
ProjectsTreeWidget::ProjectsTreeWidget(QWidget *parent) :
        QTreeWidget(parent),
        prm(Factory::getProjectsManager()),
        settings(Factory::getSettings())
{
    // get the main window pointer
    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

    // make connections
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(openFileDoubleClick(QTreeWidgetItem*,int)));
    connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(changeActiveProject(QTreeWidgetItem*,QTreeWidgetItem*)));

    // set initial gui settings
    this->setSortingEnabled(true);
    this->sortByColumn(0);
    this->sortItems(0,Qt::AscendingOrder);
}


/*

 /\/|__          _        _      _____          __      ___    _          _
|/\/ _ \_ _ ___ (_)___ __| |_ __|_   _| _ ___ __\ \    / (_)__| |__ _ ___| |_
   |  _/ '_/ _ \| / -_) _|  _(_-< | || '_/ -_) -_) \/\/ /| / _` / _` / -_)  _|
   |_| |_| \___// \___\__|\__/__/ |_||_| \___\___|\_/\_/ |_\__,_\__, \___|\__|
              |__/                                              |___/

*/
/**
  *
  */
ProjectsTreeWidget::~ProjectsTreeWidget()
{
    Factory::releaseSettings(settings);
    Factory::releaseProjectsManager(prm);
}


/*
            _           _   __  __              ___             _
 __ ___ _ _| |_ _____ _| |_|  \/  |___ _ _ _  _| __|_ _____ _ _| |_
/ _/ _ \ ' \  _/ -_) \ /  _| |\/| / -_) ' \ || | _|\ V / -_) ' \  _|
\__\___/_||_\__\___/_\_\\__|_|  |_\___|_||_\_,_|___|\_/\___|_||_\__|

*/
/**
  *
  */
void ProjectsTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    std::cout << "contextMenuEvent start" << std::endl;

    QTreeWidgetItem *item = itemAt(event->pos());

    // if there are no opened projects, do nothing
    if (topLevelItemCount()==0) {
        return;
    }

    // if user clicked on the position, where is no item, do nothing
    else if (item==0) {
        return;
    }

    /*
    // check if the item that user clicked isn't the "project file"
    else if (item->data(0,Id).toString() == "projectFile") {
        // if so, create context menu
        QMenu menu(this);

        // create action "Open File"
        QAction *action_Open_File = menu.addAction(tr("Open File"));
        // append data with the action type and absolute path to the file
        QStringList data;
        data.append("openFile");
        data.append(item->data(0,ProjectFilePath).toString());
        action_Open_File->setData(data);

        // connect the context menu to the corresponding slot and execute it
        connect(&menu, SIGNAL(triggered(QAction*)), this, SLOT(processContextMenuAction(QAction*)));
        menu.exec(event->globalPos());
    }
    */

    // check if the item that user clicked isn't the "project name"
    else if (item->data(0,Id).toString() == "projectName") {
        // if so, create context menu
        QMenu menu(this);

        // create menu "New"
        QMenu menu_New(tr("New"),&menu);

        QAction *action_New_Network = menu_New.addAction(tr("Network"));
        action_New_Network->setIcon(QIcon(":/images/icons/network-16.png"));
        action_New_Network->setIconVisibleInMenu(true);

        QAction *action_New_Setting = menu_New.addAction(tr("Setting"));
        action_New_Setting->setIcon(QIcon(":/images/icons/setting-16.png"));
        action_New_Setting->setIconVisibleInMenu(true);

        menu.addMenu(&menu_New);
        menu.addSeparator();

        // create action "Close Project"
        QAction *action_Close_Project = menu.addAction(tr("Close"));
        // append data with the action type
        QStringList data;
        data.append("closeActiveProject");
        action_Close_Project->setData(data);

        QAction *action_Rename_Project = menu.addAction(tr("Rename..."));
        QAction *action_Move_Project = menu.addAction(tr("Move..."));
        QAction *action_Copy_Project = menu.addAction(tr("Copy..."));
        QAction *action_Delete_Project = menu.addAction(tr("Delete"));

        menu.addSeparator();

        // create action "Project Properties"
        QAction *action_Project_Properties = menu.addAction(tr("Properties"));

        // connect the context menu to the corresponding slot and execute it
        connect(&menu, SIGNAL(triggered(QAction*)), this, SLOT(processContextMenuAction(QAction*)));
        menu.exec(event->globalPos());
    }

    std::cout << "contextMenuEvent stop" << std::endl;
}


/*
                    ___ _ _     ___           _    _      ___ _ _    _
 ___ _ __  ___ _ _ | __(_) |___|   \ ___ _  _| |__| |___ / __| (_)__| |__
/ _ \ '_ \/ -_) ' \| _|| | / -_) |) / _ \ || | '_ \ / -_) (__| | / _| / /
\___/ .__/\___|_||_|_| |_|_\___|___/\___/\_,_|_.__/_\___|\___|_|_\__|_\_\
    |_|

*/
/**
  *
  */
void ProjectsTreeWidget::openFileDoubleClick(QTreeWidgetItem *current, int column)
{
    // get the main window pointer
    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

    if (current->data(0,Id).toString()=="network") {
        mw->openFile(current->data(0,FilePath).toString());
    }

    if (current->data(0,Id).toString()=="setting") {
        mw->openFile(current->data(0,FilePath).toString());
    }
}


/*
                             ___         _           _   __  __                _      _   _
 _ __ _ _ ___  __ ___ ______/ __|___ _ _| |_ _____ _| |_|  \/  |___ _ _ _  _  /_\  __| |_(_)___ _ _
| '_ \ '_/ _ \/ _/ -_|_-<_-< (__/ _ \ ' \  _/ -_) \ /  _| |\/| / -_) ' \ || |/ _ \/ _|  _| / _ \ ' \
| .__/_| \___/\__\___/__/__/\___\___/_||_\__\___/_\_\\__|_|  |_\___|_||_\_,_/_/ \_\__|\__|_\___/_||_|
|_|

*/
/**
  *
  */
void ProjectsTreeWidget::processContextMenuAction(QAction *action)
{
    std::cout << "Slot: processContextMenuAction Start" << std::endl;

    // find out the action type
    QStringList data = action->data().toStringList();
    QString id = data.value(0);
    QString parameter = data.value(1);

    // get the main window pointer
    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

    // call apropriate function based on the action type
    if (id=="openFile") {
        mw->openFile(parameter);
    }
    else if (id=="closeActiveProject") {
        prm->closeActiveProject();
    }
    else if (id=="openProject") {
    }

    std::cout << "Slot: processContextMenuAction Stop   " << id.toStdString() << std::endl;
}


/*
    _                         _      _   _         ___          _        _
 __| |_  __ _ _ _  __ _ ___  /_\  __| |_(_)_ _____| _ \_ _ ___ (_)___ __| |_
/ _| ' \/ _` | ' \/ _` / -_)/ _ \/ _|  _| \ V / -_)  _/ '_/ _ \| / -_) _|  _|
\__|_||_\__,_|_||_\__, \___/_/ \_\__|\__|_|\_/\___|_| |_| \___// \___\__|\__|
                  |___/                                      |__/

*/
/**
  *
  */
void ProjectsTreeWidget::changeActiveProject(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    std::cout << "Slot: changeActiveProject Start" << std::endl;

    QString name;
    QString location;

    // check if "current" points somewhere
    if (current!=0) {
        // get the project name and location, highlight the active project
        // searching in 1. generation
        if (current->data(0,Id).toString() == "projectName") {
            name = current->text(0);
            location = current->data(0,ProjectLocation).toString();

            highlightActiveProject(current);
        }
        // searching in 2. generation
        else if (current->parent()->data(0,Id).toString() == "projectName") {
            name = current->parent()->text(0);
            location = current->parent()->data(0,ProjectLocation).toString();
            highlightActiveProject(current->parent());
        }
        // searching in 3. generation
        else if (current->parent()->parent()->data(0,Id).toString() == "projectName") {
            name = current->parent()->parent()->text(0);
            location = current->parent()->parent()->data(0,ProjectLocation).toString();
            highlightActiveProject(current->parent()->parent());
        }

        // project the change into some File menu actions
        QMenu *menuFile = qobject_cast<QMenu*> (Utils::findWidget("menu_File"));
        QList<QAction*> actions = menuFile->actions();
        for (QList<QAction*>::iterator i=actions.begin(); i!=actions.end(); ++i) {
            if ((*i)->objectName() == "action_Close_Project" || (*i)->objectName() == "action_Project_Properties") {
                QString text = (*i)->text();
                text = text.left(text.indexOf("(")).trimmed();
                (*i)->setText(" "+text+" ("+name+")");
            }
        }

        // set selected project to be the active one in Projects Manager
        prm->setActiveProject(name,location,true);
    }

    std::cout << "Slot: changeActiveProject Stop" << std::endl;
}


/*
  __ _         _ ___          _        _   ___ _
 / _(_)_ _  __| | _ \_ _ ___ (_)___ __| |_|_ _| |_ ___ _ __
|  _| | ' \/ _` |  _/ '_/ _ \| / -_) _|  _|| ||  _/ -_) '  \
|_| |_|_||_\__,_|_| |_| \___// \___\__|\__|___|\__\___|_|_|_|
                           |__/

*/
/**
  *
  */
QTreeWidgetItem* ProjectsTreeWidget::findProjectItem(const QString &projectName, const QString &projectLocation) {
    for (int i=0; i<topLevelItemCount(); i++) {
        if (topLevelItem(i)->text(0) == projectName && topLevelItem(i)->data(0,ProjectLocation).toString() == projectLocation)
            return topLevelItem(i);
    }
    return 0;
}


/*
  __ _         _ ___ _ _      ___      _                         ___ _
 / _(_)_ _  __| | __(_) |___ / __|__ _| |_ ___ __ _ ___ _ _ _  _|_ _| |_ ___ _ __
|  _| | ' \/ _` | _|| | / -_) (__/ _` |  _/ -_) _` / _ \ '_| || || ||  _/ -_) '  \
|_| |_|_||_\__,_|_| |_|_\___|\___\__,_|\__\___\__, \___/_|  \_, |___|\__\___|_|_|_|
                                              |___/         |__/

*/
/**
  *
  */
QTreeWidgetItem* ProjectsTreeWidget::findFileCategoryItem(const QString &projectName, const QString &projectLocation, const QString &fileCategoryId) {

    QTreeWidgetItem *topItem = findProjectItem(projectName,projectLocation);
    for (int i=0; i<topItem->childCount(); i++) {
        if (topItem->child(i)->data(0,Id).toString() == fileCategoryId)
            return topItem->child(i);
    }
    return 0;
}


/*
    _     _     _       ___          _        _   ___ _
 __| |___| |___| |_ ___| _ \_ _ ___ (_)___ __| |_|_ _| |_ ___ _ __
/ _` / -_) / -_)  _/ -_)  _/ '_/ _ \| / -_) _|  _|| ||  _/ -_) '  \
\__,_\___|_\___|\__\___|_| |_| \___// \___\__|\__|___|\__\___|_|_|_|
                                  |__/

*/
/**
  *
  */
void ProjectsTreeWidget::deleteProjectItem(const QString &projectName, const QString &projectLocation)
{
    QTreeWidgetItem *item = findProjectItem(projectName, projectLocation);
    if (item!=0)
        delete item;
}


/*
         _    _ ___          _        _   ___ _
 __ _ __| |__| | _ \_ _ ___ (_)___ __| |_|_ _| |_ ___ _ __
/ _` / _` / _` |  _/ '_/ _ \| / -_) _|  _|| ||  _/ -_) '  \
\__,_\__,_\__,_|_| |_| \___// \___\__|\__|___|\__\___|_|_|_|
                          |__/

*/
/**
  *
  */
void ProjectsTreeWidget::addProjectItem(const QString &projectName, const QString &projectLocation, bool markAsActive)
{
    // add project expandable item
    QTreeWidgetItem *itemProject = new QTreeWidgetItem(this);
    itemProject->setText(0,projectName);
    itemProject->setData(0,Id,"projectName");
    itemProject->setData(0,ProjectLocation,projectLocation);
    itemProject->setIcon(0,QIcon(":/images/icons/babieca-64.png"));
    itemProject->setExpanded(true);

    // add networks, solutions, settings expandable item and non expandable projectFile item, set corresponding texts and icons
    /*
    QTreeWidgetItem *itemProjectFile = new QTreeWidgetItem(itemProject);
    itemProjectFile->setText(0,projectName+".qgp");
    itemProjectFile->setData(0,Id,"projectFile");
    itemProjectFile->setData(0,ProjectFilePath,projectLocation+projectName+"/"+projectName+".qgp");
    itemProjectFile->setIcon(0,QIcon(":/images/icons/notes-32.png"));
    */

    QTreeWidgetItem *itemNetworks = new QTreeWidgetItem(itemProject);
    itemNetworks->setText(0,QObject::tr("Networks"));
    itemNetworks->setData(0,Id,"Networks");
    itemNetworks->setIcon(0,QIcon(":/images/icons/standardbutton-open-32.png"));

    QTreeWidgetItem *itemSettings = new QTreeWidgetItem(itemProject);
    itemSettings->setText(0,QObject::tr("Settings"));
    itemSettings->setData(0,Id,"Settings");
    itemSettings->setIcon(0,QIcon(":/images/icons/standardbutton-open-32.png"));

    QTreeWidgetItem *itemSolutions = new QTreeWidgetItem(itemProject);
    itemSolutions->setText(0,QObject::tr("Solutions"));
    itemSolutions->setData(0,Id,"Solutions");
    itemSolutions->setIcon(0,QIcon(":/images/icons/standardbutton-open-32.png"));

    // mark it as active project if desired
    if (markAsActive)
        prm->setActiveProject(projectName, projectLocation);
}


/*
         _   ___          _        _   ___ _               _      _   _
 ___ ___| |_| _ \_ _ ___ (_)___ __| |_|_ _| |_ ___ _ __   /_\  __| |_(_)_ _____
(_-</ -_)  _|  _/ '_/ _ \| / -_) _|  _|| ||  _/ -_) '  \ / _ \/ _|  _| \ V / -_)
/__/\___|\__|_| |_| \___// \___\__|\__|___|\__\___|_|_|_/_/ \_\__|\__|_|\_/\___|
                       |__/

*/
/**
  *
  */
void ProjectsTreeWidget::setProjectItemActive(const QString &projectName, const QString &projectLocation)
{
    QTreeWidgetItem *item = findProjectItem(projectName, projectLocation);
    if (item!=0) {
        emit changeActiveProject(item,0);
    }
}


/*
         _    _ ___ _ _     ___ _
 __ _ __| |__| | __(_) |___|_ _| |_ ___ _ __  ___
/ _` / _` / _` | _|| | / -_)| ||  _/ -_) '  \(_-<
\__,_\__,_\__,_|_| |_|_\___|___|\__\___|_|_|_/__/

*/
/**
  *
  */
void ProjectsTreeWidget::addFileItems(Project *project)
{
    std::cout << "addFileItems START" << std::endl;

    // get the main window pointer
    MainWindow *mw = qobject_cast<MainWindow*> (Utils::findTopLevelWidget("MainWindow"));

    // add networks
    QStringList &networks = project->getNetworks();
    for (int i=0; i<networks.size(); i++) {
        QStringList file = networks[i].split("|");
        if (file.size()>3)
            continue;

        QString fileName = file.value(0);
        QString fileType = file.value(1);
        QString fileOpened = file.value(2);
        QString filePath = project->getLocation()+project->getName()+"/Networks/"+fileName;

        QTreeWidgetItem *item = new QTreeWidgetItem(findFileCategoryItem(project->getName(),project->getLocation(),"Networks"));
        item->setText(0,fileName);
        item->setData(0,Id,"network");
        item->setData(0,FileType,fileType);
        item->setData(0,FilePath,filePath);
        item->setData(0,FileOpened,fileOpened);
        item->setIcon(0,QIcon(":/images/icons/network-32.png"));
        highlightActiveFile(item);
        networks[i].append("|opened");
        //if (fileOpened=="true")
            //mw->openFile(filePath);
    }

    // add settings
    QStringList &settings = project->getSettings();
    for (int i=0; i<settings.size(); i++) {
        QStringList file = settings[i].split("|");
        if (file.size()>2)
            continue;

        QString fileName = file.value(0);
        QString fileOpened = file.value(1);
        QString filePath = project->getLocation()+project->getName()+"/Settings/"+fileName;

        QTreeWidgetItem *item = new QTreeWidgetItem(findFileCategoryItem(project->getName(),project->getLocation(),"Settings"));
        item->setText(0,fileName);
        item->setData(0,Id,"setting");
        item->setData(0,FilePath,filePath);
        item->setData(0,FileOpened,fileOpened);
        item->setIcon(0,QIcon(":/images/icons/setting-32.png"));
        highlightActiveFile(item);
        settings[i].append("|true");
        //if (fileOpened=="true")
            //mw->openFile(filePath);
    }

    std::cout << "addFileItems STOP" << std::endl;
}


/*
                     _   _   _ _ _  _ _      _    _ _      _   _   _
 __ __ _ _ _  __ ___| | /_\ | | | || (_)__ _| |_ | (_)__ _| |_| |_(_)_ _  __ _ ___
/ _/ _` | ' \/ _/ -_) |/ _ \| | | __ | / _` | ' \| | / _` | ' \  _| | ' \/ _` (_-<
\__\__,_|_||_\__\___|_/_/ \_\_|_|_||_|_\__, |_||_|_|_\__, |_||_\__|_|_||_\__, /__/
                                       |___/         |___/               |___/

*/
/**
  *
  */
void ProjectsTreeWidget::cancelAllHighlightings()
{    
    if (topLevelItemCount()>0) {
        QFont font = topLevelItem(0)->font(0);
        font.setBold(false);

        // 1. generation
        for (int i=0; i<topLevelItemCount(); ++i) {
             topLevelItem(i)->setSelected(false);
             topLevelItem(i)->setFont(0,font);

             // 2. generation
             if (topLevelItem(i)->childCount() != 0) {
                 for (int j=0; j<topLevelItem(i)->childCount(); ++j) {
                     topLevelItem(i)->child(j)->setSelected(false);
                     topLevelItem(i)->child(j)->setFont(0,font);

                     // 3. generation
                     if (topLevelItem(i)->child(j)->childCount() != 0) {
                         for (int k=0; k<topLevelItem(i)->child(j)->childCount(); ++k) {
                             topLevelItem(i)->child(j)->child(k)->setSelected(false);
                             topLevelItem(i)->child(j)->child(k)->setFont(0,font);
                         }
                     }
                 }
             }
         }
    }
}


/*
 _    _      _    _ _      _   _     _      _   _         ___          _        _
| |_ (_)__ _| |_ | (_)__ _| |_| |_  /_\  __| |_(_)_ _____| _ \_ _ ___ (_)___ __| |_
| ' \| / _` | ' \| | / _` | ' \  _|/ _ \/ _|  _| \ V / -_)  _/ '_/ _ \| / -_) _|  _|
|_||_|_\__, |_||_|_|_\__, |_||_\__/_/ \_\__|\__|_|\_/\___|_| |_| \___// \___\__|\__|
       |___/         |___/                                          |__/

*/
/**
  *
  */
void ProjectsTreeWidget::highlightActiveProject(QTreeWidgetItem *item)
{
    // cancel all highlightings
    cancelAllHighlightings();

    // emphasize with bold letters
    QFont font = item->font(0);
    font.setBold(true);
    item->setFont(0,font);
}


/*
 _    _      _    _ _      _   _     _      _   _         ___ _ _
| |_ (_)__ _| |_ | (_)__ _| |_| |_  /_\  __| |_(_)_ _____| __(_) |___
| ' \| / _` | ' \| | / _` | ' \  _|/ _ \/ _|  _| \ V / -_) _|| | / -_)
|_||_|_\__, |_||_|_|_\__, |_||_\__/_/ \_\__|\__|_|\_/\___|_| |_|_\___|
       |___/         |___/

*/
/**
  *
  */
void ProjectsTreeWidget::highlightActiveFile(QTreeWidgetItem *item)
{
    highlightActiveProject(item->parent()->parent());

    // set the item selected and it's parent expanded
    item->setSelected(true);
    item->parent()->setExpanded(true);
    item->parent()->parent()->setExpanded(true);
}


/**
  *
  */
void ProjectsTreeWidget::collapseNonActiveProjects()
{
    QStringList activeProject = settings->get("projects/activeProject").toStringList();
    for (int i=0; i<topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = topLevelItem(i);
        if (item->text(0)!=activeProject.value(0) || item->data(0,ProjectLocation)!=activeProject.value(1)) {
            item->setExpanded(false);
            for (int j=0; j<item->childCount(); ++j)
                item->child(j)->setExpanded(false);
        }
    }
}
