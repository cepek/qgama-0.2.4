# include options
!include(../../options.pri) : error(Couldn't find the options.pri file!)

# dependency to qgama-core
qgamacore.commands = cd ../../qgama-core/src && $$QMAKE_QMAKE qgama-core.pro && $$MAKE_COMMAND
QMAKE_EXTRA_TARGETS += qgamacore
PRE_TARGETDEPS+=qgamacore

# make the linker add all symbols, not only used ones, to the dynamic symbol table
unix:QMAKE_LFLAGS += -rdynamic
unix:QMAKE_CXXFLAGS += -rdynamic

# initalize the installs target
isEmpty(PREFIX) {
    PREFIX = /usr/local
}
prefix.path = $$PREFIX
target.path = $$prefix.path/lib/qgama
INSTALLS += target

TEMPLATE = lib

TARGET = $$qtLibraryTarget(xmlvalidation)

DESTDIR = ../../bin/plugins

INCLUDEPATH = ../../

QT += xmlpatterns xml

CONFIG += plugin release

HEADERS = xmlvalidationplugin.h \
    messagehandler.h

SOURCES = xmlvalidationplugin.cpp

UI_DIR = ui
MOC_DIR = .moc/release-shared
OBJECTS_DIR = .obj/release-shared
RCC_DIR = .rcc/release-shared
