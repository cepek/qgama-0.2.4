# generating of config.h file with the version info
unix:version.commands = cd ../scripts && g++ -o version version.cpp && ./version
win32:version.commands = cd ../scripts && mingw32-g++.exe -o version version.cpp && version.exe
QMAKE_EXTRA_TARGETS += version
PRE_TARGETDEPS += version

# add a file to be cleaned
QMAKE_CLEAN += ../config.h

# dependency to libqgama
unix:libqgama.commands = cd ../libqgama && $$QMAKE_QMAKE libqgama.pro && make
win32:libqgama.commands = cd ../libqgama && $$QMAKE_QMAKE libqgama.pro && mingw32-make.exe
QMAKE_EXTRA_TARGETS += libqgama
PRE_TARGETDEPS+=libqgama

# include options
!include(../options.pri) : error(Couldn't find the options.pri file!)

# initalize the installs target
isEmpty(PREFIX) {
    PREFIX = /usr/local
}
prefix.path = $$PREFIX
target.path = $$prefix.path/bin
INSTALLS += target

# compile in release mode
CONFIG += release

# without qt support
CONFIG -= qt

# disable the thread support, because we don't need it
win32:QMAKE_LFLAGS_EXCEPTIONS_ON = -Wl
win32:QMAKE_CXXFLAGS_EXCEPTIONS_ON = -fexceptions

# link statically with the compiler library
win32:QMAKE_LFLAGS_RELEASE += -static-libgcc

# specify that deals a console application
win32:CONFIG+=console

TARGET=gama-local

TEMPLATE=app

INCLUDEPATH+=../../gama/lib /usr/include

LIBS+=-L../libqgama -lqgama

!GNU_gama_expat_1_1 { LIBS+=-lexpat }

DESTDIR=../bin

HEADERS+=../../gama/bin/gama-local-main.h

SOURCES+=../../gama/bin/gama-local.cpp
