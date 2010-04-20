/****************************************************************************
**
**    QGamaCore GUI C++ Library (QGamaCoreLib)
**    Copyright (C) 2010  Jiri Novak <jiri.novak.2@fsv.cvut.cz>
**
**    This file is part of the QGamaCore GUI C++ Library.
**
**    This library is free software; you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation; either version 2 of the License, or
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
#include <QtWebKit>
#include <string>

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
#include "htmlviewer.h"
#include "progressdialog.h"
#include "solvenetworkdialog.h"
#include "../utils/applicationcomponentprovider.h"
#include "../factory.h"
#include "../projects_manager/projectpropertiesdialog.h"
#include "../projects_manager/project.h"
#include "../projects_manager/adjustmentsettingdialog.h"

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
    settings(Factory::getSettings()),
    calculating(false)
 {
    // setting .ui file
    ui->setupUi(this);

    // make connections
    makeConnections();

    // initialize ui
    initializeUi();

    // load all settings
    readSettings();

    // load plugins
    pm->loadPlugins();
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::initializeUi()
{
    // add close button to the tabs in mdi area and also block the default context menu over it and connect its close
    // action
    foreach (QTabBar* tab, ui->mdiArea->findChildren<QTabBar*>()) {
        tab->setTabsClosable(true);
        tab->setContextMenuPolicy(Qt::NoContextMenu);

        connect(tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeSubWindow(int)));
    }

    // setting window title
    setWindowTitle("QGama " + QString(QGAMA_VERSION) + tr(" (using GNU GamaLib ") + QString(VERSION) + ")");

    // setting the menu initial state
    ui->action_Toolbar_File->setChecked(ui->toolBar_File->isEnabled());
    ui->action_Toolbar_Network->setChecked(ui->toolBar_Network->isEnabled());

    // adding what's this icon
    QAction *action_Whatsthis = QWhatsThis::createAction();
    action_Whatsthis->setIcon(QIcon(":/images/icons/whatsthis-24.png"));
    action_Whatsthis->setIconVisibleInMenu(true);
    ui->toolBar_File->addAction(action_Whatsthis);
    ui->menu_Help->addAction(action_Whatsthis);
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

    // Others
    connect(ui->mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(onSubWindowActivated(QMdiSubWindow*)));
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
        Project *project = prm->getProject(activeProject.value(0),activeProject.value(1));
        Q_ASSERT(project!=0 && "project pointer is 0!");
        prm->setActiveProject(project);
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

    // if there are no projects opened
    if (prm->projectsCount()==0)
        decreaseProjectsCount();

    // initialize file menu actions state, if there are no subwindows opened
    if (ui->mdiArea->subWindowList().size()==0) {
        onSubWindowStateChanged();
        onSubWindowActivated(0);
    }
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
/**
  *
  */
