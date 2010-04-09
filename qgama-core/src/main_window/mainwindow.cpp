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

#include "mainwindow.h"
#include "../../../config.h"
#include "../plugins_manager/pluginsmanagerdialog.h"
#include "../preferences/preferencesdialog.h"
#include "aboutqgamadialog.h"
#include "aboutgnugamadialog.h"
#include "../projects_manager/newprojectdialog.h"
#include "../projects_manager/newfilewizard.h"
#include "texteditor.h"
#include "../utils/utils.h"
#include "../factory.h"
#include "../projects_manager/projectpropertiesdialog.h"

//#include <gama-local-main.h>

#include <iostream>

using namespace QGamaCore;


/*
 __  __      _   __      ___         _
|  \/  |__ _(_)_ \ \    / (_)_ _  __| |_____ __ __
| |\/| / _` | | ' \ \/\/ /| | ' \/ _` / _ \ V  V /
|_|  |_\__,_|_|_||_\_/\_/ |_|_||_\__,_\___/\_/\_/

*/
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

    // setting bottom left corner of dock widget area
    this->setCorner(Qt::BottomLeftCorner,Qt::LeftDockWidgetArea);

    // set output dock widget to hidden at startup
    ui->dockWidget_Output->setVisible(false);

    // setting the menu initial state
    ui->action_Toolbar_File->setChecked(ui->toolBar_File->isEnabled());
    ui->menu_Network->setEnabled(false);

    // setting window title
    this->setWindowTitle("QGama " + QString(QGAMA_VERSION) + tr(" (using GNU GamaLib ") + QString(VERSION) + ")");

    // setting mdiArea subwindows icons
    ui->mdiArea->setWindowIcon(QIcon(":/images/icons/notes-32.png"));

    // if there are no projects opened
    if (prm->projectsCount()==0) {
        decreaseProjectsCount();
    }

    // add close button to the tabs in mdi area and also block the default context menu over it
    foreach (QTabBar* tab, ui->mdiArea->findChildren<QTabBar*>()) {
        tab->setTabsClosable(true);
        tab->setContextMenuPolicy(Qt::NoContextMenu);

        connect(tab,SIGNAL(tabCloseRequested(int)),ui->mdiArea,SLOT(closeActiveSubWindow()));
    }
}

/*
 /\/|_  __      _   __      ___         _
|/\/  \/  |__ _(_)_ \ \    / (_)_ _  __| |_____ __ __
   | |\/| / _` | | ' \ \/\/ /| | ' \/ _` / _ \ V  V /
   |_|  |_\__,_|_|_||_\_/\_/ |_|_||_\__,_\___/\_/\_/

*/
/** Destructor.
  *
  * Deletes dynamicaly created structures.
  */
MainWindow::~MainWindow()
{
    settings->set("MainWindow/size",size());
    settings->set("MainWindow/pos",pos());

    ui->mdiArea->closeAllSubWindows();
    Factory::releaseSettings(settings);
    Factory::releasePluginsManager(pm);
    Factory::releaseProjectsManager(prm);

    delete ui;
    delete pmd;
}


/*
            _        ___                      _   _
 _ __  __ _| |_____ / __|___ _ _  _ _  ___ __| |_(_)___ _ _  ___
| '  \/ _` | / / -_) (__/ _ \ ' \| ' \/ -_) _|  _| / _ \ ' \(_-<
|_|_|_\__,_|_\_\___|\___\___/_||_|_||_\___\__|\__|_\___/_||_/__/

*/
/** Makes signal slot connections.
  *
  */
