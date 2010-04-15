#ifndef NEWNETWORKWIZARD_H
#define NEWNETWORKWIZARD_H

#include <QWizard>


namespace QGamaCore {

    /**
      *
      */
    class NewNetworkWizard : public QWizard
    {
        Q_OBJECT

        public:
            enum { Page_Select_Network_Type, Page_Create_New_Network, Page_Import_Link_Existing_Network };

            NewNetworkWizard(QWidget *parent = 0);

        private slots:
            void showHelp();
    }; // class NewNetworkWizard

} // namespace QGamaCore

#endif // NEWNETWORKWIZARD_H
