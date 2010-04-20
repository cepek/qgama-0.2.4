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

#include "projectstreewidget.h"
#include "../utils/applicationcomponentprovider.h"
#include "../main_window/mainwindow.h"
#include "../factory.h"
#include "adjustmentsetting.h"
#include "adjustmentsettingdialog.h"

#include <iostream>

using namespace QGamaCore;


enum { Id=32, ProjectLocation=33, AdjustmentSettingId=34, NetworkId=35, SolutionId=36 };


/* ===============================================================================================================*/
/** Constructor.
  *
  */
ProjectsTreeWidget::ProjectsTreeWidget(QWidget *parent) :
        QTreeWidget(parent),
        prm(Factory::getProjectsManager()),
        settings(Factory::getSettings()),
        mw(ApplicationComponentProvider::getMainWindow())
{
    // make connections
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(openFileDoubleClick(QTreeWidgetItem*,int)));
    connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(changeActiveProject(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(this, SIGNAL(updateFileMenuEntries(Project*)), mw, SLOT(updateFileMenuEntries(Project*)));

    // set initial gui settings
    this->setSortingEnabled(true);
    this->sortByColumn(0);
    this->sortItems(0,Qt::AscendingOrder);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setSelectionBehavior(QAbstractItemView::SelectItems);
}


/* ===============================================================================================================*/
/**
  *
  */
ProjectsTreeWidget::~ProjectsTreeWidget()
{
    Factory::releaseSettings(settings);
    Factory::releaseProjectsManager(prm);
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::contextMenuEvent(QContextMenuEvent *event)
{
    qDebug() << "ProjectsTreeWidget::contextMenuEvent() - START";

    QTreeWidgetItem *item = itemAt(event->pos());

    // if there are no opened projects, do nothing
    if (topLevelItemCount()==0) {
        return;
    }

    // if user clicked on the position, where is no item, do nothing
    else if (item==0) {
        return;
    }

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

    qDebug() << "ProjectsTreeWidget::contextMenuEvent() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::openFileDoubleClick(QTreeWidgetItem *current, int column)
{
    QString fileId = current->data(0,Id).toString();

    Project *project = prm->getActiveProject();
    Q_ASSERT(project!=0 && "active project is 0!");

    if (fileId=="network") {
        int networkId = current->data(0,NetworkId).toInt();
        QString networkPath = project->getNetwork(networkId)->getPath();
        mw->openFile(networkPath,"network",project);
    }
    else if (fileId=="setting") {
        int adjustmentSettingId = current->data(0,AdjustmentSettingId).toInt();
        AdjustmentSetting *adjustmentSetting = project->getAdjustmentSetting(adjustmentSettingId);
        AdjustmentSettingDialog dialog(adjustmentSetting,mw);
        dialog.exec();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::processContextMenuAction(QAction *action)
{
    // find out the action type
    QStringList data = action->data().toStringList();
    QString id = data.value(0);
    QString parameter = data.value(1);

    // call apropriate function based on the action type
    if (id=="openFile") {
        mw->openFile(parameter,"network",prm->getActiveProject());
    }
    else if (id=="closeActiveProject") {
        prm->closeActiveProject();
    }
    else if (id=="openProject") {
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::changeActiveProject(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    qDebug() << "ProjectsTreeWidget::changeActiveProject() - START";

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
        Project *project = prm->getProject(name,location);
        if (project!=0)
            emit updateFileMenuEntries(project);

        // set selected project to be the active one in Projects Manager
        prm->setActiveProject(project,true);
    }

    qDebug() << "ProjectsTreeWidget::changeActiveProject() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
QTreeWidgetItem* ProjectsTreeWidget::findProjectItem(Project *project)
{
    Q_ASSERT(project!=0 && "project pointer is 0!");

    // find the corresponding project item and return it
    for (int i=0; i<topLevelItemCount(); i++) {
        if (topLevelItem(i)->text(0) == project->getName() && topLevelItem(i)->data(0,ProjectLocation).toString() == project->getLocation()) {
            return topLevelItem(i);
        }
    }

    return 0;
}


/* ===============================================================================================================*/
/**
  *
  */
QTreeWidgetItem* ProjectsTreeWidget::findFileCategoryItem(Project *project, const QString &fileCategoryId)
{
    Q_ASSERT(project!=0 && "project pointer is 0!");

    // find the corresponding project item
    QTreeWidgetItem *topItem = findProjectItem(project);
    Q_ASSERT(topItem!=0 && "topItem pointer is 0!");

    // find the specified category item and return it
    for (int i=0; i<topItem->childCount(); i++) {
        if (topItem->child(i)->data(0,Id).toString() == fileCategoryId)
            return topItem->child(i);
    }

    return 0;
}


/* ===============================================================================================================*/
/**
  *
  */
QTreeWidgetItem* ProjectsTreeWidget::findFileItem(Project *project, const QString &fileCategoryId, int fileId)
{
    Q_ASSERT(project!=0 && "project pointer is 0!");

    // find the corresponding file category item
    QTreeWidgetItem *categoryItem = findFileCategoryItem(project,fileCategoryId);
    Q_ASSERT(categoryItem!=0 && "categoryItem pointer is 0!");

    int role;
    if (fileCategoryId == "Networks")       role = NetworkId;
    else if (fileCategoryId == "Settings")  role = AdjustmentSettingId;

    // find the specified category item and return it
    for (int i=0; i<categoryItem->childCount(); i++) {
        if (categoryItem->child(i)->data(0,role).toInt() == fileId)
            return categoryItem->child(i);
    }

    return 0;
}



/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::deleteProjectItem(Project *project)
{
    Q_ASSERT(project!=0 && "project pointer is 0!");

    // find the corresponding project item and delete it
    QTreeWidgetItem *projectItem = findProjectItem(project);
    Q_ASSERT(projectItem!=0 && "projectItem pointer is 0!");
    delete projectItem;
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::renameItem(Project *project, const QString &fileCategoryId, int fileId, const QString &newName)
{
    Q_ASSERT(project!=0 && "project pointer is 0!");
    // find the corresponding file item
    QTreeWidgetItem *item = findFileItem(project, fileCategoryId, fileId);
    Q_ASSERT(item!=0 && "file item pointer is 0!");
    item->setText(0,newName);
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::addProjectItem(Project *project)
{
    qDebug() << "ProjectsTreeWidget::addProjectItem() - START";

    QString projectName = project->getName();
    QString projectLocation = project->getLocation();

    // add project expandable item
    QTreeWidgetItem *itemProject = new QTreeWidgetItem(this);
    itemProject->setText(0,projectName);
    itemProject->setData(0,Id,"projectName");
    itemProject->setData(0,ProjectLocation,projectLocation);
    itemProject->setIcon(0,QIcon(":/images/icons/babieca-64.png"));
    itemProject->setExpanded(true);

    // add networks, solutions, settings expandable item and non expandable projectFile item,
    // set corresponding texts and icons
    QTreeWidgetItem *itemNetworks = new QTreeWidgetItem(itemProject);
    if (project->getType()=="SingleNetworkProject")
        itemNetworks->setText(0,QObject::tr("Network"));
    else
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

    qDebug() << "ProjectsTreeWidget::addProjectItem() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::setProjectItemActive(Project *project)
{
    qDebug() << "ProjectsTreeWidget::setProjectItemActive() - START";

    Q_ASSERT(project!=0 && "project pointer is 0!");

    // find the corresponding project item
    QTreeWidgetItem *projectItem = findProjectItem(project);
    Q_ASSERT(projectItem!=0 && "projectItem pointer is 0!");
    // change it to be active
    setCurrentItem(projectItem);

    qDebug() << "ProjectsTreeWidget::setProjectItemActive() - STOP";
}



void ProjectsTreeWidget::addFileItem(Project *project, const File &file, const QString &fileCategoryId, bool highlightOpened)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(findFileCategoryItem(project,fileCategoryId));
    Q_ASSERT(item!=0 && "item pointer is null!");

    if (fileCategoryId == "Networks") {
        item->setText(0,file.getName());
        item->setData(0,Id,"network");
        item->setData(0,NetworkId,file.getId());
        item->setIcon(0,QIcon(":/images/icons/network-32.png"));
    }

    if (fileCategoryId == "Solutions") {
        item->setText(0,file.getName());
        item->setData(0,Id,"network");
        item->setData(0,SolutionId,file.getId());
        QIcon icon;
        if (file.getFormat() == "xml")  icon.addFile(":/images/icons/xml-32.png");
        if (file.getFormat() == "txt")  icon.addFile(":/images/icons/txt-32.png");
        if (file.getFormat() == "html") icon.addFile(":/images/icons/html-32.png");
        item->setIcon(0,icon);
    }

    if (highlightOpened)
        setCurrentItem(item);

    if (file.getOpened()=="true")
        mw->openFile(file.getPath(),"network",project);
}


void ProjectsTreeWidget::addSettingItem(Project *project, const AdjustmentSetting &adjustmentSetting, bool highlightOpened)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(findFileCategoryItem(project,"Settings"));
    Q_ASSERT(item!=0 && "item pointer is null!");

    item->setText(0,adjustmentSetting.getName());
    item->setData(0,Id,"setting");
    item->setData(0,AdjustmentSettingId,adjustmentSetting.getId());
    item->setIcon(0,QIcon(":/images/icons/setting-32.png"));
    if (highlightOpened)
        setCurrentItem(item);
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::addFileItems(Project *project, bool highlightOpened)
{
    qDebug() << "ProjectsTreeWidget::addFileItems() - START";

    // add networks
    QList<File> &networks = project->getNetworks();
    for (int i=0; i<networks.size(); i++) {
        File &network = networks[i];
        if (network.isDisplayed())
            continue;

        addFileItem(project, network, "Networks", highlightOpened);
        network.setDisplayed(true);
    }

    // add settings
    QList<AdjustmentSetting> &adjustmentSettings = project->getAdjustmentSettings();
    for (int i=0; i<adjustmentSettings.size(); i++) {
        AdjustmentSetting &adjustmentSetting = adjustmentSettings[i];
        if (adjustmentSetting.isDisplayed())
            continue;

        addSettingItem(project, adjustmentSetting,highlightOpened);
        adjustmentSetting.setDisplayed(true);
    }

    qDebug() << "ProjectsTreeWidget::addFileItems() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::cancelAllHighlightings()
{    
    qDebug() << "ProjectsTreeWidget::cancelAllHighlightings() - START";

    if (topLevelItemCount()>0) {
        QFont font = topLevelItem(0)->font(0);
        font.setBold(false);

        // 1. generation
        for (int i=0; i<topLevelItemCount(); ++i) {
             //topLevelItem(i)->setSelected(false);
             topLevelItem(i)->setFont(0,font);

             // 2. generation
             if (topLevelItem(i)->childCount() != 0) {
                 for (int j=0; j<topLevelItem(i)->childCount(); ++j) {
                     //topLevelItem(i)->child(j)->setSelected(false);
                     topLevelItem(i)->child(j)->setFont(0,font);

                     // 3. generation
                     if (topLevelItem(i)->child(j)->childCount() != 0) {
                         for (int k=0; k<topLevelItem(i)->child(j)->childCount(); ++k) {
                             //topLevelItem(i)->child(j)->child(k)->setSelected(false);
                             topLevelItem(i)->child(j)->child(k)->setFont(0,font);
                         }
                     }
                 }
             }
         }
    }

    qDebug() << "ProjectsTreeWidget::cancelAllHighlightings() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::highlightActiveProject(QTreeWidgetItem *item)
{
    qDebug() << "ProjectsTreeWidget::highlightActiveProject() - START";

    // cancel all highlightings
    cancelAllHighlightings();

    // emphasize with bold letters
    QFont font = item->font(0);
    font.setBold(true);
    item->setFont(0,font);

    // set it expanded and selected
    //item->setSelected(true);

    qDebug() << "ProjectsTreeWidget::highlightActiveProject() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectsTreeWidget::collapseNonActiveProjects()
{
    qDebug() << "ProjectsTreeWidget::collapseNonActiveProjects() - START";

    // get the active project
    Project *project = prm->getActiveProject();

    // collapse all project that are not active
    for (int i=0; i<topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = topLevelItem(i);
        if (item->text(0)!=project->getName() || item->data(0,ProjectLocation)!=project->getLocation()) {
            item->setExpanded(false);
            for (int j=0; j<item->childCount(); ++j)
                item->child(j)->setExpanded(false);
        }
    }

    qDebug() << "ProjectsTreeWidget::collapseNonActiveProjects() - STOP";
}
