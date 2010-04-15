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

#include <QtGui>
#include <QtWebKit>

#include "mainwindow.h"
#include "../../../config.h"
#include "../plugins_manager/pluginsmanagerdialog.h"
#include "../preferences/preferencesdialog.h"
#include "aboutqgamadialog.h"
#include "aboutgnugamadialog.h"
#include "../projects_manager/newprojectdialog.h"
#include "../projects_manager/newnetworkwizard.h"
#include "document.h"
#include "texteditor.h"
#include "../utils/utils.h"
#include "../factory.h"
#include "../projects_manager/projectpropertiesdialog.h"
#include "../projects_manager/project.h"
#include "../projects_manager/adjustmentsettingdialog.h"

//#include <gama-local-main.h>

#include <iostream>

using namespace QGamaCore;


/* ===============================================================================================================*/
/** Constructor.
  *
  * Setups ui, allocate dialogs, loads settings for the application, loads plugins.
  *
  * @param[in] parent   The pointer to the parent's widget.
  */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new QGamaCore::Ui::MainWindow),
    pmd(new PluginsManagerDialog(this)),
    pd(new PreferencesDialog(this)),
    pm(Factory::getPluginsManager()),
    prm(Factory::getProjectsManager()),
    settings(Factory::getSettings())
 {
    // setting .ui file
    ui->setupUi(this);

    // add close button to the tabs in mdi area and also block the default context menu over it
    foreach (QTabBar* tab, ui->mdiArea->findChildren<QTabBar*>()) {
        tab->setTabsClosable(true);
        tab->setContextMenuPolicy(Qt::NoContextMenu);

        connect(tab, SIGNAL(tabCloseRequested(int)),this, SLOT(closeFile()));
    }

    // setting window title
    this->setWindowTitle("QGama " + QString(QGAMA_VERSION) + tr(" (using GNU GamaLib ") + QString(VERSION) + ")");

    // setting the menu initial state
    ui->action_Toolbar_File->setChecked(ui->toolBar_File->isEnabled());
    ui->menu_Network->setEnabled(false);

    // load all settings
    readSettings();

    // load plugins
    pm->loadPlugins();

    // make connections
    makeConnections();

    // adding what's this icon
    QAction *action_Whatsthis = QWhatsThis::createAction();
    action_Whatsthis->setIcon(QIcon(":/images/icons/whatsthis-24.png"));
    action_Whatsthis->setIconVisibleInMenu(true);
    ui->toolBar_File->addAction(action_Whatsthis);
    ui->menu_Help->addAction(action_Whatsthis);

    // if there are no projects opened
    if (prm->projectsCount()==0) {
        decreaseProjectsCount();
    }

    // initialize file menu actions state, if there are no subwindows opened
    if (ui->mdiArea->subWindowList().size()==0)
        activeSubWindowChanged(0);
}


/* ===============================================================================================================*/
/** Destructor.
  *
  * Deletes dynamicaly created structures.
  */
MainWindow::~MainWindow()
{
    // save the window's state
    settings->set("MainWindow/size",size());
    settings->set("MainWindow/pos",pos());

    // release all singletons
    Factory::releaseSettings(settings);
    Factory::releasePluginsManager(pm);
    Factory::releaseProjectsManager(prm);

    // delete dynamically created structures
    delete ui;
    delete pmd;
}


/* ===============================================================================================================*/
/** Makes signal slot connections.
  *
  */
void MainWindow::makeConnections()
{
    // File menu actions
    connect(ui->action_New_Project, SIGNAL(triggered()), this, SLOT(newProject()));
    connect(ui->action_New_Network, SIGNAL(triggered()), this, SLOT(newNetwork()));
    connect(ui->action_Quit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_Open_File, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->action_Close_File, SIGNAL(triggered()), this, SLOT(closeFile()));
    connect(ui->action_Open_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->action_Close_Project, SIGNAL(triggered()), this, SLOT(closeProject()));
    connect(ui->menu_Open_Recent_Project, SIGNAL(triggered(QAction*)), this, SLOT(openRecentProject(QAction*)));
    connect(ui->menu_Open_Recent_File, SIGNAL(triggered(QAction*)), this, SLOT(openRecentFile(QAction*)));
    connect(ui->action_Close_All_Projects, SIGNAL(triggered()), this, SLOT(closeAllProjects()));
    connect(ui->action_Project_Properties, SIGNAL(triggered()), this, SLOT(projectProperties()));
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->action_Save_As, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->action_Save_All, SIGNAL(triggered()), this, SLOT(saveAll()));
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(activeSubWindowChanged(QMdiSubWindow*)));
    connect(ui->action_Print, SIGNAL(triggered()), this, SLOT(print()));

    // Edit menu actions
    connect(ui->action_Plugins, SIGNAL(triggered()), this, SLOT(pluginManagerDialog()));
    connect(ui->action_Preferences, SIGNAL(triggered()), this, SLOT(preferencesDialog()));

    // Networks menu actions
    connect(ui->action_Solve, SIGNAL(triggered()), this, SLOT(solve()));
    connect(ui->action_Add_Setting, SIGNAL(triggered()), this, SLOT(newSetting()));

    // Window menu actions
    connect(ui->action_Projects, SIGNAL(triggered()), this, SLOT(openProjectsDock()));

    // About menu actions
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(aboutQGamaDialog()));
    connect(ui->action_About_GNU_Gama, SIGNAL(triggered()), this, SLOT(aboutGnuGamaDialog()));
    connect(ui->action_About_Qt, SIGNAL(triggered()), this, SLOT(aboutQtDialog()));
}


