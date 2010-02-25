TEMPLATE = lib
TARGET = $$qtLibraryTarget(xmlvalidation)
DESTDIR = ../../bin/plugins
CONFIG += plugin
INCLUDEPATH += ../../
HEADERS = xmlvalidationplugin.h \
    xmlvalidationdialog.h
SOURCES = xmlvalidationplugin.cpp \
    xmlvalidationdialog.cpp
RESOURCES += xmlvalidationplugin.qrc #\
#../../qgama-core/src/qgama-core.qrc
UI_DIR = ui
MOC_DIR = .moc/release-shared
OBJECTS_DIR = .obj/release-shared
RCC_DIR = .rcc/release-shared
FORMS += xmlvalidationdialog.ui
