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

#include "newfilewizardpage.h"
#include "../factory.h"
#include "../projects_manager/project.h"
#include "newfilewizard.h"

using namespace QGamaCore;


enum { Id=32, Description=33, Location=34, ProjectFilePath=35 };


/**
  *
  */
NewFileWizardPage::NewFileWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new QGamaCore::Ui::NewFileWizardPage),
    prm(Factory::getProjectsManager()),
    settings(Factory::getSettings())
{
    ui->setupUi(this);

    // fill the projects combobox and select the active project
    QList<Project*> projects = prm->getProjectsList();
    QStringList activeProject = settings->get("projects/activeProject").toStringList();
    int index = 0;
    for (int i=0; i<projects.size(); i++) {
        ui->comboBox_Project->addItem(projects[i]->getName());
        ui->comboBox_Project->setItemData(i,projects[i]->getLocation(),Location);
        ui->comboBox_Project->setItemData(i,projects[i]->getProjectFilePath(),ProjectFilePath);
        if (projects[i]->getName()==activeProject.value(0) && projects[i]->getLocation()==activeProject.value(1)) {
            index = i;
        }
    }
    ui->comboBox_Project->setCurrentIndex(index);

    // set the sorting of items
    ui->listWidget_Categories->setSortingEnabled(true);
    ui->listWidget_Categories->sortItems(Qt::AscendingOrder);

    // add items to Categories list
    QListWidgetItem *networkItem = new QListWidgetItem(tr("Networks"), ui->listWidget_Categories);
    networkItem->setData(Id,"Networks");
    networkItem->setIcon(QIcon(":/images/icons/standardbutton-open-16.png"));
    QListWidgetItem *settingsItem = new QListWidgetItem(tr("Settings"), ui->listWidget_Categories);
    settingsItem->setData(Id,"Settings");
    settingsItem->setIcon(QIcon(":/images/icons/standardbutton-open-16.png"));

    // add items to File Types list
    QListWidgetItem *oneDimensionNetworkItem = new QListWidgetItem(tr("Create new network"), ui->listWidget_File_Types);
    oneDimensionNetworkItem->setData(Id,"CreateNewNetwork");
    oneDimensionNetworkItem->setData(Description,tr("Creates a new empty network's xml file in the project."));
    oneDimensionNetworkItem->setIcon(QIcon(":/images/icons/network-16.png"));
    QListWidgetItem *twoDimensionsNetworkItem = new QListWidgetItem(tr("Import existing network"), ui->listWidget_File_Types);
    twoDimensionsNetworkItem->setData(Id,"ImportExistingNetwork");
    twoDimensionsNetworkItem->setData(Description,"Copies existing network's xml file into the project.");
    twoDimensionsNetworkItem->setIcon(QIcon(":/images/icons/network-16.png"));
    QListWidgetItem *threeDimensionsNetworkItem = new QListWidgetItem(tr("Link existing network"), ui->listWidget_File_Types);
    threeDimensionsNetworkItem->setData(Id,"LinkExistingNetwork");
    threeDimensionsNetworkItem->setData(Description,"Adds the link to the network's xml file into the project.");
    threeDimensionsNetworkItem->setIcon(QIcon(":/images/icons/network-16.png"));
    QListWidgetItem *settingItem = new QListWidgetItem(tr("Setting"), ui->listWidget_File_Types);
    settingItem->setData(Id,"Setting");
    settingItem->setData(Description,"Add a new setting of computational parameters into the project.");
    settingItem->setIcon(QIcon(":/images/icons/setting-16.png"));

    // set the first item as selected
    ui->listWidget_Categories->setCurrentRow(0);
}


/**
  *
  */
NewFileWizardPage::~NewFileWizardPage()
{
    Factory::releaseProjectsManager(prm);
    Factory::releaseSettings(settings);

    delete ui;
}


/**
  *
  */
void NewFileWizardPage::changeEvent(QEvent *e)
{
    QWizardPage::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


/**
  *
  */
void NewFileWizardPage::on_listWidget_Categories_currentRowChanged(int currentRow)
{
    int count = 0;
    if (ui->listWidget_Categories->item(currentRow)->data(Id).toString()=="Networks") {
        for (int i=0; i<ui->listWidget_File_Types->count(); i++) {
            if ( ui->listWidget_File_Types->item(i)->data(Id).toString()=="CreateNewNetwork" ||
                 ui->listWidget_File_Types->item(i)->data(Id).toString()=="ImportExistingNetwork" ||
                 ui->listWidget_File_Types->item(i)->data(Id).toString()=="LinkExistingNetwork" ) {
                ui->listWidget_File_Types->item(i)->setHidden(false);
                count++;
                if (count == 1)
                    ui->listWidget_File_Types->setCurrentRow(i);
            }
            else {
                ui->listWidget_File_Types->item(i)->setHidden(true);
            }
        }
    }
    else if (ui->listWidget_Categories->item(currentRow)->data(Id).toString()=="Settings") {
        for (int i=0; i<ui->listWidget_File_Types->count(); i++) {
            if (ui->listWidget_File_Types->item(i)->data(Id).toString()=="Setting") {
                ui->listWidget_File_Types->item(i)->setHidden(false);
                ui->listWidget_File_Types->setCurrentRow(i);
            }
            else {
                ui->listWidget_File_Types->item(i)->setHidden(true);
            }
        }
    }
}


/**
  *
  */
void NewFileWizardPage::on_listWidget_File_Types_currentRowChanged(int currentRow)
{
    ui->textBrowser_Description->setText(ui->listWidget_File_Types->item(currentRow)->data(Description).toString());
}


/**
  *
  */
int NewFileWizardPage::nextId() const
{
    return NewFileWizard::Page_Select_Name_And_Location;
}


/**
  *
  */
bool NewFileWizardPage::validatePage()
{
    settings->set("temporary/NFWPselectedCategory",ui->listWidget_Categories->currentItem()->data(Id).toString());
    settings->set("temporary/NFWPselectedFileType",ui->listWidget_File_Types->currentItem()->data(Id).toString());
    settings->set("temporary/NFWPselectedProjectName",ui->comboBox_Project->currentText());
    settings->set("temporary/NFWPselectedProjectLocation",ui->comboBox_Project->itemData(ui->comboBox_Project->currentIndex(),Location));
    settings->set("temporary/NFWPselectedProjectFilePath",ui->comboBox_Project->itemData(ui->comboBox_Project->currentIndex(),ProjectFilePath));

    return true;
}
