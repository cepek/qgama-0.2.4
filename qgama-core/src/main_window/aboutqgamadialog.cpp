/****************************************************************************
**
**    QGamaCore GUI C++ Library (QGamaCoreLib)
**    Copyright (C) 2010  Jiri Novak <jiri.novak.2@fsv.cvut.cz>
**
**    This file is part of the QGamaCore GUI C++ Library.
**
**    This library is free software; you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation; either version 2 of the License, or
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

#include "aboutqgamadialog.h"
#include "../../../config.h"

using namespace QGamaCore;


/** Constructor.
  *
  * Setups ui, initialize labels, adjusts dialog size.
  *
  * \param[in] parent       The pointer to the parent's widget.
  */
AboutQGamaDialog::AboutQGamaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new QGamaCore::Ui::AboutQGamaDialog)
{
    ui->setupUi(this);

    ui->label_Program->setText("<b>GNU Gama / QGama - " + QString(QGAMA_VERSION) + "</b>");
    ui->label_Author->setText("&copy; 2010 " + QString::fromUtf8("Jiří Novák") + " (<a href=mailto:jiri.novak.2@fsv.cvut.cz>jiri.novak.2@fsv.cvut.cz</a>)");

    resize(this->sizeHint());
}


/** Destructor.
  *
  * Deletes dynamically alocated structures.
  */
AboutQGamaDialog::~AboutQGamaDialog()
{
    delete ui;
}


/** Reimplementation of the changeEvent handler.
  *
  * Checks if the event is of QEvent::LanguageChange type, if it's so, will retranslate the UI.
  *
  * @param[in] e    Produced QEvent.
  */
void AboutQGamaDialog::changeEvent(QEvent *e)
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
