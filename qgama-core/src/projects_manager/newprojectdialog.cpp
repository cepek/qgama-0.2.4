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

#include "newprojectdialog.h"
#include "project.h"
#include "../factory.h"

#include <iostream>

using namespace QGamaCore;


/**
  *
  */
NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog),
    prm(Factory::getProjectsManager())
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
    ui->lineEdit_Project_Location->setText(location.absolutePath());
    ui->lineEdit_Project_Location->setMinimumWidth(ui->lineEdit_Project_Location->text().length()*8);

    ui->comboBox_Project_Type->addItem(QIcon(":/images/icons/babieca-64.png")," "+tr("Single Network Project"));
    ui->comboBox_Project_Type->setItemData(0,"SingleNetworkProject",Id);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(createProject()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


/**
  *
  */
NewProjectDialog::~NewProjectDialog()
{
    Factory::releaseProjectsManager(prm);
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
void NewProjectDialog::on_lineEdit_Project_Name_textChanged(QString text)
{   
    folder.setPath(location.absolutePath()+"/"+ui->lineEdit_Project_Name->text());

    if (!isNameValid(text)) {
        ui->label_Warning->setVisible(true);
        ui->label_Warning_Icon->setVisible(true);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else {
        ui->label_Warning->setVisible(false);
        ui->label_Warning_Icon->setVisible(false);
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}


/**
  *
  */
void NewProjectDialog::on_toolButton_Browse_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"), location.absolutePath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!directory.isEmpty()) {
        ui->lineEdit_Project_Location->setText(directory);

        location.setPath(directory);
        folder.setPath(directory+"/"+ui->lineEdit_Project_Name->text());
    }
}


/**
  *
  */
void NewProjectDialog::createProject()
{
    QString projectType = ui->comboBox_Project_Type->itemData(ui->comboBox_Project_Type->currentIndex(),Id).toString();
    QString projectName = ui->lineEdit_Project_Name->text();
    QString projectLocation = ui->lineEdit_Project_Location->text();
    QString projectFilePath = folder.absolutePath()+"/"+projectName+".qgp";

    prm->newProject(projectType, projectName, projectLocation);
    std::cout << "PROJEKT VYTVOREN" << std::endl;
    prm->openProject(projectFilePath);
    std::cout << "PROJEKT OTEVREN" << std::endl;

    accept();
}


/**
  *
  */
void NewProjectDialog::on_buttonBox_helpRequested()
{
    QString message = tr("Specify the project type name and location!\n\n"
                         "Project name could not already exist in the specified location and "
                         "must not contain any of the following characters:\n"
                         "[?:&*\"()|#%<> /',.!]\n\n"
                         "Default project type is Single Network Project.");
    QMessageBox::information(this, tr("New QGama Project Dialog Help"), message);
}


/**
  *
  */
bool NewProjectDialog::isNameValid(const QString &name)
{
    if (name.isEmpty()) {
        ui->label_Warning->setText(tr("Project name have to be specified!"));
        return false;
    }
    else if (name.contains(QRegExp("[?:;&*\"()|#%<> /',.!]"))) {
        ui->label_Warning->setText("  "+tr("Project name must not contain any of the following characters:\n[?:&*\"()|#%<> /',.!]"));
        return false;
    }
    else if (folder.exists()) {
        std::cout << "bb" << folder.absolutePath().toStdString() << std::endl;
        ui->label_Warning->setText(tr("A project with the specified name already exists! Choose diferent name."));
        return false;
    }
    else {
        return true;
    }
}
