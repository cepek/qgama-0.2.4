# dependency to qgama-core
unix:qgamacore.commands = cd ../qgama-core/src && $$QMAKE_QMAKE qgama-core.pro && make
win32:qgamacore.commands = cd ../qgama-core/src && $$QMAKE_QMAKE qgama-core.pro && mingw32-make.exe
QMAKE_EXTRA_TARGETS += qgamacore
PRE_TARGETDEPS+=qgamacore

TEMPLATE      = subdirs
SUBDIRS       = xmlvalidation