/* ===============================================================================================================*/
/** Reads all available settings for the application and initialize the application based on it.
  *
  */
void MainWindow::readSettings()
{
    // set font
    if (settings->get("preferences/font").toString().isEmpty())
        settings->set("preferences/font",qApp->font().toString());
    QString fontString = settings->get("preferences/font").toString();
    QFont font;
    font.fromString(fontString);
    qApp->setFont(font);

    // open projects
    QStringList openedProjects = settings->get("projects/openedProjects").toStringList();
    for (int i=0; i<openedProjects.size(); i++) {
        prm->openProject(openedProjects[i],false);
    }

    // set active project
    if (openedProjects.size()>0) {
        QStringList activeProject = settings->get("projects/activeProject").toStringList();
        prm->setActiveProject(activeProject.value(0),activeProject.value(1));
        ui->treeWidget_Projects->collapseNonActiveProjects();
    }

    // initialize recently opened projects
    updateRecentlyOpenedProjects();

    // initialize recently opened files
    updateRecentlyOpenedFiles();

    // resize and move
    if (!settings->get("MainWindow/size").isNull())
        resize(settings->get("MainWindow/size").toSize());
    if (!settings->get("MainWindow/pos").isNull())
        move(settings->get("MainWindow/pos").toPoint());
}


/* ===============================================================================================================*/
/** Reimplementation of the changeEvent handler.
  *
  * Checks if the event is of QEvent::LanguageChange type, if it's so, will retranslate the UI.
  *
  * @param[in] e    Produced QEvent.
  */
