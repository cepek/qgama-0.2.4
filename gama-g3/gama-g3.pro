# include options
!include(../options.pri) : error(Couldn't find the options.pri file!)

# add a file to be cleaned
QMAKE_CLEAN += ../config.h

# dependency to libqgama
libqgama.commands = cd ../libqgama && $$QMAKE_QMAKE libqgama.pro && $$MAKE_COMMAND
QMAKE_EXTRA_TARGETS += libqgama
PRE_TARGETDEPS+=libqgama

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

TARGET = gama-g3

TEMPLATE = app

INCLUDEPATH += ../../gama/lib

LIBS += -L../libqgama -lqgama

# if include of expath 1.1 is not desired, link with the version installed on host system
!GNU_gama_expat_1_1 {
    LIBS+=-lexpat
}

DESTDIR = ../bin

SOURCES += ../../gama/bin/gama-g3.cpp
