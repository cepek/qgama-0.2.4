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

#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QDir>
#include <ui_newprojectdialog.h>

#include "../projects_manager/projectsmanager.h"


namespace QGamaCore {

    namespace Ui {

        /**
          *
          */
        class NewProjectDialog : public Ui_NewProjectDialog {};

    } // namespace Ui


    /**
      *
      */
    class NewProjectDialog : public QDialog
    {
        Q_OBJECT

        public:
            NewProjectDialog(QWidget *parent = 0);
            ~NewProjectDialog();

        protected:
            void changeEvent(QEvent *e);

        private:
            Ui::NewProjectDialog *ui;
            QDir location;
            QDir folder;
            QGamaCore::ProjectsManager *prm;
            bool isNameValid(const QString &name);

            enum { Id=32 };

        private slots:
            void on_buttonBox_helpRequested();
            void on_toolButton_Browse_clicked();
            void on_lineEdit_Project_Name_textChanged(QString text);
            void createProject();
    }; // class NewProjectDialog

} // namespace QGamaCore


#endif // NEWPROJECTDIALOG_H
