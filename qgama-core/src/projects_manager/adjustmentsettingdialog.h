#ifndef QGAMACORE__ADJUSTMENTSETTINGDIALOG_H
#define QGAMACORE__ADJUSTMENTSETTINGDIALOG_H

#include <QDialog>
#include <ui_adjustmentsettingdialog.h>

#include "adjustmentsetting.h"
#include "projectstreewidget.h"


namespace QGamaCore {

    namespace Ui {

        /**
          *
          */
        class AdjustmentSettingDialog : public Ui_AdjustmentSettingDialog {};

    } // namespace Ui


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
            QString mode;

        private slots:
            void on_lineEdit_Name_textChanged(QString text);
            void on_checkBox_Apply_Corrections_toggled(bool checked);
            void showHelp();
    }; // class NewComputationalSettingDialog

} // namespace QGamaCore

#endif // QGAMACORE__ADJUSTMENTSETTINGDIALOG_H
