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

#ifndef QGAMACORE__ABOUTQGAMADIALOG_H
#define QGAMACORE__ABOUTQGAMADIALOG_H

#include <QDialog>
#include <ui_aboutqgamadialog.h>


namespace QGamaCore {

    namespace Ui {

        /** Class generated from Qt Designer's .ui file.
          *
          * It defines the appearence of QGamaCore::AboutQGamaDialog.
          */
        class AboutQGamaDialog : public Ui_AboutQGamaDialog {};

    } // namespace Ui


    /** AboutQGamaDialog implementation class.
      *
      * All the underlaying functionality for QGamaCore::Ui::AboutQGamaDialog.
      */
    class AboutQGamaDialog : public QDialog
    {
        Q_OBJECT

        public:
            AboutQGamaDialog(QWidget *parent = 0);
            ~AboutQGamaDialog();

        protected:
            void changeEvent(QEvent *e);

        private:
            /// Pointer to the Qt Designer's generated class with GUI definition.
            QGamaCore::Ui::AboutQGamaDialog *ui;
    }; // class AboutQGamaDialog

} // namespace QGamaCore


#endif // QGAMACORE__ABOUTQGAMADIALOG_H
