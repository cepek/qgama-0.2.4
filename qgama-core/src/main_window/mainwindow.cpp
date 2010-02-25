/*
    QGamaCore GUI C++ Library (QGamaCoreLib)
    Copyright (C) 2010  Jiri Novak <jiri.novak.2@fsv.cvut.cz>

    This file is part of the QGamaCore GUI C++ Library.

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <QMessageBox>
#include <QWhatsThis>

#include "../../../config.h"
#include "mainwindow.h"
#include "plugin_manager/pluginmanagerdialog.h"
#include "plugin_manager/pluginmanagerimpl.h"
#include "preferences/qgamasettingsimpl.h"
#include "preferences/preferencesdialog.h"
#include "aboutqgamadialog.h"
#include "aboutgnugamadialog.h"
#include "network.h"

using namespace QGamaCore;


/** Constructor.
  *
  * Setups ui, allocate dialogs, loads settings for the application, loads plugins.
  *
  * @param[in] parent   The pointer to the parent's widget.
  */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new QGamaCore::Ui::MainWindow),
    pmd(new PluginManagerDialog(this)),
    pd(new PreferencesDialog(this)),
    pm(PluginManagerImpl::instance()),
    settings(QGamaSettingsImpl::instance())
 {
    // setting .ui file
    ui->setupUi(this);

    // load all settings
    readSettings();

    // load plugins
    pm.loadPlugins();

    // make connections
    makeConnections();

    // adding what's this icon
    QAction *action_Whatsthis = QWhatsThis::createAction();
    action_Whatsthis->setIcon(QIcon(":/images/icons/whatsthis-24.png"));
    action_Whatsthis->setIconVisibleInMenu(true);
    ui->toolBar_File->addAction(action_Whatsthis);
    ui->menu_Help->addAction(action_Whatsthis);

    // setting bottom left corner of dock widget area
    this->setCorner(Qt::BottomLeftCorner,Qt::LeftDockWidgetArea);

    // set output dock widget to hidden at startup
    ui->dockWidget_Output->setVisible(false);

    // setting the menu initial state
    ui->action_Toolbar_File->setChecked(ui->toolBar_File->isEnabled());
    ui->menu_Points->setEnabled(false);
    ui->menu_Observations->setEnabled(false);
    ui->menu_Network->setEnabled(false);

    // setting window title
    this->setWindowTitle("QGama " + QString(QGAMA_VERSION) + tr(" (using GNU Gama version ") + QString(GAMA_VERSION) + ")");

    // setting mdiArea subwindows icons
    ui->mdiArea->setWindowIcon(QIcon(":/images/icons/notes-32.png"));
}


/** Destructor.
  *
  * Deletes dynamicaly created structures.
  */
MainWindow::~MainWindow()
{
    delete ui;
    delete pmd;
}


/** Makes signal slot connections.
  *
  */
void MainWindow::makeConnections()
{
    connect(ui->action_New_File, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->action_Output, SIGNAL(triggered()), this, SLOT(openOutputDock()));
    connect(ui->action_Projects, SIGNAL(triggered()), this, SLOT(openProjectsDock()));
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(aboutQGamaDialog()));
    connect(ui->action_About_GNU_Gama, SIGNAL(triggered()), this, SLOT(aboutGnuGamaDialog()));
    connect(ui->action_About_Qt, SIGNAL(triggered()), this, SLOT(aboutQtDialog()));
    connect(ui->action_Plugins, SIGNAL(triggered()), this, SLOT(pluginManagerDialog()));
    connect(ui->action_Preferences, SIGNAL(triggered()), this, SLOT(preferencesDialog()));
    connect(ui->action_Quit, SIGNAL(triggered()), this, SLOT(close()));
}


/** Reads all available settings for the application and initialize the application based on it.
  *
  */
void MainWindow::readSettings()
{
    // setting font
    if (settings.get("preferences/font").toString().isEmpty())
        settings.set("preferences/font",qApp->font().toString());

    QString fontString = settings.get("preferences/font").toString();
    QFont font;
    font.fromString(fontString);
    qApp->setFont(font);
}


/** Reimplementation of the changeEvent handler.
  *
  * Checks if the event is of QEvent::LanguageChange type, if it's so, will retranslate the UI.
  *
  * @param[in] e    Produced QEvent.
  */
void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


/** Opens modal Plugin Manager dialog.
  *
  */
void MainWindow::pluginManagerDialog()
{
    pmd->exec();
}


/** Opens modal Preferences dialog.
  *
  */
void MainWindow::preferencesDialog()
{
    pd->exec();
}


/** Opens modal About QGama dialog.
  *
  */
void MainWindow::aboutQGamaDialog()
{
    AboutQGamaDialog about(this);
    about.exec();
}


/** Opens modal About GNU Gama dialog.
  *
  */
void MainWindow::aboutGnuGamaDialog()
{
    AboutGnuGamaDialog about(this);
    about.exec();
}


/** Opens modal About Qt dialog.
  *
  */
void MainWindow::aboutQtDialog()
{
    QMessageBox::aboutQt(this);
}


/** Slot for mantaining "View->Toolbar->File" checkbox synchronized with the toolbar visibility.
  *
  */
void MainWindow::on_action_Toolbar_File_toggled(bool checked)
{
    ui->toolBar_File->setVisible(checked);
}


/** Slot for making visible the Projects dock widget.
  *
  */
void MainWindow::openProjectsDock()
{
    ui->dockWidget_Projects->setVisible(true);
}


/** Slot for making visible the Output dock widget.
  *
  */
void MainWindow::openOutputDock()
{
    ui->dockWidget_Output->setVisible(true);
}


/**
  *
  */
void MainWindow::newFile()
{
    Network *network = new Network;
    ui->mdiArea->addSubWindow(network);

    network->newFile();
    network->showMaximized();
}
