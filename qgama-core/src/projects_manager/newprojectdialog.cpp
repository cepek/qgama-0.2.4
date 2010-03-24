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


#include <QDir>
#include <QFileDialog>
#include <QPushButton>

#include "newprojectdialog.h"
#include "project.h"
#include "projectsmanagerimpl.h"

#include <iostream>

using namespace QGamaCore;


/**
  *
  */
NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog),
    prm(ProjectsManagerImpl::instance())
{
    ui->setupUi(this);

    location.setPath(location.home().absolutePath()+"/QGamaProjects");

    int num = 1;
    QStringList dirNames = location.entryList(QDir::Dirs);
    QList<int> numbers;
    for (QStringList::iterator i=dirNames.begin(); i!=dirNames.end(); ++i) {
        if (i->startsWith("QGamaProject") && (*i)!="QGamaProject") {
            numbers.append(i->remove(0,12).toInt());
        }
    }
    qSort(numbers.begin(),numbers.end());
    for (QList<int>::iterator i=numbers.begin(); i!=numbers.end(); ++i) {
        if (*i == num)
            ++num;
        else
            break;
    }

    ui->lineEdit_Project_Name->setText("QGamaProject"+QString::number(num));
    ui->lineEdit_Project_Folder->setText(location.absolutePath()+"/"+ui->lineEdit_Project_Name->text());
    ui->lineEdit_Project_Location->setText(location.absolutePath());
    ui->lineEdit_Project_Folder->setMinimumWidth(ui->lineEdit_Project_Folder->text().length()*8);
    ui->label_Warning->setVisible(false);

    folder.setPath(ui->lineEdit_Project_Folder->text());

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(createProject()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


/**
  *
  */
NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}


/**
  *
  */
void NewProjectDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
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
void NewProjectDialog::on_lineEdit_Project_Name_textChanged(QString)
{
    ui->lineEdit_Project_Folder->setText(ui->lineEdit_Project_Location->text()+"/"+ui->lineEdit_Project_Name->text());
    folder.setPath(ui->lineEdit_Project_Folder->text());

    if (ui->lineEdit_Project_Name->text().isEmpty()) {
        ui->label_Warning->setText(tr("Project name have to be specified!"));
        ui->label_Warning->setStyleSheet("background-color: yellow");
        ui->label_Warning->setVisible(true);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else if (ui->lineEdit_Project_Name->text().contains(QRegExp("[?:&*\"|#%<> /]"))) {
        ui->label_Warning->setText(tr("Project name must not contain any of the following characters '?:&*\"|#%<> /'!"));
        ui->label_Warning->setStyleSheet("background-color: red");
        ui->label_Warning->setVisible(true);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else if (folder.exists()) {
        ui->label_Warning->setText(tr("A project with the specified name already exists!"));
        ui->label_Warning->setStyleSheet("background-color: yellow");
        ui->label_Warning->setVisible(true);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else {
        ui->label_Warning->setVisible(false);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}


/**
  *
  */
void NewProjectDialog::on_toolButton_Browse_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"), location.absolutePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_Project_Location->setText(directory);

    location.setPath(directory);
}


/**
  *
  */
void NewProjectDialog::createProject()
{
    prm.newProject(ui->lineEdit_Project_Name->text(), ui->lineEdit_Project_Location->text());
    prm.openProject(ui->lineEdit_Project_Folder->text()+"/"+ui->lineEdit_Project_Name->text().toLower()+".qgp");

    accept();
}
