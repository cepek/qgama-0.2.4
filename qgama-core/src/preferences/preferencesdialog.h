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

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <ui_preferencesdialog.h>

#include "../preferences/qgamasettings.h"


namespace QGamaCore {

    namespace Ui {

        /** Class generated from Qt Designer's .ui file.
          *
          * It defines the appearence of QGamaCore::PreferencesDialog GUI.
          */
        class PreferencesDialog : public Ui_PreferencesDialog {};
    } // namespace Ui


    /** PreferencesDialog implementation class.
      *
      * All the functionality for QGamaCore::Ui::PreferencesDialog class.
      */
    class PreferencesDialog : public QDialog
    {
        Q_OBJECT

        public:
            PreferencesDialog(QWidget *parent = 0);
            ~PreferencesDialog();

        protected:
            void changeEvent(QEvent *e);
            void paintEvent(QPaintEvent *e);

        private:
            /// Pointer to the Qt Designer's generated class with GUI definition.
            QGamaCore::Ui::PreferencesDialog *ui;
            /// Reference to the QGamaCore::QGamaSettings.
            QGamaCore::QGamaSettings &settings;

        signals:
            void fontChanged();

        private slots:
            void on_pushButtonSelectFont_clicked();
    }; // class PreferencesDialog

} // namespace QGamaCore


#endif // PREFERENCESDIALOG_H