void MainWindow::on_action_Toolbar_Network_toggled(bool checked)
{
    ui->toolBar_Network->setVisible(checked);
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
void MainWindow::openFile(const QString &filePath, const QString &fileType, Project *project)
{
    if (!filePath.isEmpty()) {
        // if it was already opened, set active window to it
        QMdiSubWindow *existing = ApplicationComponentProvider::findMdiSubWindow(filePath);
        if (existing) {
            ui->mdiArea->setActiveSubWindow(existing);
            return;
        }
        // else open new subwindow
        else {
            openNewSubWindow(filePath, fileType, project);
        }
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::openNewSubWindow(const QString &filePath, const QString &fileType, Project *project, const QString &content)
{
    qDebug() << "MainWindow::openNewSubWindow() - START";

    Document *document = 0;
    QMdiSubWindow *subWindow = 0;

    if (project == 0)
        project = prm->getActiveProject();

    Q_ASSERT(project!=0 && "project pointer is 0!");

    if (fileType == "network" || fileType == "solution-xml" || fileType == "txt") {
        QIcon icon;
        if (fileType == "network")              icon.addFile(":/images/icons/network-32.png");
        else if (fileType == "solution-xml")    icon.addFile(":/images/icons/xml-32.png");
        else if (fileType == "txt")             icon.addFile(":/images/icons/txt-32.png");

        // add subwindow and set it corresponding icon
        TextEditor *textEditor = new TextEditor(fileType, project);
        document = textEditor;
        subWindow = ui->mdiArea->addSubWindow(textEditor);
        subWindow->setWindowIcon(icon);
    }

    else if (fileType == "solution-html") {
        // add subwindow and set it corresponding icon
        HtmlViewer *htmlViewer = new HtmlViewer("solution-html", project);
        document = htmlViewer;
        subWindow = ui->mdiArea->addSubWindow(htmlViewer);
        subWindow->setWindowIcon(QIcon(":/images/icons/html-32.png"));
    }

    // open it in the way dependent of the mode variable
    Q_ASSERT(document!=0 && "document pointer is 0!");

    // if no content is specified as parameter, load the file from filePath
    if (content.isEmpty()) {
        if (document->loadFile(filePath))
            document->showMaximized();
        else
            document->close();
    }
    // else open a new file and initialize it with the content
    else {
        document->newFile(filePath,content);
        document->showMaximized();
    }

    // run the corresponding callbacks
    onSubWindowActivated(subWindow);
    onSubWindowOpen(filePath, fileType);
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::onSubWindowOpen(const QString &filePath, const QString &fileType)
{
    // disable subwindow's default shortcuts so that our work
    foreach (QAction* action, ui->mdiArea->findChildren<QAction*>()) {
        if (action->shortcut().toString()=="Ctrl+W")
            action->setShortcut(QKeySequence(""));
    }

    // set corresponding icon
    QIcon icon;
    if (fileType=="network")             icon.addFile(":/images/icons/network-16.png");
    else if (fileType=="solution-html")  icon.addFile(":/images/icons/html-16.png");
    else if (fileType=="solution-xml")   icon.addFile(":/images/icons/xml-16.png");
    else if (fileType=="txt")            icon.addFile(":/images/icons/txt-16.png");

    // add entry to the window menu
    QAction *action = new QAction(icon," "+QFileInfo(filePath).fileName(),ui->menu_Windows);
    action->setIconVisibleInMenu(true);
    action->setData(filePath);
    ui->menu_Windows->addAction(action);
    connect(ui->menu_Windows, SIGNAL(triggered(QAction*)), this, SLOT(onWindowItemClicked(QAction*)));
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
        ui->action_Close_Project->setEnabled(false);
        ui->action_Close_All_Projects->setEnabled(false);
        ui->action_Project_Properties->setEnabled(false);
        ui->action_Add_Setting->setEnabled(false);
        ui->action_Open_File->setEnabled(false);
        ui->menu_Open_Recent_File->setEnabled(false);

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
        ui->action_Close_Project->setEnabled(true);
        ui->action_Close_All_Projects->setEnabled(true);
        ui->action_Project_Properties->setEnabled(true);
        ui->action_Add_Setting->setEnabled(true);
        ui->action_Open_File->setEnabled(true);
        updateRecentlyOpenedFiles();

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
    qDebug() << "MainWindow::updateRecentlyOpenedProjects() - START";

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

    qDebug() << "MainWindow::updateRecentlyOpenedProjects() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::updateRecentlyOpenedFiles()
{
    qDebug() << "MainWindow::updateRecentlyOpenedFiles() - START";

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

    qDebug() << "MainWindow::updateRecentlyOpenedFiles() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::openRecentProject(QAction *action)
{
    qDebug() << "MainWindow::openRecentProject() - START";

    QString projectFilePath = action->data().toString();

    if (!projectFilePath.isEmpty()) {
        prm->openProject(projectFilePath);
    }

    qDebug() << "MainWindow::openRecentProject() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::openRecentFile(QAction *action)
{
    qDebug() << "MainWindow::openRecentFile() - START";

    QStringList aux = action->data().toString().split("|");
    QString fileName = aux.value(0);
    QString fileType = aux.value(1);

    if (!fileName.isEmpty() && !fileType.isEmpty()) {
        openFile(fileName, fileType);
    }

    qDebug() << "MainWindow::openRecentFile() - STOP";
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
    qDebug() << "MainWindow::solve() - START";

    SolveNetworkDialog dialog(this);
    dialog.exec();

    qDebug() << "MainWindow::solve() - STOP";
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

    // get know info about it
    Document *document = getActiveDocument();
    Q_ASSERT(document!=0 && "document pointer is 0!");
    fileToClose = document->currentFile();
    fileType = document->documentType();

    // close it
    if (ui->mdiArea->subWindowList().size()==1)
        ui->mdiArea->closeAllSubWindows();
    else
        ui->mdiArea->closeActiveSubWindow();

    // run the corresponding callback
    onFileClosed(fileToClose, fileType);
}


/* ===============================================================================================================*/
/**
  *
  */
Document* MainWindow::getActiveDocument()
{
    Document *document = qobject_cast<Document*> (getActiveSubWindow()->widget());

    Q_ASSERT(document!=0 && "document pointer is 0!");
    return document;
}


/* ===============================================================================================================*/
/**
  *
  */
QMdiSubWindow* MainWindow::getActiveSubWindow()
{
    QMdiSubWindow *subWindow = 0;
    if (ui->mdiArea->subWindowList().size()==1)
        subWindow = ui->mdiArea->subWindowList()[0];
    else
        subWindow = ui->mdiArea->activeSubWindow();

    Q_ASSERT(subWindow!=0 && "subWindow pointer is 0!");
    return subWindow;
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::onFileClosed(const QString &fileToClose, const QString &fileType)
{
    // remove the Window menu entry
    QList<QAction*> actions = ui->menu_Windows->actions();
    for (int i=0; i<actions.size(); i++) {
        if (actions[i]->data().toString().split("|").value(0) == fileToClose)
            ui->menu_Windows->removeAction(actions[i]);
    }

    // save the file to the list of the last five recently opened files
    QStringList recentlyOpenedFiles = settings->get("projects/recentlyOpenedFiles").toStringList();
    if (!fileToClose.isEmpty() && !fileType.isEmpty()) {
        if (!recentlyOpenedFiles.contains(fileToClose+"|"+fileType)) {
            if (recentlyOpenedFiles.size()==5) {
                recentlyOpenedFiles.removeAt(0);
            }
            recentlyOpenedFiles.append(fileToClose+"|"+fileType);
            settings->set("projects/recentlyOpenedFiles",recentlyOpenedFiles);
        }
        else {
            int index = recentlyOpenedFiles.indexOf(fileToClose+"|"+fileType);
            std::cout << index << std::endl;
            recentlyOpenedFiles.removeAt(index);
            recentlyOpenedFiles.append(fileToClose+"|"+fileType);
        }

        // and "commit" the change
        updateRecentlyOpenedFiles();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::closeFile(const QString &filePath)
{
    // change focus to the corresponding subwindow if exists and close it
    QMdiSubWindow *existing = ApplicationComponentProvider::findMdiSubWindow(filePath);
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
    Document *document = getActiveDocument();
    Q_ASSERT(document!=0 && "document pointer is 0!");
    if (document!=0)
        document->save();
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::saveAs()
{
    Document *document = getActiveDocument();
    Q_ASSERT(document!=0 && "document pointer is 0!");
    if (document!=0)
            document->saveAs();
 }


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::saveAll()
{
    for (int i=0; i<ui->mdiArea->subWindowList().size(); i++) {
        Document *document = qobject_cast<Document*> (ui->mdiArea->subWindowList()[i]->widget());
        Q_ASSERT(document!=0 && "document pointer is 0!");
        if (document!=0)
            document->save();
    }
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::onSubWindowStateChanged()
{
    qDebug() << "MainWindow::onSubWindowStateChanged() - START";

    // get know the subwindows count
    int n = ui->mdiArea->subWindowList().size();

    // get know the number of the modified ones
    int modified = 0;
    for (int i=0; i<n; i++) {
        if (ui->mdiArea->subWindowList()[i]->isWindowModified())
            modified++;
    }

    // if there are no subwindows opened or none of the opened ones is modified disable save actions
    if (n==0 || modified==0) {
        ui->action_Save->setEnabled(false);
        ui->action_Save_As->setEnabled(false);
        ui->action_Save_All->setEnabled(false);
    }
    // else enable those functions again
    else {
        ui->action_Save->setEnabled(true);
        ui->action_Save_As->setEnabled(true);
        ui->action_Save_All->setEnabled(true);
    }

    qDebug() << "MainWindow::onSubWindowStateChanged() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::onSubWindowActivated(QMdiSubWindow *subWindow)
{
    qDebug() << "MainWindow::onSubWindowActivated() - START";

    // if doesn't deal the last subwindow, change the title
    if (subWindow!=0) {
        setWindowModified(subWindow->isWindowModified());
        setWindowTitle(windowTitle().split(" - ").value(0).trimmed()+" - "+subWindow->windowTitle());
        ui->action_Close_File->setEnabled(true);
        ui->action_Print->setEnabled(true);
        if (!calculating && getActiveDocument()->documentType()=="network") {
            ui->menu_Network->setEnabled(true);
            ui->action_Solve->setEnabled(true);
        }
        else {
            ui->menu_Network->setEnabled(false);
            ui->action_Solve->setEnabled(false);
        }
    }

    // if it was last, disable the close file and print action
    else {
        setWindowTitle(windowTitle().split(" - ").value(0).trimmed());
        ui->action_Close_File->setEnabled(false);
        ui->action_Print->setEnabled(false);
        ui->menu_Network->setEnabled(false);
        ui->action_Solve->setEnabled(false);
    }

    qDebug() << "MainWindow::onSubWindowActivated() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::onWindowItemClicked(QAction *action)
{
    setActiveSubWindow(action->data().toString());
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::setActiveSubWindow(const QString &filePath)
{
    QMdiSubWindow *subWindow = 0;
    for (int i=0; i<ui->mdiArea->subWindowList().size(); i++) {
        subWindow = ui->mdiArea->subWindowList()[i];

        Q_ASSERT(subWindow!=0 && "subWindow pointer is 0!");

        Document *document = qobject_cast<Document*> (subWindow->widget());

        Q_ASSERT(document!=0 && "document pointer is 0!");

        if (document->currentFile() == filePath)
            ui->mdiArea->setActiveSubWindow(subWindow);
    }
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


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::updateFileMenuEntries(Project *project)
{
    qDebug() << "MainWindow::updateFileMenuEntries() - START";

    Q_ASSERT(project!=0 && "project pointer is 0!");

    if (project) {
        // set close project action to active project
        QString text = ui->action_Close_Project->text();
        text = text.left(text.indexOf("(")).trimmed();
        ui->action_Close_Project->setText(" "+text+" ("+project->getName()+")");

        // set project properties action to active project
        text = ui->action_Project_Properties->text();
        text = text.left(text.indexOf("(")).trimmed();
        ui->action_Project_Properties->setText(" "+text+" ("+project->getName()+")");

        // disable the new network action if deals the single network project and already has one added
        if (project->getType()=="SingleNetworkProject" && project->getNetworks().size()==1)
            ui->action_New_Network->setEnabled(false);
        else
            ui->action_New_Network->setEnabled(true);
    }

    qDebug() << "MainWindow::updateFileMenuEntries() - STOP";
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::onAdjustmentSuccess(const QString xmlStream, const QString txtStream, Document *document, AdjustmentSetting *as)
{
    Q_ASSERT(as!=0 && "adjustmentSetting pointer is 0!");
    Q_ASSERT(document!=0 && "document pointer is 0!");
    Project *project = document->getAsociatedProject();
    Q_ASSERT(project!=0 && " project pointer is 0!");

    QString filePath;
    // if calculated, add subwindow with the xml output
    if (!xmlStream.isEmpty()) {
        filePath = project->getLocation()+project->getName()+"/Solutions/"+document->userFriendlyCurrentFile().split(".").value(0)+"__"+as->getName()+".xml";
        openNewSubWindow(filePath, "solution-xml", project, xmlStream);
    }

    // if calculated, add subwindow with the txt output
    if (!txtStream.isEmpty()) {
        filePath = project->getLocation()+project->getName()+"/Solutions/"+document->userFriendlyCurrentFile().split(".").value(0)+"__"+as->getName()+".txt";
        openNewSubWindow(filePath, "txt", project, txtStream);
    }

    setCalculating(false);
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::onAdjustmentFailure(const QString errorMessage)
{
    QMessageBox::critical(this, "Adjustment failure", errorMessage);
    setCalculating(false);
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::setCalculating(bool calculating)
{
    this->calculating = calculating;
    ui->action_Solve->setEnabled(!calculating);
}


/* ===============================================================================================================*/
/**
  *
  */
void MainWindow::closeSubWindow(int number)
{
    QMdiSubWindow *subWindow = ui->mdiArea->subWindowList()[number];

    Q_ASSERT(subWindow!=0 && "subwindow pointer is 0!");

    Document *document = qobject_cast<Document*> (subWindow->widget());

    Q_ASSERT(document!=0 && "document pointer is 0!");

    subWindow->close();

    // run the corresponding callback
    onFileClosed(document->currentFile(), document->documentType());
}
