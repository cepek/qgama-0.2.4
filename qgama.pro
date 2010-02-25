TEMPLATE=subdirs

CONFIG+=ordered all

all {
    SUBDIRS=libqgama \
    gama-local \
    gama-local-xml2txt \
    gama-g3 \
    qgama-plugins \
    qgama-core/src/qgama-core.pro
}

libqtgama {
    SUBDIRS=libqgama
}

gama-local {
    SUBDIRS=libqgama \
    gama-local \
    gama-local-xml2txt
}

gama-g3 {
    SUBDIRS=libqgama \
    gama-g3
}

qgama {
    SUBDIRS=qgama-plugins \
    qgama-core/src/qgama-core.pro
}

qgama-core {
    SUBDIRS=qgama-core/src/qgama-core.pro
}

qgama-plugins {
    SUBDIRS=qgama-plugins
}
