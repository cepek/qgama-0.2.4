#ifndef NEWNETWORKWIZARDPAGE3_H
#define NEWNETWORKWIZARDPAGE3_H

#include <QWizardPage>
#include <ui_newnetworkwizardpage3.h>


namespace QGamaCore {

    namespace Ui {

        /**
          *
          */
        class NewNetworkWizardPage3 : public Ui_NewNetworkWizardPage3 {};

    } // namespace Ui


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


#endif // NEWNETWORKWIZARDPAGE3_H
