#include <QtGui>

#include "newfilewizard.h"
#include "newfilewizardpage.h"
#include "newfilewizardpage2.h"

using namespace QGamaCore;


/**
  *
  */
NewFileWizard::NewFileWizard(QWidget *parent) :
    QWizard(parent)
{
    // set wizard title
    setWindowTitle(tr("New File"));

    // populate pages
    NewFileWizardPage *page = new NewFileWizardPage;
    setMinimumSize(page->sizeHint());
    setPage(Page_Select_File_Type, page);
    setPage(Page_Select_Name_And_Location, new NewFileWizardPage2);

    // set which page should be first
    setStartId(Page_Select_File_Type);

    // specify that "Help" button should be active and connect a slot to it
    setOption(HaveHelpButton, true);
    connect(this, SIGNAL(helpRequested()), this, SLOT(showHelp()));
}


/**
  *
  */
void NewFileWizard::showHelp()
 {
     QString message;

     switch (currentId()) {
         case Page_Select_File_Type:
             message = tr("Select the project to which you want to add the new file. Choose a category and then "
                          "a file type from the posibilities specified.");
             break;
        case Page_Select_Name_And_Location:
             message = tr("Specify the file name!\n\n"
                          "This could not already exist in the project and "
                          "must not contain any of the following characters:\n"
                          "[?:&*\"|#%<> /'!]");
             break;
     }

     QMessageBox::information(this, tr("New File Wizard Help"), message);
 }
