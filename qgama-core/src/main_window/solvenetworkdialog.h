#ifndef QGAMACORE__SOLVENETWORKDIALOG_H
#define QGAMACORE__SOLVENETWORKDIALOG_H

#include <QDialog>
#include <ui_solvenetworkdialog.h>

#include "../projects_manager/project.h"
#include "document.h"


namespace QGamaCore {

    class MainWindow;


    namespace Ui {

        /**
          *
          */
        class SolveNetworkDialog : public Ui_SolveNetworkDialog {};

    } // namespace Ui


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

            QGamaCore::MainWindow *mw;
            QGamaCore::Document *document;
            QGamaCore::Project *project;
    }; // class SolveNetworkDialog

} // namespace QGamaCore


#endif // QGAMACORE__SOLVENETWORKDIALOG_H