void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    switch (event->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::closeEvent(QCloseEvent *event)
{
    // update files attributes in projects
    prm->updateProjectFilesEntries();

    // close all subwindows
    ui->mdiArea->closeAllSubWindows();

    event->accept();
}


/* ===============================================================================================================*/
/** Opens modal Plugin Manager dialog.
  *
  */
void MainWindow::pluginManagerDialog()
{
    pmd->exec();
}


/* ===============================================================================================================*/
/** Opens modal Preferences dialog.
  *
  */
void MainWindow::preferencesDialog()
{
    pd->exec();
}


/* ===============================================================================================================*/
/** Opens modal About QGama dialog.
  *
  */
void MainWindow::aboutQGamaDialog()
{
    AboutQGamaDialog dialog(this);
    dialog.exec();
}


/* ===============================================================================================================*/
/** Opens modal About GNU Gama dialog.
  *
  */
void MainWindow::aboutGnuGamaDialog()
{
    AboutGnuGamaDialog dialog(this);
    dialog.exec();
}


/* ===============================================================================================================*/
/** Opens modal About Qt dialog.
  *
  */
void MainWindow::aboutQtDialog()
{
    QMessageBox::aboutQt(this);
}


/* ===============================================================================================================*/
/** Slot for mantaining "View->Toolbar->File" checkbox synchronized with the toolbar visibility.
  *
  */
void MainWindow::on_action_Toolbar_File_toggled(bool checked)
{
    ui->toolBar_File->setVisible(checked);
}


/* ===============================================================================================================*/
/** Slot for making visible the Projects dock widget.
  *
  */
void MainWindow::openProjectsDock()
{
    ui->dockWidget_Projects->setVisible(true);
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::newNetwork()
{
    NewNetworkWizard wizard(this);
    wizard.exec();
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::newProject()
{
    NewProjectDialog dialog(this);
    dialog.exec();
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::openFile()
{
    QDir dir;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), dir.home().absolutePath()+"/QGamaProjects", tr("QGama Network Files (*.xml *.gkf);; QGama Solution Files (*.xml *.txt *.html)"));

    QString terminator = fileName.split(".").last();
    if ((terminator == "xml" && !fileName.contains("Solutions")) || terminator == "gkf")
        openFile(fileName,"network");
    else if (terminator == "html")
        openFile(fileName,"solution-html");
    else if (terminator == "xml" && (fileName.contains("Solutions")))
        openFile(fileName,"solution-xml");
    else
        openFile(fileName,"txt");
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::openFile(const QString &file, const QString &fileType)
{
    if (!file.isEmpty()) {
        // if it was already opened, set active window to it
        QMdiSubWindow *existing = Utils::findMdiSubWindow(file);
        if (existing) {
            ui->mdiArea->setActiveSubWindow(existing);
            return;
        }

        if (fileType == "network") {
            // enable network menu
            ui->menu_Network->setEnabled(true);

            // add subwindow and open the file in it
            TextEditor *child = new TextEditor("network");
            QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(child->getWidget());
            if (child->loadFile(file))
                child->showMaximized();
            else
                child->close();

            // set subwindow icon
            subWindow->setWindowIcon(QIcon(":/images/icons/network-32.png"));

            // disable subwindow's default shortcuts so that our works
            foreach (QAction* action, ui->mdiArea->findChildren<QAction*>()) {
                if (action->shortcut().toString()=="Ctrl+W")
                    action->setShortcut(QKeySequence(""));
            }

            // add entries to the window menu
            QAction *action = new QAction(QIcon(":/images/icons/network-32.png")," "+QFileInfo(file).fileName(),ui->menu_Windows);
            action->setIconVisibleInMenu(true);
            action->setData(file+"|network");
            ui->menu_Windows->addAction(action);
            connect(ui->menu_Windows, SIGNAL(triggered(QAction*)), this, SLOT(activateDesiredSubwindow(QAction*)));
        }

        if (fileType == "solution-html") {
            // add subwindow and open the file in it
            QWebView *child = new QWebView;
            child->setAttribute(Qt::WA_DeleteOnClose);
            QMdiSubWindow *subwindow = ui->mdiArea->addSubWindow(child);
            QFile in(file);
            in.open(QIODevice::ReadOnly);
            QTextStream ts(&in);
            child->setHtml(ts.readAll());
            child->showMaximized();
        }
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::openProject()
{
    QDir dir;
    QString projectName = QFileDialog::getOpenFileName(this, tr("Open QGama Project"), dir.home().absolutePath()+"/QGamaProjects", tr("QGama Project Files (*.qgp)"));
    if (!projectName.isEmpty())
        prm->openProject(projectName);
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::closeProject()
{
    prm->closeActiveProject();
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::decreaseProjectsCount()
{
    ui->dockWidget_Projects->setWindowTitle(QObject::tr("Projects") + " ("+QString::number(prm->projectsCount()) + QObject::tr(" Opened)"));

    if (prm->projectsCount()==0) {
        // hide some actions in the file menu
        ui->action_New_Network->setEnabled(false);
        ui->action_Close_File->setEnabled(false);
        ui->action_Close_Project->setEnabled(false);
        ui->action_Close_All_Projects->setEnabled(false);
        ui->action_Project_Properties->setEnabled(false);

        // hide treewidget with projects
        ui->treeWidget_Projects->setStyleSheet("background-color: transparent;");

        // set the active project in the actions text to an empty string
        ui->action_Project_Properties->setText(" "+ui->action_Project_Properties->text().left(ui->action_Project_Properties->text().indexOf("(")).trimmed());
        ui->action_Close_Project->setText(" "+ui->action_Close_Project->text().left(ui->action_Close_Project->text().indexOf("(")).trimmed());
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::increaseProjectsCount()
{    
    ui->dockWidget_Projects->setWindowTitle(QObject::tr("Projects") + " ("+QString::number(prm->projectsCount()) + QObject::tr(" Opened)"));

    if (prm->projectsCount()==1) {
        // hide some actions in the file menu
        ui->action_New_Network->setEnabled(true);
        ui->action_Close_File->setEnabled(true);
        ui->action_Close_Project->setEnabled(true);
        ui->action_Close_All_Projects->setEnabled(true);
        ui->action_Project_Properties->setEnabled(true);

        // hide treewidget with projects
        ui->treeWidget_Projects->setStyleSheet("");
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::updateRecentlyOpenedProjects()
{
    std::cout << "updateRecentlyOpenedProjects() start" << std::endl;

    QStringList recentlyOpenedProjects = settings->get("projects/recentlyOpenedProjects").toStringList();
    int n = recentlyOpenedProjects.size();

    // if there are no recently opened projects, disable the submenu
    if (n == 0) {
        ui->menu_Open_Recent_Project->setEnabled(false);
    }
    // else, fill corresponding number of items
    else {
        ui->menu_Open_Recent_Project->setEnabled(true);

        for (int i=0; i<5; i++) {
            QAction *action = ui->menu_Open_Recent_Project->actions().at(i);
            action->setVisible(false);
        }

        for (int i=0; i<n; i++) {
            QAction *action = ui->menu_Open_Recent_Project->actions().at(i);
            QString projectFilePath = recentlyOpenedProjects[n-1-i];
            QStringList aux = projectFilePath.split("/");
            action->setVisible(true);
            action->setText(" "+aux.value(aux.size()-2));
            action->setData(projectFilePath);
            action->setIcon(QIcon(":/images/icons/babieca-64.png"));
            action->setIconVisibleInMenu(true);
        }
    }

    std::cout << "updateRecentlyOpenedProjects() stop" << std::endl;
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::updateRecentlyOpenedFiles()
{
    std::cout << "updateRecentlyOpenedFiles() start" << std::endl;

    QStringList recentlyOpenedFiles = settings->get("projects/recentlyOpenedFiles").toStringList();
    int n = recentlyOpenedFiles.size();

    // if there are no recently opened files, disable the submenu
    if (n == 0) {
        ui->menu_Open_Recent_File->setEnabled(false);
    }
    // else, fill corresponding number of items
    else {
        ui->menu_Open_Recent_File->setEnabled(true);

        for (int i=0; i<5; i++) {
            QAction *action = ui->menu_Open_Recent_File->actions().at(i);
            action->setVisible(false);
        }

        for (int i=0; i<n; i++) {
            QAction *action = ui->menu_Open_Recent_File->actions().at(i);
            QString openedFileData = recentlyOpenedFiles[n-1-i];
            QStringList aux = openedFileData.split("|");
            QString openedFilePath = aux.value(0);
            QString openedFileType = aux.value(1);

            action->setVisible(true);
            action->setText(" "+openedFilePath.split("/").last());
            action->setData(openedFileData);
            action->setIconVisibleInMenu(true);

            if (openedFileType == "network") {
                action->setIcon(QIcon(":/images/icons/network-32.png"));
            }
        }
    }

    std::cout << "updateRecentlyOpenedFiles() stop" << std::endl;
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::openRecentProject(QAction *action)
{
    std::cout << "openRecentProjectStart" << std::endl;

    QString projectFilePath = action->data().toString();

    if (!projectFilePath.isEmpty()) {
        prm->openProject(projectFilePath);
    }

    std::cout << "openRecentProjectStop" << std::endl;
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::openRecentFile(QAction *action)
{
    std::cout << "openRecentFileStart" << std::endl;

    QStringList aux = action->data().toString().split("|");
    QString fileName = aux.value(0);
    QString fileType = aux.value(1);

    if (!fileName.isEmpty() && !fileType.isEmpty()) {
        openFile(fileName, fileType);
    }

    std::cout << "openRecentFileStop" << std::endl;
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::closeAllProjects()
{
    QStringList openedProjects = settings->get("projects/openedProjects").toStringList();

    for (int i=0; i<openedProjects.size(); i++) {
        prm->closeActiveProject();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::projectProperties()
{
    ProjectPropertiesDialog dialog(this);
    dialog.exec();
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::solve()
{
    /*
    char* argv[4];

    argv[0] = "gama-local";
    argv[1] = "../../../QGamaProjects/QGamaProject1/Networks/New1DNetwork.xml";
    argv[2] = "--text";
    argv[3] = "../../../QGamaProjects/QGamaProject1/Solutions/New1DNetworkSolution.xml";

    std::cout << "Starting solving" << std::endl;
    std::cout << GaMa_Main(4,argv) << std::endl;
    std::cout << "Ended solving" << std::endl;

    openFile("../../../QGamaProjects/QGamaProject1/Solutions/New1DNetworkSolution.xml");
    */
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::closeFile()
{
    // close the file
    QString fileToClose;
    QString fileType;
    if (ui->mdiArea->subWindowList().size()==1) {
        Document *textEditor = qobject_cast<Document*> (ui->mdiArea->subWindowList()[0]->widget());
        fileToClose = textEditor->currentFile();
        fileType = textEditor->documentType();
        ui->mdiArea->closeAllSubWindows();
    }
    else {
        Document *textEditor = qobject_cast<Document*> (ui->mdiArea->activeSubWindow()->widget());
        fileToClose = textEditor->currentFile();
        fileType = textEditor->documentType();
        ui->mdiArea->closeActiveSubWindow();
    }

    // remove the Window menu entry
    QList<QAction*> actions = ui->menu_Windows->actions();
    for (int i=0; i<actions.size(); i++) {
        if (actions[i]->data().toString().split("|").value(0) == fileToClose)
            ui->menu_Windows->removeAction(actions[i]);
    }
    
    // save the file to the list of the last five recently opened files
    QStringList recentlyOpenedFiles = settings->get("projects/recentlyOpenedFiles").toStringList();
    if (!recentlyOpenedFiles.contains(fileToClose+"|"+fileType)) {
        if (recentlyOpenedFiles.size()==5) {
            recentlyOpenedFiles.removeAt(0);
        }
        recentlyOpenedFiles.append(fileToClose+"|"+fileType);
        settings->set("projects/recentlyOpenedFiles",recentlyOpenedFiles);
    }
    else {
        int index = recentlyOpenedFiles.indexOf(fileToClose+"|"+fileType);
        recentlyOpenedFiles.removeAt(index);
        recentlyOpenedFiles.append(fileToClose+"|"+fileType);
    }

    // and "commit" the change
    updateRecentlyOpenedFiles();
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::closeFile(const QString &filePath)
{
    // change focus to the corresponding subwindow if exists and close it
    QMdiSubWindow *existing = Utils::findMdiSubWindow(filePath);
    if (existing) {
        ui->mdiArea->setActiveSubWindow(existing);
        closeFile();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::save()
{
    if (ui->mdiArea->subWindowList().size()==1) {
        Document *textEditor = qobject_cast<Document*> (ui->mdiArea->subWindowList()[0]->widget());
        textEditor->save();
    }
    else {
        Document *textEditor = qobject_cast<Document*> (ui->mdiArea->activeSubWindow()->widget());
        textEditor->save();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::saveAs()
{
    if (ui->mdiArea->subWindowList().size()==1) {
        Document *textEditor = qobject_cast<Document*> (ui->mdiArea->subWindowList()[0]->widget());
        textEditor->saveAs();
    }
    else {
        Document *textEditor = qobject_cast<Document*> (ui->mdiArea->activeSubWindow()->widget());
        textEditor->saveAs();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::saveAll()
{
    for (int i=0; i<ui->mdiArea->subWindowList().size(); i++) {
        Document *textEditor = qobject_cast<Document*> (ui->mdiArea->subWindowList()[i]->widget());
        textEditor->save();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::subWindowsStatesChanged()
{
    // get know the subwindows count
    int n = ui->mdiArea->subWindowList().size();

    // get know the number of the modified ones
    int modified = 0;
    for (int i=0; i<n; i++) {
        if (ui->mdiArea->subWindowList()[i]->isWindowModified())
            modified++;
    }

    std::cout << "modified: " << modified << std::endl;

    // if there are no subwindows opened or none of the opened ones is modified disable save actions
    if (n==0 || modified==0) {
        ui->action_Save->setEnabled(false);
        ui->action_Save_As->setEnabled(false);
        ui->action_Save_All->setEnabled(false);
    }
    // else enable those functions again
    else {
        std::cout << "jdu tudy" << std::endl;
        ui->action_Save->setEnabled(true);
        ui->action_Save_As->setEnabled(true);
        ui->action_Save_All->setEnabled(true);
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::activeSubWindowChanged(QMdiSubWindow *subWindow)
{
    // if doesn't deal the last subwindow, change the title
    if (subWindow!=0) {
        std::cout << "activeSubWindowChanged" << std::endl;

        setWindowModified(subWindow->isWindowModified());
        setWindowTitle(windowTitle().split(" - ").value(0).trimmed()+" - "+subWindow->windowTitle());
        ui->action_Close_File->setEnabled(true);
    }
    // if it was last, disable the close file action
    else {
        ui->action_Close_File->setEnabled(false);
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::activateDesiredSubwindow(QAction *action)
{
    QStringList data = action->data().toString().split("|");

    openFile(data.value(0), data.value(1));
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::print()
{
    QMessageBox::information(this, tr("Function not implemented!"), tr("In this version of QGama the Print functionality is not yet implemented, wait for the future releases..."));
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::newSetting()
{
    AdjustmentSettingDialog dialog(0,this);
    dialog.exec();
}
