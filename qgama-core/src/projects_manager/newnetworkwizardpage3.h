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

#ifndef QGAMACORE__NEWNETWORKWIZARDPAGE3_H
#define QGAMACORE__NEWNETWORKWIZARDPAGE3_H

#include <QWizardPage>

#include <ui_newnetworkwizardpage3.h>


namespace QGamaCore {

    namespace Ui {

        /**
          *
          */
        class NewNetworkWizardPage3 : public Ui_NewNetworkWizardPage3 {};

    } // namespace Ui


    // forward declarations
    class Settings;
    class ProjectsManager;


    /**
      *
      */
    class NewNetworkWizardPage3 : public QWizardPage
    {
        Q_OBJECT

        public:
            NewNetworkWizardPage3(QWidget *parent = 0);
            ~NewNetworkWizardPage3();

        protected:
            void changeEvent(QEvent *e);
            bool validatePage();
            void initializePage();
            void cleanupPage();
            bool isComplete() const;
            int nextId() const;

        private:
            Ui::NewNetworkWizardPage3 *ui;
            QGamaCore::Settings *settings;
            QGamaCore::ProjectsManager *prm;
            bool isNameValid(const QString &name) const;

            QString networkType;
            QString projectName;
            QString projectLocation;
            QString projectType;

        private slots:
            void on_toolButton_clicked();
            void on_lineEdit_Network_textChanged(QString);
    }; // class NewNetworkWizardPage3

} // namespace NewNetworkWizardPage3


#endif // QGAMACORE__NEWNETWORKWIZARDPAGE3_H
