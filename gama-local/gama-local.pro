# generating of config.h file with the version info
!exists(../config.h) {
    unix:version.commands = cd ../scripts && g++ -o version version.cpp && ./version
    win32:version.commands = cd ../scripts && mingw32-g++.exe -o version version.cpp && version.exe
    QMAKE_EXTRA_TARGETS += version
    PRE_TARGETDEPS += version
}

# dependency to libqgama
unix:libqgama.commands = cd ../libqgama && $$QMAKE_QMAKE libqgama.pro && make
win32:libqgama.commands = cd ../libqgama && $$QMAKE_QMAKE libqgama.pro && minqw32-make.exe
QMAKE_EXTRA_TARGETS += libqgama
PRE_TARGETDEPS+=libqgama

!include(../options.pri) {
    error( Couldn't find the options.pri file! )
}

TARGET=gama-local

TEMPLATE=app

CONFIG += release

win32:CONFIG -= qt
win32:QMAKE_LFLAGS_EXCEPTIONS_ON = -Wl
win32:QMAKE_CXXFLAGS_EXCEPTIONS_ON = -fexceptions
win32:CONFIG+=console

INCLUDEPATH+=../../gama/lib

LIBS+=-L../libqgama -lqgama

DESTDIR=../bin

HEADERS+=../../gama/gama-local/gama-local-main.h

SOURCES+=../../gama/gama-local/gama-local.cpp
