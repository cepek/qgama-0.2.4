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

#include <QtGui>

#include <iostream>

#include "project.h"
#include "../factory.h"
#include "../main_window/mainwindow.h"
#include "../projects_manager/adjustmentsetting.h"

using namespace QGamaCore;


/* ===============================================================================================================*/
/**
  *
  */
Project::Project(const QString &name, const QString &location, const QString &projectFilePath) :
    acp(Factory::getApplicationComponentProvider())
{
    // initialize atributes
    this->name = name;
    this->location = location;
    this->projectFilePath = projectFilePath;
    this->active = true;

    // initialize id counters
    lastNetworksId  = 0;
    lastSettingsId  = 0;
    lastSolutionsId = 0;

    // load the project's xml
    loadXml();

    // set pointers to the widgets
    mw = acp->getMainWindow();
    ptw = acp->getProjectsTreeWidget();
}
    

/* ===============================================================================================================*/
/**
  *
  */
bool Project::loadXml()
{
    // open the project file
    QFile file(getProjectFilePath());
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical( 0, QObject::tr("Project file could not be opened!"), QObject::tr("Check out if it has set sufficient permissions to read from it."));
        return false;
    }

    // initialize the document content from it
    xml.setContent(&file);
    file.close();

    // get main project element
    QDomElement projectElement = xml.documentElement();
    setType(projectElement.attribute("type"));
    setName(projectElement.attribute("name"));

    // get category elements
    QDomNode categoryNode = projectElement.firstChild();
    while (!categoryNode.isNull()) {
        QDomElement categoryElement = categoryNode.toElement();

        // networks processing
        if (categoryElement.tagName() == "networks") {
            QDomNode networksNode = categoryElement.firstChild();
            while (!networksNode.isNull()) {
                QDomElement networksElement = networksNode.toElement();
                File network;
                network.setName(networksElement.attribute("name"));
                network.setPath(networksElement.attribute("path"));
                network.setId(networksElement.attribute("id").toInt());
                network.setOpened(networksElement.attribute("opened"));
                network.setFormat(networksElement.attribute("format"));
                network.setSettingsId(networksElement.attribute("settingsId").toInt());
                networks.append(network);
                if (network.getId()>lastNetworksId)
                    lastNetworksId = network.getId();
                networksNode = networksNode.nextSibling();
            }
        }

        // settings processing
        else if (categoryElement.tagName() == "settings") {
            QDomNode settingsNode = categoryElement.firstChild();
            while (!settingsNode.isNull()) {
                QDomElement settingsElement = settingsNode.toElement();
                AdjustmentSetting as;
                as.setAlgorithm(settingsElement.attribute("algorithm"));
                as.setAngles(settingsElement.attribute("angles"));
                as.setCovband(settingsElement.attribute("covband"));
                as.setEllipsoid(settingsElement.attribute("ellipsoid"));
                as.setEncoding(settingsElement.attribute("encoding"));
                as.setLanguage(settingsElement.attribute("language"));
                as.setLatitude(settingsElement.attribute("latitude"));
                as.setName(settingsElement.attribute("name"));
                as.setOutput(settingsElement.attribute("output"));
                as.setId(settingsElement.attribute("id").toInt());
                adjustmentSettings.append(as);
                if (as.getId()>lastSettingsId)
                    lastSettingsId = as.getId();
                settingsNode = settingsNode.nextSibling();
            }
        }

        categoryNode = categoryNode.nextSibling();
    }

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
Project::~Project()
{
    Factory::releaseApplicationComponentProvider(acp);
}


/* ===============================================================================================================*/
/**
  *
  */
