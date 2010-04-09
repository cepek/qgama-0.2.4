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

#include "newfilewizardpage2.h"
#include "../factory.h"


using namespace QGamaCore;


/**
  *
  */
NewFileWizardPage2::NewFileWizardPage2(QWidget *parent) :
    QWizardPage(parent),
    ui(new QGamaCore::Ui::NewFileWizardPage2),
    settings(Factory::getSettings()),
    prm(Factory::getProjectsManager())
{
    ui->setupUi(this);

    ui->label_Warning_Icon->setVisible(false);
    ui->label_Warning->setVisible(false);

    connect(ui->lineEdit_Name, SIGNAL(textChanged(QString)),this, SIGNAL(completeChanged()));
}


/**
  *
  */
NewFileWizardPage2::~NewFileWizardPage2()
{
    Factory::releaseSettings(settings);
    Factory::releaseProjectsManager(prm);

    delete ui;
}


/**
  *
  */
void NewFileWizardPage2::changeEvent(QEvent *e)
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
void NewFileWizardPage2::initializePage()
{
    // set new window title
    wizard()->setWindowTitle(tr("New "+settings->get("temporary/NFWPselectedFileType").toString().toAscii()));

    category = settings->get("temporary/NFWPselectedCategory").toString();
    fileType = settings->get("temporary/NFWPselectedFileType").toString();
    projectName = settings->get("temporary/NFWPselectedProjectName").toString();
    projectLocation = settings->get("temporary/NFWPselectedProjectLocation").toString();

    QString promotedName = tr("New"+fileType.remove(" ").toAscii());
    QString createdFile  = projectLocation + projectName + "/" + category + "/" + promotedName+".xml";

    ui->lineEdit_Name->setText(promotedName);
    ui->lineEdit_Project->setText(projectName);
    ui->lineEdit_Created_File->setText(createdFile);

    emit on_lineEdit_Name_textChanged(ui->lineEdit_Name->text());
}


/**
  *
  */
void NewFileWizardPage2::cleanupPage()
{
    wizard()->setWindowTitle(tr("New File"));
}


/**
  *
  */
void NewFileWizardPage2::on_lineEdit_Name_textChanged(QString text)
{
    ui->lineEdit_Created_File->setText(ui->lineEdit_Created_File->text().left(ui->lineEdit_Created_File->text().lastIndexOf("/")+1)+text+".xml");

    if (!isComplete()) {
        ui->label_Warning->setVisible(true);
        ui->label_Warning_Icon->setVisible(true);
    }
    else {
        ui->label_Warning->setVisible(false);
        ui->label_Warning_Icon->setVisible(false);
    }
}


/**
  *
  */
bool NewFileWizardPage2::isComplete() const
{
    return isNameValid(ui->lineEdit_Name->text());
}


/**
  *
  */
bool NewFileWizardPage2::isNameValid(const QString &name) const
{
    if (name.isEmpty()) {
        ui->label_Warning->setText(tr("File name could not be empty!"));
        ui->lineEdit_Created_File->setText(ui->lineEdit_Created_File->text().left(ui->lineEdit_Created_File->text().lastIndexOf("/")+1));
        return false;
    }
    else if (name.contains(QRegExp("[?:&*\"()|#%<> /',.!]"))) {
        ui->label_Warning->setText(tr("File name must not contain any of the following characters:\n[?:;&*\"()|#%<> /',.!]"));
        return false;
    }
    else if (QFile::exists(ui->lineEdit_Created_File->text())) {
        ui->label_Warning->setText(tr("File with the specified name already exists! Choose diferent name."));
        return false;
    }
    else {
        return true;
    }
}


/**
  *
  */
bool NewFileWizardPage2::validatePage()
{
    prm->newFile(ui->lineEdit_Created_File->text(),fileType);

    return true;
}
