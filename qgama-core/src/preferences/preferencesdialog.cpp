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

#include <QFont>
#include <QFontDialog>

#include "preferencesdialog.h"
#include "../preferences/settingsimpl.h"

using namespace QGamaCore;


/** Constructor.
  *
  * Setups ui, load settings.
  */
PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new QGamaCore::Ui::PreferencesDialog),
    settings(SettingsImpl::instance())
{
    ui->setupUi(this);
}


/** Destructor.
  *
  * Deletes dynamically allocated structures.
  */
PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}


/** Reimplementation of the paintEvent handler.
  *
  * Sets, current application font as the button label, adjusts dialog size.
  * \param[in]  e   Paint Event.
  */
void PreferencesDialog::paintEvent(QPaintEvent *e)
{
    ui->pushButton_Select_Font->setText(qApp->font().family() + " | " + QString::number(qApp->font().pointSize()) + "pt");
    resize(this->sizeHint());
}


/** Slot for selecting application font setting.
  *
  */
void PreferencesDialog::on_pushButton_Select_Font_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, qApp->font(), this);

    if (ok) {
        settings.set("preferences/font",font.toString());
        qApp->setFont(font);
    }
}


/** Reimplementation of the changeEvent handler.
  *
  * Checks if the event is of QEvent::LanguageChange type, if it's so, will retranslate the UI.
  *
  * @param[in] e    Produced QEvent.
  */
void PreferencesDialog::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
