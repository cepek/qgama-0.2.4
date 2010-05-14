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

#ifndef QGAMACORE__SOLVENETWORKDIALOG_H
#define QGAMACORE__SOLVENETWORKDIALOG_H

#include <QDialog>
#include <ui_solvenetworkdialog.h>

#include "../projects_manager/project.h"
#include "document.h"
#include "../utils/applicationcomponentprovider.h"


namespace QGamaCore {

    namespace Ui {

        /**
          *
          */
        class SolveNetworkDialog : public Ui_SolveNetworkDialog {};

    } // namespace Ui


    // forward declarations
    class MainWindow;


    /**
      *
      */
    class SolveNetworkDialog : public QDialog
    {
        Q_OBJECT

        public:
            SolveNetworkDialog(QWidget *parent = 0);
            ~SolveNetworkDialog();

        protected:
            void changeEvent(QEvent *e);
            void accept();

        signals:
            void setCalculating(bool calculating);

        private:
            QGamaCore::Ui::SolveNetworkDialog *ui;
            void initializeUi();

            QGamaCore::ApplicationComponentProvider *acp;
            QGamaCore::MainWindow *mw;
            QGamaCore::Document *document;
            QGamaCore::Project *project;
    }; // class SolveNetworkDialog

} // namespace QGamaCore


#endif // QGAMACORE__SOLVENETWORKDIALOG_H