void MainWindow::makeConnections()
{
    // File menu actions
    connect(ui->action_New_Project, SIGNAL(triggered()), this, SLOT(newProject()));
    connect(ui->action_New_File, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->action_Quit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->action_Open_File, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->action_Open_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->action_Close_Project, SIGNAL(triggered()), this, SLOT(closeProject()));
    connect(ui->menu_Open_Recent_Project, SIGNAL(triggered(QAction*)), this, SLOT(openRecentProject(QAction*)));
    connect(ui->action_Close_All_Projects, SIGNAL(triggered()), this, SLOT(closeAllProjects()));
    connect(ui->action_Project_Properties, SIGNAL(triggered()), this, SLOT(projectProperties()));
    connect(ui->action_Close_File, SIGNAL(triggered()), this, SLOT(closeFile()));

    // Edit menu actions
    connect(ui->action_Plugins, SIGNAL(triggered()), this, SLOT(pluginManagerDialog()));
    connect(ui->action_Preferences, SIGNAL(triggered()), this, SLOT(preferencesDialog()));

    // Networks menu actions
    connect(ui->action_Solve, SIGNAL(triggered()), this, SLOT(solve()));

    // Window menu actions
    connect(ui->action_Output, SIGNAL(triggered()), this, SLOT(openOutputDock()));
    connect(ui->action_Projects, SIGNAL(triggered()), this, SLOT(openProjectsDock()));

    // About menu actions
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(aboutQGamaDialog()));
    connect(ui->action_About_GNU_Gama, SIGNAL(triggered()), this, SLOT(aboutGnuGamaDialog()));
    connect(ui->action_About_Qt, SIGNAL(triggered()), this, SLOT(aboutQtDialog()));
}


/*
                 _ ___      _   _   _
 _ _ ___ __ _ __| / __| ___| |_| |_(_)_ _  __ _ ___
| '_/ -_) _` / _` \__ \/ -_)  _|  _| | ' \/ _` (_-<
|_| \___\__,_\__,_|___/\___|\__|\__|_|_||_\__, /__/
                                          |___/

*/
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
        prm->openProject(openedProjects[i], false);
    }

    // set active project
    if (openedProjects.size()>0) {
        QStringList activeProject = settings->get("projects/activeProject").toStringList();
        prm->setActiveProject(activeProject.value(0),activeProject.value(1));
        ui->treeWidget_Projects->collapseNonActiveProjects();
    }

    // initialize recently opened projects
    updateRecentlyOpenedProjects();

    // resize and move
    if (!settings->get("MainWindow/size").isNull())
        resize(settings->get("MainWindow/size").toSize());
    if (!settings->get("MainWindow/pos").isNull())
        move(settings->get("MainWindow/pos").toPoint());
}


/*
    _                       ___             _
 __| |_  __ _ _ _  __ _ ___| __|_ _____ _ _| |_
/ _| ' \/ _` | ' \/ _` / -_) _|\ V / -_) ' \  _|
\__|_||_\__,_|_||_\__, \___|___|\_/\___|_||_\__|
                  |___/

*/
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


/*
    _             ___             _
 __| |___ ___ ___| __|_ _____ _ _| |_
/ _| / _ (_-</ -_) _|\ V / -_) ' \  _|
\__|_\___/__/\___|___|\_/\___|_||_\__|

*/
/**
  *
  */
void MainWindow::closeEvent(QCloseEvent *event)
{
    /*
    QList<QMdiSubWindow*> subWindows = ui->mdiArea->subWindowList();
    for (QList<QMdiSubWindow*>::iterator i=subWindows.begin(); i!=subWindows.end(); ++i) {
        (*i)->close();
    }
    event->accept();
    */
    ui->mdiArea->closeAllSubWindows();
}


/*
      _           _      __  __                             ___  _      _
 _ __| |_  _ __ _(_)_ _ |  \/  |__ _ _ _  __ _ __ _ ___ _ _|   \(_)__ _| |___  __ _
| '_ \ | || / _` | | ' \| |\/| / _` | ' \/ _` / _` / -_) '_| |) | / _` | / _ \/ _` |
| .__/_|\_,_\__, |_|_||_|_|  |_\__,_|_||_\__,_\__, \___|_| |___/|_\__,_|_\___/\__, |
|_|         |___/                             |___/                           |___/

*/
/** Opens modal Plugin Manager dialog.
  *
  */
void MainWindow::pluginManagerDialog()
{
    pmd->exec();
}


