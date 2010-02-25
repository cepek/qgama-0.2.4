TEMPLATE = lib

TARGET = $$qtLibraryTarget(xmlvalidation)

DESTDIR = ../../bin/plugins

CONFIG += plugin release

INCLUDEPATH += ../../

HEADERS = xmlvalidationplugin.h \
    xmlvalidationdialog.h

SOURCES = xmlvalidationplugin.cpp \
    xmlvalidationdialog.cpp

RESOURCES += xmlvalidationplugin.qrc

FORMS += xmlvalidationdialog.ui

UI_DIR = ui
MOC_DIR = .moc/release-shared
OBJECTS_DIR = .obj/release-shared
RCC_DIR = .rcc/release-shared
