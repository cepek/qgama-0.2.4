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

#include "newfiledialog.h"
#include "../factory.h"
#include "../projects_manager/project.h"

using namespace QGamaCore;


/**
  *
  */
NewFileDialog::NewFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new QGamaCore::Ui::NewFileDialog),
    prm(Factory::getProjectsManager())
{
    ui->setupUi(this);

    QList<Project*> projects = prm->getProjectsList();
    QStringList projectNames;
    for (int i=0; i<projects.size(); i++) {
        projectNames.append(projects[i]->getName());
    }
    ui->comboBox_Project->addItems(projectNames);
}


/**
  *
  */
NewFileDialog::~NewFileDialog()
{
    delete ui;
}


/**
  *
  */
void NewFileDialog::changeEvent(QEvent *e)
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
