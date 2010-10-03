# include options
!include(../options.pri) : error(Couldn't find the options.pri file!)

# generating of config.h file with the version info
version.commands = cd ../scripts/version && $$QMAKE_QMAKE version.pro && $$MAKE_COMMAND && ./version
QMAKE_EXTRA_TARGETS += version
PRE_TARGETDEPS += version

# generating of libqgama.pro headers and sources section
libqgama_files.commands = cd ../scripts/libgama_files && $$QMAKE_QMAKE libgama_files.pro && $$MAKE_COMMAND && ./libgama_files
QMAKE_EXTRA_TARGETS += libgama_files
PRE_TARGETDEPS += libgama_files

# add a file to be cleaned
QMAKE_CLEAN += ../config.h

# compile in release mode and as a static library
CONFIG += release
CONFIG += staticlib

# place it at the same directory
DESTDIR=./

# without qt support
CONFIG -= qt

# disable the thread support, because we don't need it
win32:QMAKE_LFLAGS_EXCEPTIONS_ON = -Wl
win32:QMAKE_CXXFLAGS_EXCEPTIONS_ON = -fexceptions

TARGET = qgama

TEMPLATE = lib

INCLUDEPATH += ../../gama/lib \
               ../ \
                /usr/include

# if include of expath 1.1 is desired, add corresponding includepaths, sources and headers
GNU_gama_expat_1_1 {
    INCLUDEPATH += ../../gama/lib/expat/xmlparse \
       ../../gama/lib/expat/xmlwf \
       ../../gama/lib/expat/xmltok

    SOURCES += ../../gama/lib/expat/xmlparse/xmlparse.c \
        ../../gama/lib/expat/xmlparse/hashtable.c \
        ../../gama/lib/expat/xmltok/xmltok.c \
        ../../gama/lib/expat/xmltok/xmlrole.c \
        ../../gama/lib/expat/xmlwf/codepage.c

    HEADERS += ../../gama/lib/expat/xmlwf/codepage.h \
        ../../gama/lib/expat/xmltok/xmlrole.h \
        ../../gama/lib/expat/xmlparse/hashtable.h \
        ../../gama/lib/expat/xmlparse/xmlparse.h \
        ../../gama/lib/expat/xmltok/xmltok.h
}

# if include of expath 1.1 is not desired, link with the version installed on host system
!GNU_gama_expat_1_1 {
    LIBS+=-lexpat
}

HEADERS += \ 
../../gama/lib/gnu_gama/e3.h \
../../gama/lib/gnu_gama/ellipsoid.h \
../../gama/lib/gnu_gama/ellipsoids.h \
../../gama/lib/gnu_gama/exception.h \
../../gama/lib/gnu_gama/gon2deg.h \
../../gama/lib/gnu_gama/intfloat.h \
../../gama/lib/gnu_gama/latlong.h \
../../gama/lib/gnu_gama/list.h \
../../gama/lib/gnu_gama/model.h \
../../gama/lib/gnu_gama/movetofront.h \
../../gama/lib/gnu_gama/obsdata.h \
../../gama/lib/gnu_gama/outstream.h \
../../gama/lib/gnu_gama/pointbase.h \
../../gama/lib/gnu_gama/radian.h \
../../gama/lib/gnu_gama/rand.h \
../../gama/lib/gnu_gama/statan.h \
../../gama/lib/gnu_gama/version.h \
../../gama/lib/gnu_gama/xml_expat.h \
../../gama/lib/gnu_gama/adj/adj_base.h \
../../gama/lib/gnu_gama/adj/adj_basefull.h \
../../gama/lib/gnu_gama/adj/adj_basesparse.h \
../../gama/lib/gnu_gama/adj/adj_chol.h \
../../gama/lib/gnu_gama/adj/adj_chol_implementation.h \
../../gama/lib/gnu_gama/adj/adj_envelope.h \
../../gama/lib/gnu_gama/adj/adj_envelope_implementation.h \
../../gama/lib/gnu_gama/adj/adj.h \
../../gama/lib/gnu_gama/adj/adj_gso.h \
../../gama/lib/gnu_gama/adj/adj_svd.h \
../../gama/lib/gnu_gama/adj/envelope.h \
../../gama/lib/gnu_gama/adj/homogenization.h \
../../gama/lib/gnu_gama/g3/g3_adjres.h \
../../gama/lib/gnu_gama/g3/g3_cluster.h \
../../gama/lib/gnu_gama/g3/g3_model.h \
../../gama/lib/gnu_gama/g3/g3_observation.h \
../../gama/lib/gnu_gama/g3/g3_parameter.h \
../../gama/lib/gnu_gama/g3/g3_point.h \
../../gama/lib/gnu_gama/g3/g3_write_observation_xml.h \
../../gama/lib/gnu_gama/sparse/intlist.h \
../../gama/lib/gnu_gama/sparse/sbdiagonal.h \
../../gama/lib/gnu_gama/sparse/smatrix_graph_connected.h \
../../gama/lib/gnu_gama/sparse/smatrix_graph.h \
../../gama/lib/gnu_gama/sparse/smatrix_ordering.h \
../../gama/lib/gnu_gama/sparse/smatrix.h \
../../gama/lib/gnu_gama/sparse/svector.h \
../../gama/lib/gnu_gama/xml/baseparser.h \
../../gama/lib/gnu_gama/xml/dataobject.h \
../../gama/lib/gnu_gama/xml/dataparser.h \
../../gama/lib/gnu_gama/xml/encoding.h \
../../gama/lib/gnu_gama/xml/localnetwork.h \
../../gama/lib/gnu_gama/xml/localnetwork_adjustment_results.h \
../../gama/lib/gnu_gama/xml/gkfparser.h \
../../gama/lib/gnu_gama/local/angobs.h \
../../gama/lib/gnu_gama/local/bpoint.h \
../../gama/lib/gnu_gama/local/c/api/capi_exception.h \
../../gama/lib/gnu_gama/local/c/api/capi_gkfparser.h \
../../gama/lib/gnu_gama/local/c/api/capi_locnet.h \
../../gama/lib/gnu_gama/local/c/api/capi_output_file.h \
../../gama/lib/gnu_gama/local/c/api/capi_private_exception.h \
../../gama/lib/gnu_gama/local/c_api.h \
../../gama/lib/gnu_gama/local/cluster.h \
../../gama/lib/gnu_gama/local/exception.h \
../../gama/lib/gnu_gama/local/float.h \
../../gama/lib/gnu_gama/local/itstream.h \
../../gama/lib/gnu_gama/local/language.h \
../../gama/lib/gnu_gama/local/linearization.h \
../../gama/lib/gnu_gama/local/acord/approx_heights.h \
../../gama/lib/gnu_gama/local/acord/approx_vectors.h \
../../gama/lib/gnu_gama/local/acord.h \
../../gama/lib/gnu_gama/local/acord/reduce_observations.h \
../../gama/lib/gnu_gama/local/acord/reduce_to_ellipsoid.h \
../../gama/lib/gnu_gama/local/gamadata.h \
../../gama/lib/gnu_gama/local/gkf2sql.h \
../../gama/lib/gnu_gama/local/lcoords.h \
../../gama/lib/gnu_gama/local/local_linearization.h \
../../gama/lib/gnu_gama/local/lpoint.h \
../../gama/lib/gnu_gama/local/median/g2d_cogo.h \
../../gama/lib/gnu_gama/local/median/g2d_coordinates.h \
../../gama/lib/gnu_gama/local/median/g2d_exception.h \
../../gama/lib/gnu_gama/local/median/g2d_helper.h \
../../gama/lib/gnu_gama/local/median/g2d_point.h \
../../gama/lib/gnu_gama/local/network_chol.h \
../../gama/lib/gnu_gama/local/network_env.h \
../../gama/lib/gnu_gama/local/network_gso.h \
../../gama/lib/gnu_gama/local/network.h \
../../gama/lib/gnu_gama/local/network_svd.h \
../../gama/lib/gnu_gama/local/orientation.h \
../../gama/lib/gnu_gama/local/pobs/bearing.h \
../../gama/lib/gnu_gama/local/pobs/format.h \
../../gama/lib/gnu_gama/local/results/text/adjusted_observations.h \
../../gama/lib/gnu_gama/local/results/text/adjusted_unknowns.h \
../../gama/lib/gnu_gama/local/results/text/approximate_coordinates.h \
../../gama/lib/gnu_gama/local/results/text/error_ellipses.h \
../../gama/lib/gnu_gama/local/results/text/fixed_points.h \
../../gama/lib/gnu_gama/local/results/text/general_parameters.h \
../../gama/lib/gnu_gama/local/results/text/network_description.h \
../../gama/lib/gnu_gama/local/results/text/outlying_abs_terms.h \
../../gama/lib/gnu_gama/local/results/text/reduced_observations.h \
../../gama/lib/gnu_gama/local/results/text/reduced_observations_to_ellipsoid.h \
../../gama/lib/gnu_gama/local/results/text/residuals_observations.h \
../../gama/lib/gnu_gama/local/results/text/test_linearization.h \
../../gama/lib/gnu_gama/local/results/text/underline.h \
../../gama/lib/gnu_gama/local/local_revision.h \
../../gama/lib/gnu_gama/local/matvec.h \
../../gama/lib/gnu_gama/local/medianf.h \
../../gama/lib/gnu_gama/local/observation.h \
../../gama/lib/gnu_gama/local/pointid.h \
../../gama/lib/gnu_gama/local/readsabw.h \
../../gama/lib/gnu_gama/local/revision.h \
../../gama/lib/gnu_gama/local/skipcomm.h \
../../gama/lib/matvec/array.h \
../../gama/lib/matvec/bandmat.h \
../../gama/lib/matvec/choldec.h \
../../gama/lib/matvec/covmat.h \
../../gama/lib/matvec/gso.h \
../../gama/lib/matvec/hilbert.h \
../../gama/lib/matvec/inderr.h \
../../gama/lib/matvec/jacobian.h \
../../gama/lib/matvec/matbase.h \
../../gama/lib/matvec/mat.h \
../../gama/lib/matvec/matvecbase.h \
../../gama/lib/matvec/matvec.h \
../../gama/lib/matvec/memrep.h \
../../gama/lib/matvec/pinv.h \
../../gama/lib/matvec/sortvec.h \
../../gama/lib/matvec/svd.h \
../../gama/lib/matvec/symmat.h \
../../gama/lib/matvec/transmat.h \
../../gama/lib/matvec/transvec.h \
../../gama/lib/matvec/vecbase.h \
../../gama/lib/matvec/vec.h

SOURCES += \ 
../../gama/lib/gnu_gama/e3.cpp \
../../gama/lib/gnu_gama/ellipsoid.cpp \
../../gama/lib/gnu_gama/ellipsoids.cpp \
../../gama/lib/gnu_gama/gon2deg.cpp \
../../gama/lib/gnu_gama/latlong.cpp \
../../gama/lib/gnu_gama/outstream.cpp \
../../gama/lib/gnu_gama/rand.cpp \
../../gama/lib/gnu_gama/statan.cpp \
../../gama/lib/gnu_gama/version.cpp \
../../gama/lib/gnu_gama/adj/adj.cpp \
../../gama/lib/gnu_gama/g3/g3_adjres.cpp \
../../gama/lib/gnu_gama/g3/g3_cluster.cpp \
../../gama/lib/gnu_gama/g3/g3_model.cpp \
../../gama/lib/gnu_gama/g3/g3_model_init.cpp \
../../gama/lib/gnu_gama/g3/g3_model_linearization.cpp \
../../gama/lib/gnu_gama/g3/g3_model_revision.cpp \
../../gama/lib/gnu_gama/g3/g3_model_write_xml_adjustment_results.cpp \
../../gama/lib/gnu_gama/g3/g3_point.cpp \
../../gama/lib/gnu_gama/g3/g3_write_observation_xml.cpp \
../../gama/lib/gnu_gama/xml/baseparser.cpp \
../../gama/lib/gnu_gama/xml/dataobject.cpp \
../../gama/lib/gnu_gama/xml/dataparser_adj.cpp \
../../gama/lib/gnu_gama/xml/dataparser.cpp \
../../gama/lib/gnu_gama/xml/dataparser_g3.cpp \
../../gama/lib/gnu_gama/xml/dataparser_g3adj.cpp \
../../gama/lib/gnu_gama/xml/encoding_cp1251.cpp \
../../gama/lib/gnu_gama/xml/encoding.cpp \
../../gama/lib/gnu_gama/xml/encoding_unknown_handler.cpp \
../../gama/lib/gnu_gama/xml/localnetwork.cpp \
../../gama/lib/gnu_gama/xml/localnetwork_adjustment_results.cpp \
../../gama/lib/gnu_gama/xml/gkfparser.cpp \
../../gama/lib/gnu_gama/local/c/api/capi_exception.cpp \
../../gama/lib/gnu_gama/local/c/api/capi_gkfparser.cpp \
../../gama/lib/gnu_gama/local/c/api/capi_locnet.cpp \
../../gama/lib/gnu_gama/local/c/api/capi_output_file.cpp \
../../gama/lib/gnu_gama/local/language.cpp \
../../gama/lib/gnu_gama/local/acord/approx_heights.cpp \
../../gama/lib/gnu_gama/local/acord/approx_vectors.cpp \
../../gama/lib/gnu_gama/local/acord.cpp \
../../gama/lib/gnu_gama/local/acord/reduce_observations.cpp \
../../gama/lib/gnu_gama/local/acord/reduce_to_ellipsoid.cpp \
../../gama/lib/gnu_gama/local/gkf2sql.cpp \
../../gama/lib/gnu_gama/local/median/g2d_cogo.cpp \
../../gama/lib/gnu_gama/local/median/g2d_coordinates.cpp \
../../gama/lib/gnu_gama/local/median/g2d_helper.cpp \
../../gama/lib/gnu_gama/local/median/g2d_point.cpp \
../../gama/lib/gnu_gama/local/network.cpp \
../../gama/lib/gnu_gama/local/observation_local.cpp \
../../gama/lib/gnu_gama/local/orientation.cpp \
../../gama/lib/gnu_gama/local/pobs/format.cpp \
../../gama/lib/gnu_gama/local/pobs/write.cpp \
../../gama/lib/gnu_gama/local/results/text/underline.cpp \
../../gama/lib/gnu_gama/local/observation.cpp \
../../gama/lib/gnu_gama/local/observation/write/angle.cpp \
../../gama/lib/gnu_gama/local/observation/write/direction.cpp \
../../gama/lib/gnu_gama/local/observation/write/distance.cpp \
../../gama/lib/gnu_gama/local/observation/write/hdiff.cpp \
../../gama/lib/gnu_gama/local/observation/write/sdistance.cpp \
../../gama/lib/gnu_gama/local/observation/write/xyz.cpp \
../../gama/lib/gnu_gama/local/observation/write/xyzdiff.cpp \
../../gama/lib/gnu_gama/local/observation/write/zangle.cpp \
../../gama/lib/gnu_gama/local/pointid.cpp \
../../gama/lib/gnu_gama/local/skipcomm.cpp
