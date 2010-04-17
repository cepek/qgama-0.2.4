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

#ifndef QGAMACORE__ABOUTGNUGAMADIALOG_H
#define QGAMACORE__ABOUTGNUGAMADIALOG_H

#include <QDialog>
#include <ui_aboutgnugamadialog.h>


namespace QGamaCore {

    namespace Ui {

        /** Class generated from Qt Designer's .ui file.
          *
          * It defines the appearence of QGamaCore::AboutGnuGamaDialog.
          */
        class AboutGnuGamaDialog : public Ui_AboutGnuGamaDialog {};

    } // namespace Ui


    /** AboutGnuGamaDialog implementation class.
      *
      * All the underlaying functionality for QGamaCore::Ui::AboutGnuGamaDialog.
      */
    class AboutGnuGamaDialog : public QDialog
    {
        Q_OBJECT

        public:
            AboutGnuGamaDialog(QWidget *parent = 0);
            ~AboutGnuGamaDialog();

        protected:
            void changeEvent(QEvent *e);

        private:
            /// Pointer to the Qt Designer's generated class with GUI definition.
            QGamaCore::Ui::AboutGnuGamaDialog *ui;
    }; //class AboutGnuGamaDialog

} // namespace QGamaCore


#endif // QGAMACORE__ABOUTGNUGAMADIALOG_H
