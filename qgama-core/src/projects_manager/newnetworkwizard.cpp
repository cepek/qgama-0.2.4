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

#include <QtGui>

#include "newnetworkwizard.h"
#include "newnetworkwizardpage.h"
#include "newnetworkwizardpage2.h"
#include "newnetworkwizardpage3.h"

using namespace QGamaCore;


/* ===============================================================================================================*/
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


/* ===============================================================================================================*/
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