/*
               __                            ___  _      _
 _ __ _ _ ___ / _|___ _ _ ___ _ _  __ ___ __|   \(_)__ _| |___  __ _
| '_ \ '_/ -_)  _/ -_) '_/ -_) ' \/ _/ -_|_-< |) | / _` | / _ \/ _` |
| .__/_| \___|_| \___|_| \___|_||_\__\___/__/___/|_\__,_|_\___/\__, |
|_|                                                            |___/

*/
/** Opens modal Preferences dialog.
  *
  */
void MainWindow::preferencesDialog()
{
    pd->exec();
}


/*
      _              _    ___   ___                 ___  _      _
 __ _| |__  ___ _  _| |_ / _ \ / __|__ _ _ __  __ _|   \(_)__ _| |___  __ _
/ _` | '_ \/ _ \ || |  _| (_) | (_ / _` | '  \/ _` | |) | / _` | / _ \/ _` |
\__,_|_.__/\___/\_,_|\__|\__\_\\___\__,_|_|_|_\__,_|___/|_\__,_|_\___/\__, |
                                                                      |___/

*/
/** Opens modal About QGama dialog.
  *
  */
void MainWindow::aboutQGamaDialog()
{
    AboutQGamaDialog dialog(this);
    dialog.exec();
}


/*
      _              _    ___           ___                 ___  _      _
 __ _| |__  ___ _  _| |_ / __|_ _ _  _ / __|__ _ _ __  __ _|   \(_)__ _| |___  __ _
/ _` | '_ \/ _ \ || |  _| (_ | ' \ || | (_ / _` | '  \/ _` | |) | / _` | / _ \/ _` |
\__,_|_.__/\___/\_,_|\__|\___|_||_\_,_|\___\__,_|_|_|_\__,_|___/|_\__,_|_\___/\__, |
                                                                              |___/

*/
/** Opens modal About GNU Gama dialog.
  *
  */
void MainWindow::aboutGnuGamaDialog()
{
    AboutGnuGamaDialog dialog(this);
    dialog.exec();
}


/*
      _              _    ___  _   ___  _      _
 __ _| |__  ___ _  _| |_ / _ \| |_|   \(_)__ _| |___  __ _
/ _` | '_ \/ _ \ || |  _| (_) |  _| |) | / _` | / _ \/ _` |
\__,_|_.__/\___/\_,_|\__|\__\_\\__|___/|_\__,_|_\___/\__, |
                                                     |___/

*/
/** Opens modal About Qt dialog.
  *
  */
void MainWindow::aboutQtDialog()
{
    QMessageBox::aboutQt(this);
}


/*
                    _   _          _____         _ _              ___ _ _      _                  _        _
 ___ _ _    __ _ __| |_(_)___ _ _ |_   _|__  ___| | |__  __ _ _ _| __(_) |___ | |_ ___  __ _ __ _| |___ __| |
/ _ \ ' \  / _` / _|  _| / _ \ ' \  | |/ _ \/ _ \ | '_ \/ _` | '_| _|| | / -_)|  _/ _ \/ _` / _` | / -_) _` |
\___/_||_|_\__,_\__|\__|_\___/_||_|_|_|\___/\___/_|_.__/\__,_|_|_|_| |_|_\___|_\__\___/\__, \__, |_\___\__,_|
        |___|                    |___|                        |___|         |___|      |___/|___/

*/
/** Slot for mantaining "View->Toolbar->File" checkbox synchronized with the toolbar visibility.
  *
  */
void MainWindow::on_action_Toolbar_File_toggled(bool checked)
{
    ui->toolBar_File->setVisible(checked);
}


/*
                    ___          _        _      ___          _
 ___ _ __  ___ _ _ | _ \_ _ ___ (_)___ __| |_ __|   \ ___  __| |__
/ _ \ '_ \/ -_) ' \|  _/ '_/ _ \| / -_) _|  _(_-< |) / _ \/ _| / /
\___/ .__/\___|_||_|_| |_| \___// \___\__|\__/__/___/\___/\__|_\_\
    |_|                       |__/

*/
/** Slot for making visible the Projects dock widget.
  *
  */
