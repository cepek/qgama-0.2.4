#include <QtGui>

#include "newnetworkwizard.h"
#include "newnetworkwizardpage.h"
#include "newnetworkwizardpage2.h"
#include "newnetworkwizardpage3.h"

using namespace QGamaCore;


/**
  *
  */
NewNetworkWizard::NewNetworkWizard(QWidget *parent) :
    QWizard(parent)
{
    // set wizard title
    setWindowTitle(tr("New Network"));

    // populate pages
    setMinimumWidth(600);
    setPage(Page_Select_Network_Type, new NewNetworkWizardPage);
    setPage(Page_Create_New_Network, new NewNetworkWizardPage2);
    setPage(Page_Import_Link_Existing_Network, new NewNetworkWizardPage3);

    // set which page should be first
    setStartId(Page_Select_Network_Type);

    // specify that "Help" button should be active and connect a slot to it
    setOption(HaveHelpButton, true);
    connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));
}


/**
  *
  */
void NewNetworkWizard::showHelp()
 {
     QString message;

     switch (currentId()) {
         case Page_Select_Network_Type:
             message = tr("Select the project to which you want to add the new network. "
                          "Choose a network type from the posibilities specified.");
             break;
        case Page_Create_New_Network:
             message = tr("Specify the network name!\n\n"
                          "This could not already exist in the project and "
                          "must not contain any of the following characters:\n"
                          "[?:&*\"|#%<> /'!]");
        case Page_Import_Link_Existing_Network:
             message = tr("Specify the path to the existing network file!");
             break;
     }

     QMessageBox::information(this, tr("New Network Wizard Help"), message);
 }
