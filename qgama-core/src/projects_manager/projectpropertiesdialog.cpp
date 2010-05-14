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

#include "projectpropertiesdialog.h"

using namespace QGamaCore;


/* ===============================================================================================================*/
/**
  *
  */
ProjectPropertiesDialog::ProjectPropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new QGamaCore::Ui::ProjectPropertiesDialog)
{
    ui->setupUi(this);
}


/* ===============================================================================================================*/
/**
  *
  */
ProjectPropertiesDialog::~ProjectPropertiesDialog()
{
    delete ui;
}


/* ===============================================================================================================*/
/**
  *
  */
void ProjectPropertiesDialog::changeEvent(QEvent *e)
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
