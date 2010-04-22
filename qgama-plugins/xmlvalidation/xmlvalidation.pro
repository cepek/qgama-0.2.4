TEMPLATE = lib

TARGET = $$qtLibraryTarget(xmlvalidation)

DESTDIR = ../../bin/plugins

CONFIG += plugin release

QT += xmlpatterns xml

INCLUDEPATH += ../../ \
../../qgama-core/src/ \
../../qgama-core/src/main_window/ \
../../qgama-core/src/plugins_manager/ \
../../qgama-core/src/projects_manager \
../../qgama-core/src/ui/

HEADERS = xmlvalidationplugin.h \
    messagehandler.h

SOURCES = xmlvalidationplugin.cpp

QMAKE_LFLAGS += -rdynamic
QMAKE_CXXFLAGS += -rdynamic

UI_DIR = ui
MOC_DIR = .moc/release-shared
OBJECTS_DIR = .obj/release-shared
RCC_DIR = .rcc/release-shared
