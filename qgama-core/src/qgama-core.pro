# version of the QGamaCore GUI
QGAMA_VERSION = 0.0.2

# generating of config.h file with the version info
!exists(../config.h) { 
    unix:version.commands = cd \
        ../../scripts \
        && \
        g++ \
        -o \
        version \
        -D"'QGAMA_VERSION=\"$${QGAMA_VERSION}\"'" \
        version.cpp \
        && \
        ./version
    win32:version.commands = cd \
        ../../scripts \
        && \
        mingw32-g++.exe \
        -o \
        version \
        -D"'QGAMA_VERSION=\"$${QGAMA_VERSION}\"'" \
        version.cpp \
        && \
        version.exe
    QMAKE_EXTRA_TARGETS += version
    PRE_TARGETDEPS += version
}

# dependency to libqgama
unix:libqgama.commands = cd \
    ../../libqgama \
    && \
    $$QMAKE_QMAKE \
    libqgama.pro \
    && \
    make
win32:libqgama.commands = cd \
    ../../libqgama \
    && \
    $$QMAKE_QMAKE \
    libqgama.pro \
    && \
    minqw32-make.exe
QMAKE_EXTRA_TARGETS += libqgama
PRE_TARGETDEPS += libqgama
!include(../../options.pri):error(Couldn't find the options.pri file!)
LIBS += -L../../libqgama \
    -lqgama
TARGET = qgama
TEMPLATE = app
DESTDIR = ../../bin
SOURCES += main.cpp \
    main_window/mainwindow.cpp \
    preferences/qgamasettingsimpl.cpp \
    plugin_manager/pluginmanagerdialog.cpp \
    plugin_manager/pluginmanagerimpl.cpp \
    preferences/preferencesdialog.cpp \
    utils/utils.cpp \
    main_window/aboutqgamadialog.cpp \
    main_window/aboutgnugamadialog.cpp \
    main_window/network.cpp \
    projects_manager/projectsmanagerimpl.cpp \
    projects_manager/newprojectdialog.cpp
HEADERS += main_window/mainwindow.h \
    preferences/qgamasettings.h \
    preferences/qgamasettingsimpl.h \
    preferences/preferencesdialog.h \
    plugin_manager/pluginmanagerdialog.h \
    plugin_manager/pluginmanager.h \
    plugin_manager/pluginmanagerimpl.h \
    plugin_manager/plugininterface.h \
    utils/utils.h \
    main_window/aboutqgamadialog.h \
    main_window/aboutgnugamadialog.h \
    main_window/network.h \
    projects_manager/projectsmanager.h \
    projects_manager/projectsmanagerimpl.h \
    projects_manager/newprojectdialog.h
FORMS += main_window/mainwindow.ui \
    plugin_manager/pluginmanagerdialog.ui \
    preferences/preferencesdialog.ui \
    main_window/aboutqgamadialog.ui \
    main_window/aboutgnugamadialog.ui \
    projects_manager/newprojectdialog.ui
RESOURCES += qgama-core.qrc
TRANSLATIONS = ../translations/qgamacore_cs_CZ.ts
INCLUDEPATH += ui
UI_DIR = ui
MOC_DIR = .moc/release-shared
OBJECTS_DIR = .obj/release-shared
RCC_DIR = .rcc/release-shared
