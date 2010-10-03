# include options
!include(../options.pri) : error(Couldn't find the options.pri file!)

# dependency to qgama-core
qgamacore.commands = cd ../qgama-core/src && $$QMAKE_QMAKE qgama-core.pro && $$MAKE_COMMAND
QMAKE_EXTRA_TARGETS += qgamacore
PRE_TARGETDEPS+=qgamacore

TEMPLATE      = subdirs
SUBDIRS       = xmlvalidation
