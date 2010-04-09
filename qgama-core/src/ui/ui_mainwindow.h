/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Mar 24 17:00:34 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../projects_manager/projectstreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_New_File;
    QAction *action_Open_File;
    QAction *action_Preferences;
    QAction *action_Plugins;
    QAction *action_Quit;
    QAction *action_Cascade;
    QAction *action_Tile;
    QAction *action_About;
    QAction *action_About_GNU_Gama;
    QAction *action_About_Qt;
    QAction *action_New_Project;
    QAction *action_Open_Project;
    QAction *action_Close_Project;
    QAction *action_Project_Properties;
    QAction *action_Save;
    QAction *action_Save_As;
    QAction *action_Save_All;
    QAction *action_Print;
    QAction *action_Project_1;
    QAction *action_Project_2;
    QAction *action_Project_3;
    QAction *action_Project_4;
    QAction *action_Project_5;
    QAction *action_File_1;
    QAction *action_File_2;
    QAction *action_File_3;
    QAction *action_File_4;
    QAction *action_File_5;
    QAction *action_Close_All_Projects;
    QAction *action_Toolbar_File;
    QAction *action_Projects;
    QAction *action_Output;
    QAction *action_Close_File;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Open_Recent_Project;
    QMenu *menu_Open_Recent_File;
    QMenu *menu_Tools;
    QMenu *menu_Points;
    QMenu *menu_Observations;
    QMenu *menu_Network;
    QMenu *menu_Windows;
    QMenu *menu_Edit;
    QMenu *menu_Help;
    QMenu *menu_View;
    QMenu *menu_Toolbars;
    QToolBar *toolBar_File;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_Projects;
    QWidget *dockWidget_Projects_Contents;
    QVBoxLayout *verticalLayout;
    QGamaCore::ProjectsTreeWidget *treeWidget_Projects;
    QDockWidget *dockWidget_Output;
    QWidget *dockWidget_Output_Contents;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/babieca-64.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setDockNestingEnabled(false);
        action_New_File = new QAction(MainWindow);
        action_New_File->setObjectName(QString::fromUtf8("action_New_File"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/file-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_New_File->setIcon(icon1);
        action_New_File->setIconVisibleInMenu(true);
        action_Open_File = new QAction(MainWindow);
        action_Open_File->setObjectName(QString::fromUtf8("action_Open_File"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/standardbutton-open-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open_File->setIcon(icon2);
        action_Open_File->setIconVisibleInMenu(true);
        action_Preferences = new QAction(MainWindow);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/icons/configure-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Preferences->setIcon(icon3);
        action_Preferences->setIconVisibleInMenu(true);
        action_Plugins = new QAction(MainWindow);
        action_Plugins->setObjectName(QString::fromUtf8("action_Plugins"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/icons/plugin-manager-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Plugins->setIcon(icon4);
        action_Plugins->setIconVisibleInMenu(true);
        action_Quit = new QAction(MainWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/icons/exit-16.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Quit->setIcon(icon5);
        action_Quit->setIconVisibleInMenu(true);
        action_Cascade = new QAction(MainWindow);
        action_Cascade->setObjectName(QString::fromUtf8("action_Cascade"));
        action_Tile = new QAction(MainWindow);
        action_Tile->setObjectName(QString::fromUtf8("action_Tile"));
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        action_About_GNU_Gama = new QAction(MainWindow);
        action_About_GNU_Gama->setObjectName(QString::fromUtf8("action_About_GNU_Gama"));
        action_About_Qt = new QAction(MainWindow);
        action_About_Qt->setObjectName(QString::fromUtf8("action_About_Qt"));
        action_New_Project = new QAction(MainWindow);
        action_New_Project->setObjectName(QString::fromUtf8("action_New_Project"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/icons/newdirectory-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_New_Project->setIcon(icon6);
        action_New_Project->setIconVisibleInMenu(true);
        action_Open_Project = new QAction(MainWindow);
        action_Open_Project->setObjectName(QString::fromUtf8("action_Open_Project"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/icons/diropen-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open_Project->setIcon(icon7);
        action_Open_Project->setIconVisibleInMenu(true);
        action_Close_Project = new QAction(MainWindow);
        action_Close_Project->setObjectName(QString::fromUtf8("action_Close_Project"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/icons/standardbutton-cancel-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Close_Project->setIcon(icon8);
        action_Close_Project->setIconVisibleInMenu(true);
        action_Project_Properties = new QAction(MainWindow);
        action_Project_Properties->setObjectName(QString::fromUtf8("action_Project_Properties"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/icons/standardbutton-save-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Save->setIcon(icon9);
        action_Save->setIconVisibleInMenu(true);
        action_Save_As = new QAction(MainWindow);
        action_Save_As->setObjectName(QString::fromUtf8("action_Save_As"));
        action_Save_All = new QAction(MainWindow);
        action_Save_All->setObjectName(QString::fromUtf8("action_Save_All"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/icons/save_all-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Save_All->setIcon(icon10);
        action_Print = new QAction(MainWindow);
        action_Print->setObjectName(QString::fromUtf8("action_Print"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/icons/print-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Print->setIcon(icon11);
        action_Print->setIconVisibleInMenu(true);
        action_Project_1 = new QAction(MainWindow);
        action_Project_1->setObjectName(QString::fromUtf8("action_Project_1"));
        action_Project_2 = new QAction(MainWindow);
        action_Project_2->setObjectName(QString::fromUtf8("action_Project_2"));
        action_Project_3 = new QAction(MainWindow);
        action_Project_3->setObjectName(QString::fromUtf8("action_Project_3"));
        action_Project_4 = new QAction(MainWindow);
        action_Project_4->setObjectName(QString::fromUtf8("action_Project_4"));
        action_Project_5 = new QAction(MainWindow);
        action_Project_5->setObjectName(QString::fromUtf8("action_Project_5"));
        action_File_1 = new QAction(MainWindow);
        action_File_1->setObjectName(QString::fromUtf8("action_File_1"));
        action_File_2 = new QAction(MainWindow);
        action_File_2->setObjectName(QString::fromUtf8("action_File_2"));
        action_File_3 = new QAction(MainWindow);
        action_File_3->setObjectName(QString::fromUtf8("action_File_3"));
        action_File_4 = new QAction(MainWindow);
        action_File_4->setObjectName(QString::fromUtf8("action_File_4"));
        action_File_5 = new QAction(MainWindow);
        action_File_5->setObjectName(QString::fromUtf8("action_File_5"));
        action_Close_All_Projects = new QAction(MainWindow);
        action_Close_All_Projects->setObjectName(QString::fromUtf8("action_Close_All_Projects"));
        action_Close_All_Projects->setIconVisibleInMenu(true);
        action_Toolbar_File = new QAction(MainWindow);
        action_Toolbar_File->setObjectName(QString::fromUtf8("action_Toolbar_File"));
        action_Toolbar_File->setCheckable(true);
        action_Projects = new QAction(MainWindow);
        action_Projects->setObjectName(QString::fromUtf8("action_Projects"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/images/icons/draft-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Projects->setIcon(icon12);
        action_Projects->setIconVisibleInMenu(true);
        action_Output = new QAction(MainWindow);
        action_Output->setObjectName(QString::fromUtf8("action_Output"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/images/icons/notes-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Output->setIcon(icon13);
        action_Output->setIconVisibleInMenu(true);
        action_Close_File = new QAction(MainWindow);
        action_Close_File->setObjectName(QString::fromUtf8("action_Close_File"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/images/icons/standardbutton-close-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_Close_File->setIcon(icon14);
        action_Close_File->setIconVisibleInMenu(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setDocumentMode(false);

        verticalLayout_2->addWidget(mdiArea);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 25));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Open_Recent_Project = new QMenu(menu_File);
        menu_Open_Recent_Project->setObjectName(QString::fromUtf8("menu_Open_Recent_Project"));
        menu_Open_Recent_File = new QMenu(menu_File);
        menu_Open_Recent_File->setObjectName(QString::fromUtf8("menu_Open_Recent_File"));
        menu_Tools = new QMenu(menuBar);
        menu_Tools->setObjectName(QString::fromUtf8("menu_Tools"));
        menu_Points = new QMenu(menuBar);
        menu_Points->setObjectName(QString::fromUtf8("menu_Points"));
        menu_Observations = new QMenu(menuBar);
        menu_Observations->setObjectName(QString::fromUtf8("menu_Observations"));
        menu_Network = new QMenu(menuBar);
        menu_Network->setObjectName(QString::fromUtf8("menu_Network"));
        menu_Windows = new QMenu(menuBar);
        menu_Windows->setObjectName(QString::fromUtf8("menu_Windows"));
        menu_Edit = new QMenu(menuBar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menu_View = new QMenu(menuBar);
        menu_View->setObjectName(QString::fromUtf8("menu_View"));
        menu_Toolbars = new QMenu(menu_View);
        menu_Toolbars->setObjectName(QString::fromUtf8("menu_Toolbars"));
        MainWindow->setMenuBar(menuBar);
        toolBar_File = new QToolBar(MainWindow);
        toolBar_File->setObjectName(QString::fromUtf8("toolBar_File"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar_File);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget_Projects = new QDockWidget(MainWindow);
        dockWidget_Projects->setObjectName(QString::fromUtf8("dockWidget_Projects"));
        dockWidget_Projects->setLayoutDirection(Qt::LeftToRight);
        dockWidget_Projects->setFloating(false);
        dockWidget_Projects->setFeatures(QDockWidget::DockWidgetClosable);
        dockWidget_Projects->setAllowedAreas(Qt::LeftDockWidgetArea);
        dockWidget_Projects_Contents = new QWidget();
        dockWidget_Projects_Contents->setObjectName(QString::fromUtf8("dockWidget_Projects_Contents"));
        verticalLayout = new QVBoxLayout(dockWidget_Projects_Contents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        treeWidget_Projects = new QGamaCore::ProjectsTreeWidget(dockWidget_Projects_Contents);
        treeWidget_Projects->setObjectName(QString::fromUtf8("treeWidget_Projects"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(237, 236, 235, 0));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 0));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(246, 245, 245, 0));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(118, 118, 117, 0));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(158, 157, 157, 0));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(246, 245, 245, 127));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        treeWidget_Projects->setPalette(palette);
        treeWidget_Projects->setStyleSheet(QString::fromUtf8(""));
        treeWidget_Projects->setProperty("alternatingRowColors", QVariant(false));
        treeWidget_Projects->setProperty("headerHidden", QVariant(true));

        verticalLayout->addWidget(treeWidget_Projects);

        dockWidget_Projects->setWidget(dockWidget_Projects_Contents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_Projects);
        dockWidget_Output = new QDockWidget(MainWindow);
        dockWidget_Output->setObjectName(QString::fromUtf8("dockWidget_Output"));
        dockWidget_Output->setStyleSheet(QString::fromUtf8("background:white"));
        dockWidget_Output->setFeatures(QDockWidget::DockWidgetClosable);
        dockWidget_Output->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidget_Output_Contents = new QWidget();
        dockWidget_Output_Contents->setObjectName(QString::fromUtf8("dockWidget_Output_Contents"));
        dockWidget_Output->setWidget(dockWidget_Output_Contents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_Output);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Edit->menuAction());
        menuBar->addAction(menu_View->menuAction());
        menuBar->addAction(menu_Points->menuAction());
        menuBar->addAction(menu_Observations->menuAction());
        menuBar->addAction(menu_Network->menuAction());
        menuBar->addAction(menu_Tools->menuAction());
        menuBar->addAction(menu_Windows->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_New_Project);
        menu_File->addAction(action_New_File);
        menu_File->addSeparator();
        menu_File->addAction(action_Open_Project);
        menu_File->addAction(menu_Open_Recent_Project->menuAction());
        menu_File->addAction(action_Open_File);
        menu_File->addAction(menu_Open_Recent_File->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(action_Close_File);
        menu_File->addAction(action_Close_Project);
        menu_File->addAction(action_Close_All_Projects);
        menu_File->addSeparator();
        menu_File->addAction(action_Project_Properties);
        menu_File->addSeparator();
        menu_File->addAction(action_Save);
        menu_File->addAction(action_Save_As);
        menu_File->addAction(action_Save_All);
        menu_File->addSeparator();
        menu_File->addAction(action_Print);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);
        menu_Open_Recent_Project->addAction(action_Project_1);
        menu_Open_Recent_Project->addAction(action_Project_2);
        menu_Open_Recent_Project->addAction(action_Project_3);
        menu_Open_Recent_Project->addAction(action_Project_4);
        menu_Open_Recent_Project->addAction(action_Project_5);
        menu_Open_Recent_File->addAction(action_File_1);
        menu_Open_Recent_File->addAction(action_File_2);
        menu_Open_Recent_File->addAction(action_File_3);
        menu_Open_Recent_File->addAction(action_File_4);
        menu_Open_Recent_File->addAction(action_File_5);
        menu_Windows->addAction(action_Projects);
        menu_Windows->addAction(action_Output);
        menu_Windows->addSeparator();
        menu_Windows->addAction(action_Cascade);
        menu_Windows->addAction(action_Tile);
        menu_Edit->addAction(action_Plugins);
        menu_Edit->addAction(action_Preferences);
        menu_Help->addAction(action_About);
        menu_Help->addAction(action_About_GNU_Gama);
        menu_Help->addAction(action_About_Qt);
        menu_Help->addSeparator();
        menu_View->addAction(menu_Toolbars->menuAction());
        menu_Toolbars->addAction(action_Toolbar_File);
        toolBar_File->addAction(action_New_File);
        toolBar_File->addAction(action_New_Project);
        toolBar_File->addAction(action_Open_Project);
        toolBar_File->addAction(action_Save_All);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
#ifndef QT_NO_TOOLTIP
        MainWindow->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        MainWindow->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        action_New_File->setText(QApplication::translate("MainWindow", " &New File...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_New_File->setToolTip(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        action_New_File->setStatusTip(QApplication::translate("MainWindow", "Create new file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        action_New_File->setWhatsThis(QApplication::translate("MainWindow", "New File (File Menu)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        action_New_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        action_Open_File->setText(QApplication::translate("MainWindow", " &Open File", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Open_File->setToolTip(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        action_Open_File->setStatusTip(QApplication::translate("MainWindow", "Open existing file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        action_Open_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        action_Preferences->setText(QApplication::translate("MainWindow", " Pr&eferences", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Preferences->setToolTip(QApplication::translate("MainWindow", "Preferences", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        action_Preferences->setStatusTip(QApplication::translate("MainWindow", "Change program's preferences.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        action_Preferences->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0, QApplication::UnicodeUTF8));
        action_Plugins->setText(QApplication::translate("MainWindow", " &Plugins", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        action_Plugins->setStatusTip(QApplication::translate("MainWindow", "Manage Plugins.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        action_Plugins->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+P", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("MainWindow", " &Exit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        action_Quit->setStatusTip(QApplication::translate("MainWindow", "Exit the program.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        action_Quit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_Cascade->setText(QApplication::translate("MainWindow", " &Cascade", 0, QApplication::UnicodeUTF8));
        action_Tile->setText(QApplication::translate("MainWindow", " &Tile", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("MainWindow", " &About", 0, QApplication::UnicodeUTF8));
        action_About->setShortcut(QApplication::translate("MainWindow", "Ctrl+F1", 0, QApplication::UnicodeUTF8));
        action_About_GNU_Gama->setText(QApplication::translate("MainWindow", " About &GNU Gama", 0, QApplication::UnicodeUTF8));
        action_About_Qt->setText(QApplication::translate("MainWindow", " About &Qt", 0, QApplication::UnicodeUTF8));
        action_New_Project->setText(QApplication::translate("MainWindow", " &New Project...", 0, QApplication::UnicodeUTF8));
        action_New_Project->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+N", 0, QApplication::UnicodeUTF8));
        action_Open_Project->setText(QApplication::translate("MainWindow", " &Open Project...", 0, QApplication::UnicodeUTF8));
        action_Open_Project->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+O", 0, QApplication::UnicodeUTF8));
        action_Close_Project->setText(QApplication::translate("MainWindow", " &Close Project", 0, QApplication::UnicodeUTF8));
        action_Project_Properties->setText(QApplication::translate("MainWindow", " Project Proper&ties", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("MainWindow", " &Save", 0, QApplication::UnicodeUTF8));
        action_Save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        action_Save_As->setText(QApplication::translate("MainWindow", " &Save As...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Save_As->setToolTip(QApplication::translate("MainWindow", "Save As...", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Save_All->setText(QApplication::translate("MainWindow", " &Save All", 0, QApplication::UnicodeUTF8));
        action_Save_All->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        action_Print->setText(QApplication::translate("MainWindow", " &Print", 0, QApplication::UnicodeUTF8));
        action_Print->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        action_Project_1->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        action_Project_2->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        action_Project_3->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        action_Project_4->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        action_Project_5->setText(QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8));
        action_File_1->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        action_File_2->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        action_File_3->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        action_File_4->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        action_File_5->setText(QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8));
        action_Close_All_Projects->setText(QApplication::translate("MainWindow", " &Close All Projects", 0, QApplication::UnicodeUTF8));
        action_Toolbar_File->setText(QApplication::translate("MainWindow", " &File", 0, QApplication::UnicodeUTF8));
        action_Projects->setText(QApplication::translate("MainWindow", " &Projects", 0, QApplication::UnicodeUTF8));
        action_Projects->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", 0, QApplication::UnicodeUTF8));
        action_Output->setText(QApplication::translate("MainWindow", " &Output", 0, QApplication::UnicodeUTF8));
        action_Output->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", 0, QApplication::UnicodeUTF8));
        action_Close_File->setText(QApplication::translate("MainWindow", " &Close File", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Open_Recent_Project->setTitle(QApplication::translate("MainWindow", " Open Recent Project", 0, QApplication::UnicodeUTF8));
        menu_Open_Recent_File->setTitle(QApplication::translate("MainWindow", " Open Recent &File", 0, QApplication::UnicodeUTF8));
        menu_Tools->setTitle(QApplication::translate("MainWindow", "&Tools", 0, QApplication::UnicodeUTF8));
        menu_Points->setTitle(QApplication::translate("MainWindow", "&Points", 0, QApplication::UnicodeUTF8));
        menu_Observations->setTitle(QApplication::translate("MainWindow", "&Observations", 0, QApplication::UnicodeUTF8));
        menu_Network->setTitle(QApplication::translate("MainWindow", "&Network", 0, QApplication::UnicodeUTF8));
        menu_Windows->setTitle(QApplication::translate("MainWindow", "&Windows", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menu_View->setTitle(QApplication::translate("MainWindow", "View", 0, QApplication::UnicodeUTF8));
        menu_Toolbars->setTitle(QApplication::translate("MainWindow", " &Toolbars", 0, QApplication::UnicodeUTF8));
        toolBar_File->setWindowTitle(QApplication::translate("MainWindow", "File Toolbar", 0, QApplication::UnicodeUTF8));
        dockWidget_Projects->setWindowTitle(QApplication::translate("MainWindow", "Projects", 0, QApplication::UnicodeUTF8));
        dockWidget_Output->setWindowTitle(QApplication::translate("MainWindow", "Output", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
