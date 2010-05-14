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

#include "newnetworkwizardpage2.h"
#include "../factory.h"


using namespace QGamaCore;


/* ===============================================================================================================*/
/**
  *
  */
NewNetworkWizardPage2::NewNetworkWizardPage2(QWidget *parent) :
    QWizardPage(parent),
    ui(new QGamaCore::Ui::NewNetworkWizardPage2),
    settings(Factory::getSettings()),
    prm(Factory::getProjectsManager())
{
    ui->setupUi(this);

    connect(ui->lineEdit_Name, SIGNAL(textChanged(QString)),this, SIGNAL(completeChanged()));
}


/* ===============================================================================================================*/
/**
  *
  */
NewNetworkWizardPage2::~NewNetworkWizardPage2()
{
    Factory::releaseSettings(settings);
    Factory::releaseProjectsManager(prm);

    delete ui;
}


/* ===============================================================================================================*/
/**
  *
  */
void NewNetworkWizardPage2::changeEvent(QEvent *e)
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


/* ===============================================================================================================*/
/**
  *
  */
void NewNetworkWizardPage2::initializePage()
{
    ui->label_Warning_Icon->setVisible(false);
    ui->label_Warning->setVisible(false);

    networkType = settings->get("temporary/NFWPselectedNetworkType").toString();
    projectName = settings->get("temporary/NFWPselectedProjectName").toString();
    projectLocation = settings->get("temporary/NFWPselectedProjectLocation").toString();
    projectType = settings->get("temporary/NFWPselectedProjectType").toString();

    // set new window title
    wizard()->setWindowTitle(tr("Create New Network"));

    QString promotedName = tr("NewNetwork");
    QString createdNetwork;

    if (projectType=="SingleNetworkProject")
        createdNetwork = projectLocation + projectName + "/Network/" + promotedName+".xml";
    else
        createdNetwork = projectLocation + projectName + "/Networks/" + promotedName+".xml";

    ui->lineEdit_Name->setText(promotedName);
    ui->lineEdit_Project->setText(projectName);
    ui->lineEdit_Created_Network->setText(createdNetwork);

    emit on_lineEdit_Name_textChanged(ui->lineEdit_Name->text());
}


/* ===============================================================================================================*/
/**
  *
  */
void NewNetworkWizardPage2::cleanupPage()
{
    wizard()->setWindowTitle(tr("New Network"));
}


/* ===============================================================================================================*/
/**
  *
  */
void NewNetworkWizardPage2::on_lineEdit_Name_textChanged(QString text)
{
    ui->lineEdit_Created_Network->setText(ui->lineEdit_Created_Network->text().left(ui->lineEdit_Created_Network->text().lastIndexOf("/")+1)+text+".xml");

    if (!isComplete()) {
        ui->label_Warning->setVisible(true);
        ui->label_Warning_Icon->setVisible(true);
    }
    else {
        ui->label_Warning->setVisible(false);
        ui->label_Warning_Icon->setVisible(false);
    }
}


/* ===============================================================================================================*/
/**
  *
  */
bool NewNetworkWizardPage2::isComplete() const
{
    return isNameValid(ui->lineEdit_Name->text());
}


/* ===============================================================================================================*/
/**
  *
  */
bool NewNetworkWizardPage2::isNameValid(const QString &name) const
{
    if (name.isEmpty()) {
        ui->label_Warning->setText(tr("Network name could not be empty!"));
        ui->lineEdit_Created_Network->setText(ui->lineEdit_Created_Network->text().left(ui->lineEdit_Created_Network->text().lastIndexOf("/")+1));
        return false;
    }
    else if (name.contains(QRegExp("[?:&*\"()|#%<> /',.!]"))) {
        ui->label_Warning->setText(tr("Network name must not contain any of the following characters:\n[?:;&*\"()|#%<> /',.!]"));
        return false;
    }
    else if (QFile::exists(ui->lineEdit_Created_Network->text())) {
        ui->label_Warning->setText(tr("Network with the specified name already exists! Choose diferent name."));
        return false;
    }
    else {
        return true;
    }
}


/* ===============================================================================================================*/
/**
  *
  */
bool NewNetworkWizardPage2::validatePage()
{
    QString filePath = ui->lineEdit_Created_Network->text();
    prm->getProject(projectName,projectLocation)->newNetwork(filePath);

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
int NewNetworkWizardPage2::nextId() const
{
    return -1;
}
