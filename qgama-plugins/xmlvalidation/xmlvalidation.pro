# dependency to qgama-core
unix:qgamacore.commands = cd ../../qgama-core/src && $$QMAKE_QMAKE qgama-core.pro && make
win32:qgamacore.commands = cd ../../qgama-core/src && $$QMAKE_QMAKE qgama-core.pro && mingw32-make.exe
QMAKE_EXTRA_TARGETS += qgamacore
PRE_TARGETDEPS+=qgamacore

# make the linker add all symbols, not only used ones, to the dynamic symbol table
QMAKE_LFLAGS += -rdynamic
QMAKE_CXXFLAGS += -rdynamic

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

UI_DIR = ui
MOC_DIR = .moc/release-shared
OBJECTS_DIR = .obj/release-shared
RCC_DIR = .rcc/release-shared
