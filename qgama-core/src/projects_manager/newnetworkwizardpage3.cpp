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

#include "newnetworkwizardpage3.h"
#include "../factory.h"

using namespace QGamaCore;


/* ===============================================================================================================*/
/**
  *
  */
NewNetworkWizardPage3::NewNetworkWizardPage3(QWidget *parent) :
    QWizardPage(parent),
    ui(new QGamaCore::Ui::NewNetworkWizardPage3),
    settings(Factory::getSettings()),
    prm(Factory::getProjectsManager())
{
    ui->setupUi(this);

    connect(ui->lineEdit_Network, SIGNAL(textChanged(QString)),this, SIGNAL(completeChanged()));
}


/* ===============================================================================================================*/
/**
  *
  */
NewNetworkWizardPage3::~NewNetworkWizardPage3()
{
    Factory::releaseProjectsManager(prm);
    Factory::releaseSettings(settings);

    delete ui;
}


/* ===============================================================================================================*/
/**
  *
  */
void NewNetworkWizardPage3::changeEvent(QEvent *e)
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
void NewNetworkWizardPage3::initializePage()
{
    ui->label_Warning_Icon->setVisible(false);
    ui->label_Warning->setVisible(false);

    networkType = settings->get("temporary/NFWPselectedNetworkType").toString();
    projectName = settings->get("temporary/NFWPselectedProjectName").toString();
    projectLocation = settings->get("temporary/NFWPselectedProjectLocation").toString();
    projectType = settings->get("temporary/NFWPselectedProjectType").toString();

    // set corresponding titles
    if (networkType == "ImportExistingNetwork") {
        wizard()->setWindowTitle(tr("Import Existing Network into the project"));
    }
    else if (networkType == "LinkExistingNetwork") {
        wizard()->setWindowTitle(tr("Link Existing Network into the project"));
    }

    ui->lineEdit_Project->setText(projectName);

    emit on_lineEdit_Network_textChanged(ui->lineEdit_Network->text());
}


/* ===============================================================================================================*/
/**
  *
  */
void NewNetworkWizardPage3::cleanupPage()
{
    wizard()->setWindowTitle(tr("New Network"));
}


/* ===============================================================================================================*/
/**
  *
  */
void NewNetworkWizardPage3::on_lineEdit_Network_textChanged(QString text)
{
    Q_UNUSED(text);

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
bool NewNetworkWizardPage3::isComplete() const
{
    return isNameValid(ui->lineEdit_Network->text());
}


/* ===============================================================================================================*/
/**
  *
  */
bool NewNetworkWizardPage3::isNameValid(const QString &networkPath) const
{
    QString path;
    if (projectType=="SingleNetworkProject")
        path = projectLocation+projectName+"/Network/"+networkPath.split("/").last();
    else
        path = projectLocation+projectName+"/Networks/"+networkPath.split("/").last();

    if (networkPath.isEmpty()) {
        ui->label_Warning->setText(tr("Network path could not be empty!"));
        return false;
    }
    else if (QFile::exists(path)) {
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
bool NewNetworkWizardPage3::validatePage()
{
    QString filePath = ui->lineEdit_Network->text();

    // do corresponding actions
    if (networkType == "ImportExistingNetwork")
        prm->getProject(projectName,projectLocation)->importNetwork(filePath);
    else if (networkType == "LinkExistingNetwork")
        prm->getProject(projectName,projectLocation)->linkNetwork(filePath);

    return true;
}


/* ===============================================================================================================*/
/**
  *
  */
int NewNetworkWizardPage3::nextId() const
{
    return -1;
}


/* ===============================================================================================================*/
/**
  *
  */
void QGamaCore::NewNetworkWizardPage3::on_toolButton_clicked()
{
    QDir dir;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Specify the network which should be added to the project"), dir.home().absolutePath()+"/QGamaProjects", tr("QGama Network Files (*.xml *.gkf)"));
    ui->lineEdit_Network->setText(fileName);
    update();
}
