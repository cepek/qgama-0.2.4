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

#ifndef NEWFILEWIZARDPAGE2_H
#define NEWFILEWIZARDPAGE2_H

#include <QWizardPage>

#include <ui_newfilewizardpage2.h>


namespace QGamaCore {

    namespace Ui {

        /**
          *
          */
        class NewFileWizardPage2 : public Ui_NewFileWizardPage2 {};

    } // namespace Ui


    class Settings;
    class ProjectsManager;


    /**
      *
      */
    class NewFileWizardPage2 : public QWizardPage
    {
        Q_OBJECT

        public:
            NewFileWizardPage2(QWidget *parent = 0);
            ~NewFileWizardPage2();

        protected:
            void changeEvent(QEvent *e);
            bool validatePage();
            void initializePage();
            void cleanupPage();
            bool isComplete() const;

        private:
            Ui::NewFileWizardPage2 *ui;
            QGamaCore::Settings *settings;
            QGamaCore::ProjectsManager *prm;
            bool isNameValid(const QString &name) const;

            QString category;
            QString fileType;
            QString projectName;
            QString projectLocation;

        private slots:
            void on_lineEdit_Name_textChanged(QString);
}; // class NewFileWizardPage2

} // namespace QGamaCore


#endif // NEWFILEWIZARDPAGE2_H