void MainWindow::openProjectsDock()
{
    ui->dockWidget_Projects->setVisible(true);
}


/*
                    ___       _             _   ___          _
 ___ _ __  ___ _ _ / _ \ _  _| |_ _ __ _  _| |_|   \ ___  __| |__
/ _ \ '_ \/ -_) ' \ (_) | || |  _| '_ \ || |  _| |) / _ \/ _| / /
\___/ .__/\___|_||_\___/ \_,_|\__| .__/\_,_|\__|___/\___/\__|_\_\
    |_|                          |_|

  */
/** Slot for making visible the Output dock widget.
  *
  */
void MainWindow::openOutputDock()
{
    ui->dockWidget_Output->setVisible(true);
}


/*
                 ___ _ _
 _ _  _____ __ _| __(_) |___
| ' \/ -_) V  V / _|| | / -_)
|_||_\___|\_/\_/|_| |_|_\___|

*/
/**
  *
  */
void MainWindow::newFile()
{
    NewFileWizard wizard(this);
    wizard.exec();
}


/*
                 ___          _        _
 _ _  _____ __ _| _ \_ _ ___ (_)___ __| |_
| ' \/ -_) V  V /  _/ '_/ _ \| / -_) _|  _|
|_||_\___|\_/\_/|_| |_| \___// \___\__|\__|
                           |__/

*/
/**
  *
  */
void MainWindow::newProject()
{
    NewProjectDialog dialog(this);
    dialog.exec();
}


/*
                    ___ _ _
 ___ _ __  ___ _ _ | __(_) |___
/ _ \ '_ \/ -_) ' \| _|| | / -_)
\___/ .__/\___|_||_|_| |_|_\___|
    |_|

*/
/**
  *
  */
void MainWindow::openFile()
{
    QDir dir;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), dir.home().absolutePath()+"/QGamaProjects", tr("QGama Network Files (*.xml *.gkf);; QGama Solution Files (*.xml *.txt *.html);; All Files"));
    openFile(fileName);
}


/*
                    ___ _ _
 ___ _ __  ___ _ _ | __(_) |___
/ _ \ '_ \/ -_) ' \| _|| | / -_)
\___/ .__/\___|_||_|_| |_|_\___|
    |_|

*/
/**
  *
  */
void MainWindow::openFile(const QString &file)
{
    if (!file.isEmpty()) {
        QMdiSubWindow *existing = Utils::findMdiSubWindow(file);
        if (existing) {
            ui->mdiArea->setActiveSubWindow(existing);
            return;
        }

        TextEditor *child = new TextEditor;

        ui->mdiArea->addSubWindow(child);
        if (child->loadFile(file)) {
            child->showMaximized();
        } else {
            child->close();
        }

        Q_FOREACH (QAction* action, ui->mdiArea->findChildren<QAction*>())
            {
            if (action->shortcut().toString()=="Ctrl+W")
                action->setShortcut(QKeySequence(""));
            }
    }
}


/*
                    ___          _        _
 ___ _ __  ___ _ _ | _ \_ _ ___ (_)___ __| |_
/ _ \ '_ \/ -_) ' \|  _/ '_/ _ \| / -_) _|  _|
\___/ .__/\___|_||_|_| |_| \___// \___\__|\__|
    |_|                       |__/

*/
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


/*
    _             ___          _        _
 __| |___ ___ ___| _ \_ _ ___ (_)___ __| |_
/ _| / _ (_-</ -_)  _/ '_/ _ \| / -_) _|  _|
\__|_\___/__/\___|_| |_| \___// \___\__|\__|
                            |__/

*/
/**
  *
  */
void MainWindow::closeProject()
{
    prm->closeActiveProject();
}


