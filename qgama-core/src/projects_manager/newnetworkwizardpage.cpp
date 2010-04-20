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

#include "newnetworkwizardpage.h"
#include "../factory.h"
#include "../projects_manager/project.h"
#include "newnetworkwizard.h"

using namespace QGamaCore;


/**
  *
  */
NewNetworkWizardPage::NewNetworkWizardPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new QGamaCore::Ui::NewNetworkWizardPage),
    prm(Factory::getProjectsManager()),
    settings(Factory::getSettings())
{
    ui->setupUi(this);
}


/**
  *
  */
NewNetworkWizardPage::~NewNetworkWizardPage()
{
    Factory::releaseProjectsManager(prm);
    Factory::releaseSettings(settings);

    delete ui;
}


/**
  *
  */
void NewNetworkWizardPage::initializePage()
{
    // fill the projects combobox and select the active project
    QList<Project*> projects = prm->getProjectsList();
    QStringList activeProject = settings->get("projects/activeProject").toStringList();
    int index = 0;
    int activeIndex = 0;
    for (int i=0; i<projects.size(); i++) {
        if (projects[i]->getType()=="SingleNetworkProject" && projects[i]->getNetworks().size()==1)
            continue;
        else {
            ui->comboBox_Project->addItem(projects[i]->getName());
            ui->comboBox_Project->setItemData(index,projects[i]->getLocation(),Location);
            ui->comboBox_Project->setItemData(index,projects[i]->getProjectFilePath(),ProjectFilePath);
            ui->comboBox_Project->setItemData(index,projects[i]->getType(),ProjectType);

            if (projects[i]->getName()==activeProject.value(0) && projects[i]->getLocation()==activeProject.value(1)) {
                activeIndex = index;
            }
            index++;
        }
    }
    ui->comboBox_Project->setCurrentIndex(activeIndex);

    // set the sorting of items
    ui->listWidget_Network_Types->setSortingEnabled(true);
    ui->listWidget_Network_Types->sortItems(Qt::AscendingOrder);

    // add items to File Types list
    QListWidgetItem *oneDimensionNetworkItem = new QListWidgetItem(tr("Create new network"), ui->listWidget_Network_Types);
    oneDimensionNetworkItem->setData(Id,"CreateNewNetwork");
    oneDimensionNetworkItem->setData(Description,tr("Creates a new empty network's XML file in the project."));
    oneDimensionNetworkItem->setIcon(QIcon(":/images/icons/network-16.png"));
    QListWidgetItem *twoDimensionsNetworkItem = new QListWidgetItem(tr("Import existing network"), ui->listWidget_Network_Types);
    twoDimensionsNetworkItem->setData(Id,"ImportExistingNetwork");
    twoDimensionsNetworkItem->setData(Description,"Copies existing network's XML file into the project.");
    twoDimensionsNetworkItem->setIcon(QIcon(":/images/icons/network-16.png"));
    QListWidgetItem *threeDimensionsNetworkItem = new QListWidgetItem(tr("Link existing network"), ui->listWidget_Network_Types);
    threeDimensionsNetworkItem->setData(Id,"LinkExistingNetwork");
    threeDimensionsNetworkItem->setData(Description,"Adds the link to the network's XML file into the project.");
    threeDimensionsNetworkItem->setIcon(QIcon(":/images/icons/network-16.png"));

    // set the first item as selected
    ui->listWidget_Network_Types->setCurrentRow(0);
}


/**
  *
  */
void NewNetworkWizardPage::changeEvent(QEvent *e)
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
void NewNetworkWizardPage::on_listWidget_Network_Types_currentRowChanged(int currentRow)
{
    ui->textBrowser_Description->setText(ui->listWidget_Network_Types->item(currentRow)->data(Description).toString());
}


/**
  *
  */
int NewNetworkWizardPage::nextId() const
{
    if (ui->listWidget_Network_Types->currentItem()->data(Id).toString()=="CreateNewNetwork")
        return NewNetworkWizard::Page_Create_New_Network;
    else if (ui->listWidget_Network_Types->currentItem()->data(Id).toString()=="LinkExistingNetwork" ||
             ui->listWidget_Network_Types->currentItem()->data(Id).toString()=="ImportExistingNetwork")
        return NewNetworkWizard::Page_Import_Link_Existing_Network;
}


/**
  *
  */
bool NewNetworkWizardPage::validatePage()
{
    settings->set("temporary/NFWPselectedNetworkType",ui->listWidget_Network_Types->currentItem()->data(Id).toString());
    settings->set("temporary/NFWPselectedProjectName",ui->comboBox_Project->currentText());
    settings->set("temporary/NFWPselectedProjectLocation",ui->comboBox_Project->itemData(ui->comboBox_Project->currentIndex(),Location));
    settings->set("temporary/NFWPselectedProjectFilePath",ui->comboBox_Project->itemData(ui->comboBox_Project->currentIndex(),ProjectFilePath));
    settings->set("temporary/NFWPselectedProjectType",ui->comboBox_Project->itemData(ui->comboBox_Project->currentIndex(),ProjectType));

    return true;
}
