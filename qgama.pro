TEMPLATE=subdirs

CONFIG+=ordered all

all {
    SUBDIRS=libqgama \
    gama-local \
    gama-local-xml2txt \
    gama-g3 \
    qgama-core/src/qgama-core.pro \
    qgama-plugins
}

gama {
    SUBDIRS=libqgama \
    gama-local \
    gama-local-xml2txt \
    gama-g3
}

qgama {
    SUBDIRS=qgama-core/src/qgama-core.pro \
    qgama-plugins
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

libqgama {
    SUBDIRS=libqgama
}

qgama-core {
    SUBDIRS=qgama-core/src/qgama-core.pro
}

qgama-plugins {
    SUBDIRS=qgama-plugins
}
