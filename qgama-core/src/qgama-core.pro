# version of the QGamaCore GUI
QGAMA_VERSION = 0.1.5

# dependency to libqgama
unix:libqgama.commands = cd ../../libqgama && $$QMAKE_QMAKE libqgama.pro && make
win32:libqgama.commands = cd ../../libqgama && $$QMAKE_QMAKE libqgama.pro && mingw32-make.exe
QMAKE_EXTRA_TARGETS += libqgama
PRE_TARGETDEPS += libqgama

# generating of config.h file with the version info
unix:version.commands = cd ../../scripts && g++ -o version version.cpp && ./version
win32:version.commands = cd ../../scripts && mingw32-g++.exe -o version version.cpp && version.exe
QMAKE_EXTRA_TARGETS += version
PRE_TARGETDEPS += version

# including project options
!include(../../options.pri) : error(Couldn't find the options.pri file!)

# removing the thread support, static linking againts libgcc for windows
win32:QMAKE_LFLAGS_EXCEPTIONS_ON = -Wl
win32:QMAKE_CXXFLAGS_EXCEPTIONS_ON = -fexceptions
win32:QMAKE_LFLAGS_RELEASE += -static-libgcc

# static linking against libgama.a
LIBS += -L../../libqgama -lqgama

#unix:LIBS += -lXext -lm -ldl -lSM -lICE
#unix:QMAKE_LFLAGS_SHAPP += -static
#unix:QMAKE_CXXFLAGS_RELEASE = -Wall -pedantic -ansi

TARGET = qgama

QT += xml

CONFIG += release

TEMPLATE = app

DESTDIR = ../../bin

INCLUDEPATH += ui \
    ../../ \
    ../../../gama/gama-local \
    ../../../gama/lib

SOURCES += main.cpp \
    factory.cpp \
    # preferences
    preferences/settingsimpl.cpp \
    preferences/preferencesdialog.cpp \
    # plugins_manager
    plugins_manager/pluginsmanagerdialog.cpp \
    plugins_manager/pluginsmanagerimpl.cpp \
    # utils
    utils/utils.cpp \
    # main_window
    main_window/mainwindow.cpp \
    main_window/aboutqgamadialog.cpp \
    main_window/aboutgnugamadialog.cpp \
    main_window/texteditor.cpp \
    # projects_manager
    projects_manager/projectsmanagerimpl.cpp \
    projects_manager/newprojectdialog.cpp \
    projects_manager/project.cpp \
    projects_manager/projectstreewidget.cpp \
    projects_manager/newfilewizardpage.cpp \
    projects_manager/newfilewizardpage2.cpp \
    projects_manager/newfilewizard.cpp \
    projects_manager/projectpropertiesdialog.cpp

HEADERS += factory.h \
    # preferences
    preferences/settings.h \
    preferences/settingsimpl.h \
    preferences/preferencesdialog.h \
    # plugins_manager
    plugins_manager/pluginsmanagerdialog.h \
    plugins_manager/pluginsmanager.h \
    plugins_manager/pluginsmanagerimpl.h \
    plugins_manager/plugininterface.h \
    # utils
    utils/utils.h \
    # main_window
    main_window/mainwindow.h \
    main_window/aboutqgamadialog.h \
    main_window/aboutgnugamadialog.h \
    main_window/texteditor.h \
    # projects_manager
    projects_manager/projectsmanager.h \
    projects_manager/projectsmanagerimpl.h \
    projects_manager/newprojectdialog.h \
    projects_manager/project.h \
    projects_manager/projectstreewidget.h \
    projects_manager/newfilewizardpage.h \
    projects_manager/newfilewizardpage2.h \
    projects_manager/newfilewizard.h \
    projects_manager/projectpropertiesdialog.h \
    projects_manager/file.h

    
FORMS += \
    # preferences
    preferences/preferencesdialog.ui \
    # plugins_manager
    plugins_manager/pluginsmanagerdialog.ui \
    # main_window
    main_window/mainwindow.ui \
    main_window/aboutqgamadialog.ui \
    main_window/aboutgnugamadialog.ui \
    # projects_manager
    projects_manager/newprojectdialog.ui \
    projects_manager/newfilewizardpage.ui \
    projects_manager/newfilewizardpage2.ui \
    projects_manager/projectpropertiesdialog.ui

RESOURCES += qgama-core.qrc

TRANSLATIONS = ../translations/qgamacore_cs_CZ.ts

UI_DIR = ui
MOC_DIR = .moc/release-shared
OBJECTS_DIR = .obj/release-shared
RCC_DIR = .rcc/release-shared

RC_FILE = qgama.rc
