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

#include "aboutgnugamadialog.h"
#include "../../../config.h"

using namespace QGamaCore;


/* ===============================================================================================================*/
/** Constructor.
  *
  * Setups ui, initialize labels, adjusts dialog size.
  *
  * \param[in] parent       The pointer to the parent's widget.
  */
AboutGnuGamaDialog::AboutGnuGamaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new QGamaCore::Ui::AboutGnuGamaDialog)
{
    ui->setupUi(this);

    ui->label_Text1->setText(tr("This program uses GNU Gama version") + " <b>" + QString(VERSION) + "</b>.");
    ui->label_Text2->setText(tr("The project GNU Gama is a free software written in C++, released under the terms of GNU General Public License, aimed at geodetic network adjustment."));
    ui->label_Text3->setText(tr("Developers:") + "<br/>" +
                             QString::fromUtf8("&nbsp;&nbsp;&nbsp;&nbsp;Aleš Čepek") + " (<a href=mailto:cepek@gama.fsv.cvut.cz>cepek@gama.fsv.cvut.cz</a>)<br/>" +
                             QString::fromUtf8("&nbsp;&nbsp;&nbsp;&nbsp;Petr Doubrava") + " (<a href=mailto:petr@gepro.cz>petr@gepro.cz</a>)<br/>" +
                             QString::fromUtf8("&nbsp;&nbsp;&nbsp;&nbsp;Jan Pytel") + " (<a href=mailto:pytel@gama.fsv.cvut.cz>pytel@gama.fsv.cvut.cz</a>)<br/>" +
                             QString::fromUtf8("&nbsp;&nbsp;&nbsp;&nbsp;Jiří Veselý") + " (<a href=mailto:vesely@gama.fsv.cvut.cz>vesely@gama.fsv.cvut.cz</a>)");
    ui->label_Text4->setText(tr("For more information see:")+" <a href=http://www.gnu.org/software/gama>http://www.gnu.org/software/gama</a>.");
    resize(this->sizeHint());
}


/* ===============================================================================================================*/
/** Destructor.
  *
  * Deletes dynamically alocated structures.
  */
AboutGnuGamaDialog::~AboutGnuGamaDialog()
{
    delete ui;
}


/* ===============================================================================================================*/
/** Reimplementation of the changeEvent handler.
  *
  * Checks if the event is of QEvent::LanguageChange type, if it's so, will retranslate the UI.
  *
  * @param[in] e    Produced QEvent.
  */
void AboutGnuGamaDialog::changeEvent(QEvent *e)
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
