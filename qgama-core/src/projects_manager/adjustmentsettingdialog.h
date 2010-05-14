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

#ifndef QGAMACORE__ADJUSTMENTSETTINGDIALOG_H
#define QGAMACORE__ADJUSTMENTSETTINGDIALOG_H

#include <QDialog>
#include <ui_adjustmentsettingdialog.h>

#include "adjustmentsetting.h"
#include "projectstreewidget.h"
#include "../utils/applicationcomponentprovider.h"


namespace QGamaCore {

    namespace Ui {

        /**
          *
          */
        class AdjustmentSettingDialog : public Ui_AdjustmentSettingDialog {};

    } // namespace Ui


    // forward declarations
    class ProjectsManager;


    /**
      *
      */
    class AdjustmentSettingDialog : public QDialog
    {
        Q_OBJECT

        public:
            AdjustmentSettingDialog(AdjustmentSetting *as, QWidget *parent = 0);
            ~AdjustmentSettingDialog();

        protected:
            void changeEvent(QEvent *e);
            void accept();

        private:
            QGamaCore::Ui::AdjustmentSettingDialog *ui;
            QGamaCore::ProjectsManager *prm;
            QGamaCore::AdjustmentSetting *as;
            QGamaCore::ProjectsTreeWidget *ptw;
            QGamaCore::ApplicationComponentProvider *acp;
            QString mode;

        private slots:
            void on_lineEdit_Name_textChanged(QString text);
            void on_checkBox_Apply_Corrections_toggled(bool checked);
            void showHelp();
    }; // class NewComputationalSettingDialog

} // namespace QGamaCore

#endif // QGAMACORE__ADJUSTMENTSETTINGDIALOG_H