/*
    _                             ___          _        _       ___              _
 __| |___ __ _ _ ___ __ _ ___ ___| _ \_ _ ___ (_)___ __| |_ ___/ __|___ _  _ _ _| |_
/ _` / -_) _| '_/ -_) _` (_-</ -_)  _/ '_/ _ \| / -_) _|  _(_-< (__/ _ \ || | ' \  _|
\__,_\___\__|_| \___\__,_/__/\___|_| |_| \___// \___\__|\__/__/\___\___/\_,_|_||_\__|
                                            |__/

*/
/**
  *
  */
void MainWindow::decreaseProjectsCount()
{
    ui->dockWidget_Projects->setWindowTitle(QObject::tr("Projects") + " ("+QString::number(prm->projectsCount()) + QObject::tr(" Opened)"));

    if (prm->projectsCount()==0) {
        // hide some actions in the file menu
        ui->action_New_File->setEnabled(false);
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


/*
 _                              ___          _        _       ___              _
(_)_ _  __ _ _ ___ __ _ ___ ___| _ \_ _ ___ (_)___ __| |_ ___/ __|___ _  _ _ _| |_
| | ' \/ _| '_/ -_) _` (_-</ -_)  _/ '_/ _ \| / -_) _|  _(_-< (__/ _ \ || | ' \  _|
|_|_||_\__|_| \___\__,_/__/\___|_| |_| \___// \___\__|\__/__/\___\___/\_,_|_||_\__|
                                          |__/

*/
/**
  *
  */
void MainWindow::increaseProjectsCount()
{    
    ui->dockWidget_Projects->setWindowTitle(QObject::tr("Projects") + " ("+QString::number(prm->projectsCount()) + QObject::tr(" Opened)"));

    if (prm->projectsCount()==1) {
        // hide some actions in the file menu
        ui->action_New_File->setEnabled(true);
        ui->action_Close_File->setEnabled(true);
        ui->action_Close_Project->setEnabled(true);
        ui->action_Close_All_Projects->setEnabled(true);
        ui->action_Project_Properties->setEnabled(true);

        // hide treewidget with projects
        ui->treeWidget_Projects->setStyleSheet("");
    }
}


/*
               _      _       ___                _   _       ___                        _ ___          _        _
 _  _ _ __  __| |__ _| |_ ___| _ \___ __ ___ _ _| |_| |_  _ / _ \ _ __  ___ _ _  ___ __| | _ \_ _ ___ (_)___ __| |_ ___
| || | '_ \/ _` / _` |  _/ -_)   / -_) _/ -_) ' \  _| | || | (_) | '_ \/ -_) ' \/ -_) _` |  _/ '_/ _ \| / -_) _|  _(_-<
 \_,_| .__/\__,_\__,_|\__\___|_|_\___\__\___|_||_\__|_|\_, |\___/| .__/\___|_||_\___\__,_|_| |_| \___// \___\__|\__/__/
     |_|                                               |__/      |_|                                |__/

*/
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


/*
                    ___                _   ___          _        _
 ___ _ __  ___ _ _ | _ \___ __ ___ _ _| |_| _ \_ _ ___ (_)___ __| |_
/ _ \ '_ \/ -_) ' \|   / -_) _/ -_) ' \  _|  _/ '_/ _ \| / -_) _|  _|
\___/ .__/\___|_||_|_|_\___\__\___|_||_\__|_| |_| \___// \___\__|\__|
    |_|                                              |__/

*/
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


/*
    _               _   _ _ ___          _        _
 __| |___ ___ ___  /_\ | | | _ \_ _ ___ (_)___ __| |_ ___
/ _| / _ (_-</ -_)/ _ \| | |  _/ '_/ _ \| / -_) _|  _(_-<
\__|_\___/__/\___/_/ \_\_|_|_| |_| \___// \___\__|\__/__/
                                      |__/

*/
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


/**
  *
  */
void MainWindow::projectProperties()
{
    ProjectPropertiesDialog dialog(this);
    dialog.exec();
}


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


/**
  *
  */
void MainWindow::closeFile()
{
    ui->mdiArea->closeActiveSubWindow();;
}