void Project::updateProjectFileEntries()
{
    // have a look which networks from projects are still opened
    for (int i=0; i<networks.size(); i++) {
        // try to find the corresponding subwindow
        QMdiSubWindow *existing = acp->getMdiSubWindow(networks[i].getPath());

        // if still exists, set the network to be opened on another program's startup and vice versa
        if (existing)
            networks[i].setOpened("true");
        else
            networks[i].setOpened("false");
    }

    // update networks
    for (int i=0; i<networks.size(); i++)
        updateNetworkEntry(networks[i]);

    // update adjustment settings
    for (int i=0; i<adjustmentSettings.size(); i++)
        updateAdjustmentSettingEntry(adjustmentSettings[i]);

    // commit the change to the project file
    QFile file(getProjectFilePath());
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(0 , QObject::tr("Project file could not be opened!"), QObject::tr("Check out if it has set sufficient permissions to write to it."));
        return;
    }

    // "commit" it to the file
    QTextStream ts(&file);
    ts << xml.toString();

    // close the file
    file.close();
}


/* ===============================================================================================================*/
/**
  *
  */
AdjustmentSetting* Project::getAdjustmentSetting(int id)
{
    // return adjustment setting with the specified id if found, otherwise return 0
    for (int i=0; i<adjustmentSettings.size(); i++) {
        if (adjustmentSettings[i].getId()==id)
            return &adjustmentSettings[i];
    }
    return 0;
}


/* ===============================================================================================================*/
/**
  *
  */
File* Project::getNetwork(int id)
{
    // return network with the specified id if found, otherwise return 0
    for (int i=0; i<networks.size(); i++) {
        if (networks[i].getId()==id)
            return &networks[i];
    }
    return 0;
}


/* ===============================================================================================================*/
/**
  *
  */
