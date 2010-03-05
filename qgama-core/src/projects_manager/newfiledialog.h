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

#ifndef NEWFILEDIALOG_H
#define NEWFILEDIALOG_H

#include <QDialog>
#include <ui_newfiledialog.h>


namespace QGamaCore {

    namespace Ui {

        class NewFileDialog : public Ui_NewFileDialog {};

    } // namespace Ui


    class NewFileDialog : public QDialog
    {
        Q_OBJECT

        public:
            NewFileDialog(QWidget *parent = 0);
            ~NewFileDialog();

        protected:
            void changeEvent(QEvent *e);

        private:
            QGamaCore::Ui::NewFileDialog *ui;
    }; // class NewFileDialog

} // namespace QGamaCore


#endif // NEWFILEDIALOG_H