void Project::updateAdjustmentSettingEntry(const AdjustmentSetting &as)
{
    // get main project element
    QDomElement projectElement = xml.documentElement();

    // get category elements
    QDomNode categoryNode = projectElement.firstChild();
    while (!categoryNode.isNull()) {
        QDomElement categoryElement = categoryNode.toElement();

        if (categoryElement.tagName() == "settings") {
            QDomNode settingsNode = categoryElement.firstChild();
            while (!settingsNode.isNull()) {
                QDomElement settingsElement = settingsNode.toElement();

                if (settingsElement.attribute("id") == QString::number(as.getId())) {
                    // update settings parameters
                    settingsElement.setAttribute("algorithm", as.getAlgorithm());
                    settingsElement.setAttribute("angles", as.getAngles());
                    settingsElement.setAttribute("covband", as.getCovband());
                    settingsElement.setAttribute("ellipsoid", as.getEllipsoid());
                    settingsElement.setAttribute("encoding", as.getEncoding());
                    settingsElement.setAttribute("language", as.getLanguage());
                    settingsElement.setAttribute("latitude", as.getLatitude());
                    settingsElement.setAttribute("name", as.getName());
                    settingsElement.setAttribute("output", as.getOutput());
                }

                settingsNode = settingsNode.nextSibling();
            }
        }

        categoryNode = categoryNode.nextSibling();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void Project::updateNetworkEntry(const File &network)
{
    // get main project element
    QDomElement projectElement = xml.documentElement();

    // get category elements
    QDomNode categoryNode = projectElement.firstChild();
    while (!categoryNode.isNull()) {
        QDomElement categoryElement = categoryNode.toElement();

        if (categoryElement.tagName() == "networks") {
            QDomNode networksNode = categoryElement.firstChild();
            while (!networksNode.isNull()) {
                QDomElement networksElement = networksNode.toElement();

                if (networksElement.attribute("id") == QString::number(network.getId())) {
                    // update network parameters
                    networksElement.setAttribute("name", network.getName());
                    networksElement.setAttribute("path",network.getPath());
                    networksElement.setAttribute("opened",network.getOpened());
                    networksElement.setAttribute("settingsId", network.getSettingsId());
                }

                networksNode = networksNode.nextSibling();
            }
        }

        categoryNode = categoryNode.nextSibling();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
bool Project::newNetwork(const QString &filePath)
{
    // create the file, inform about potencial problems
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical( 0, QObject::tr("File could not be created!"), QObject::tr("Probably there were insufficient permisions to create the file in the specified directory."));
        return false;
    }

    // close the file
    file.close();

    // add it to the list of networks, create the corresponding xml entry and display it in projectstreewidget
    File network;
    network.setPath(filePath);
    network.setName(filePath.split("/").last());
    network.setOpened("true");
    network.setFormat("xml");
    network.setSettingsId(1);
    network.setId(++lastNetworksId);
    networks.append(network);
    createNetworkEntry(network);
    ptw->addFileItems(this);

    // open the network in subwindow
    mw->openFile(filePath,"network",this);

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
bool Project::importNetwork(const QString &filePath)
{
    // get the file name from path
    QString fileName = filePath.split("/").last();

    // set the new file path
    QString newFilePath;
    if (type=="SingleNetworkProject")
        newFilePath=location+name+"/Network/"+fileName;
    else
        newFilePath=location+name+"/Networks/"+fileName;

    // copy the file into the project
    if (!QFile::copy(filePath, newFilePath)) {
        QMessageBox::critical( 0, QObject::tr("File could not be created!"), QObject::tr("Probably there were insufficient permisions to create the file in the specified directory."));
        return false;
    }

    // add it to the list of networks, create the correspondinf xml entry and display it in projectstreewidget
    File network;
    network.setPath(newFilePath);
    network.setName(fileName);
    network.setOpened("true");
    network.setFormat("xml");
    network.setSettingsId(1);
    network.setId(++lastNetworksId);
    networks.append(network);
    createNetworkEntry(network);
    ptw->addFileItems(this);

    // open the network in subwindow
    mw->openFile(newFilePath,"network",this);

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
bool Project::linkNetwork(const QString &filePath)
{
    // add it to the list of networks, create the corresponding xml entry and display it in projectstreewidget
    File network;
    network.setPath(filePath);
    network.setName(filePath.split("/").last());
    network.setOpened("true");
    network.setFormat("xml");
    network.setSettingsId(1);
    network.setId(++lastNetworksId);
    networks.append(network);
    createNetworkEntry(network);
    ptw->addFileItems(this);

    // open the network in subwindow
    mw->openFile(filePath,"network",this);

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
bool Project::createProjectStructure(const QString &type, const QString &name, const QString &location)
{
    if (type == "SingleNetworkProject")
        return createSingleNetworkProjectStructure(type, name, location);

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
bool Project::createSingleNetworkProjectStructure(const QString &type, const QString &name, const QString &location)
{
    // get the project home directory
    QDir directory(location);

    // create it if doesn't exist
    if (!directory.exists(directory.absolutePath())) {
        if (!directory.mkpath(directory.path())) {
            QMessageBox::critical( 0, QObject::tr("Project could not be created!"), QObject::tr("Probably there were insufficient permisions to create the project structure in the specified directory."));
            return false;
        }
    }

    // create the project structure, inform about potencial problems
    if (!directory.mkdir(name) || !directory.mkpath(name+"/Network") || !directory.mkpath(name+"/Solutions")) {
        QMessageBox::critical( 0, QObject::tr("Project could not be created!"), QObject::tr("Probably there were insufficient permisions to create the project structure in the specified directory."));
        return false;
    }

    // create project file, inform about potencial problems
    QFile file(directory.absolutePath()+"/"+name+"/"+name+".qgp");
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical( 0, QObject::tr("Project could not be created!"), QObject::tr("Probably there were insufficient permisions to create the project structure in the specified directory."));
        return false;
    }

    // initialize its xml content
    QDomDocument projectDocument("qgamaproject");

    // qgamaprojectfile
    QDomElement projectElement = projectDocument.createElement("qgamaprojectfile");
    projectElement.setAttribute("name",name);
    projectElement.setAttribute("type",type);
    projectDocument.appendChild(projectElement);

    // networks category
    QDomElement networksElement;
    networksElement = projectDocument.createElement("networks");
    projectElement.appendChild(networksElement);

    // settings category
    QDomElement settingsElement = projectDocument.createElement("settings");
    projectElement.appendChild(settingsElement);

    // default setting
    QDomElement defaultSettingElement = projectDocument.createElement("setting");
    defaultSettingElement.setAttribute("algorithm","svd");
    QStringList languages;
    languages.append("en"); languages.append("ca"); languages.append("cz"); languages.append("du");
    languages.append("fi"); languages.append("fr"); languages.append("hu"); languages.append("ru");
    languages.append("ua");
    QString appLang = QLocale::system().name().right(2).toLower();
    QString appLang2 = QLocale::system().name().left(2).toLower();
    QString defLang;
    if (languages.contains(appLang))
        defLang = languages.value(languages.indexOf(appLang));
    else if (languages.contains(appLang2))
        defLang = languages.value(languages.indexOf(appLang2));
    else
        defLang = "en";
    defaultSettingElement.setAttribute("language",defLang);
    defaultSettingElement.setAttribute("encoding","utf-8");
    defaultSettingElement.setAttribute("angles","400");
    defaultSettingElement.setAttribute("latitude","");
    defaultSettingElement.setAttribute("ellipsoid","");
    defaultSettingElement.setAttribute("output","txt|xml|html");
    defaultSettingElement.setAttribute("covband","-1");
    defaultSettingElement.setAttribute("name","Default");
    defaultSettingElement.setAttribute("id",1);
    settingsElement.appendChild(defaultSettingElement);

    QDomElement solutionsElement = projectDocument.createElement("solutions");
    projectElement.appendChild(solutionsElement);

    // write into file
    QTextStream ts(&file);
    ts << projectDocument.toString();

    // close the file
    file.close();

    // if no error occured, return true
    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
void Project::createNetworkEntry(const File &network)
{
    // get main project element
    QDomElement projectElement = xml.documentElement();

    // get category elements
    QDomNode categoryNode = projectElement.firstChild();
    while (!categoryNode.isNull()) {
        QDomElement categoryElement = categoryNode.toElement();

        // add new network
        if (categoryElement.tagName() == "networks") {
            QDomElement networkElement = xml.createElement("network");
            networkElement.setAttribute("name", network.getName());
            networkElement.setAttribute("path", network.getPath());
            networkElement.setAttribute("opened", network.getOpened());
            networkElement.setAttribute("settingsId", network.getSettingsId());
            networkElement.setAttribute("format", network.getFormat());
            networkElement.setAttribute("id", network.getId());
            categoryElement.appendChild(networkElement);
        }

        categoryNode =  categoryNode.nextSibling();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void Project::createAdjustmentSettingEntry(const AdjustmentSetting &as)
{
    // get main project element
    QDomElement projectElement = xml.documentElement();

    // get category elements
    QDomNode categoryNode = projectElement.firstChild();
    while (!categoryNode.isNull()) {
        QDomElement categoryElement = categoryNode.toElement();

        // add new setting
        if (categoryElement.tagName() == "settings") {
            QDomElement settingElement = xml.createElement("setting");
            settingElement.setAttribute("id", as.getId());
            settingElement.setAttribute("algorithm", as.getAlgorithm());
            settingElement.setAttribute("angles", as.getAngles());
            settingElement.setAttribute("covband", as.getCovband());
            settingElement.setAttribute("ellipsoid", as.getEllipsoid());
            settingElement.setAttribute("encoding", as.getEncoding());
            settingElement.setAttribute("language", as.getLanguage());
            settingElement.setAttribute("latitude", as.getLatitude());
            settingElement.setAttribute("name", as.getName());
            settingElement.setAttribute("output", as.getOutput());
            categoryElement.appendChild(settingElement);
        }

        categoryNode =  categoryNode.nextSibling();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
bool Project::newAdjustmentSetting(AdjustmentSetting &as)
{
    // add it to the list of adjustment settings, create the corresponding xml entry and display it in projectstreewidget
    adjustmentSettings.append(as);
    createAdjustmentSettingEntry(as);
    ptw->addFileItems(this);

    return true;
}
