# generating of config.h file with the version info
unix:version.commands = cd ../scripts && g++ -o version version.cpp && ./version
win32:version.commands = cd ../scripts && mingw32-g++.exe -o version version.cpp && version.exe
QMAKE_EXTRA_TARGETS += version
PRE_TARGETDEPS += version

include(../options.pri) : error(Couldn't find the options.pri file!)

TARGET = qgama

TEMPLATE = lib

CONFIG += release
CONFIG += staticlib

DESTDIR=./

win32:CONFIG -= qt
win32:QMAKE_LFLAGS_EXCEPTIONS_ON = -Wl
win32:QMAKE_CXXFLAGS_EXCEPTIONS_ON = -fexceptions

INCLUDEPATH += ../../gama/lib ../

# expat1.1
GNU_gama_expat_1_1 {
INCLUDEPATH += ../../gama/lib/expat/xmlparse \
   ../../gama/lib/expat/xmlwf \
   ../../gama/lib/expat/xmltok
}

# gnu_gama
SOURCES += ../../gama/lib/gnu_gama/e3.cpp \
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
# gamalib
    ../../gama/lib/gamalib/c/api/capi_exception.cpp \
    ../../gama/lib/gamalib/c/api/capi_gkfparser.cpp \
    ../../gama/lib/gamalib/c/api/capi_locnet.cpp \
    ../../gama/lib/gamalib/c/api/capi_output_file.cpp \
    ../../gama/lib/gamalib/language.cpp \
    ../../gama/lib/gamalib/local/acord/approx_heights.cpp \
    ../../gama/lib/gamalib/local/acord/approx_vectors.cpp \
    ../../gama/lib/gamalib/local/acord.cpp \
    ../../gama/lib/gamalib/local/acord/reduce_observations.cpp \
    ../../gama/lib/gamalib/local/acord/reduce_to_ellipsoid.cpp \
    ../../gama/lib/gamalib/local/median/g2d_cogo.cpp \
    ../../gama/lib/gamalib/local/median/g2d_coordinates.cpp \
    ../../gama/lib/gamalib/local/median/g2d_helper.cpp \
    ../../gama/lib/gamalib/local/median/g2d_point.cpp \
    ../../gama/lib/gamalib/local/network.cpp \
    ../../gama/lib/gamalib/local/observation_local.cpp \
    ../../gama/lib/gamalib/local/orientation.cpp \
    ../../gama/lib/gamalib/local/pobs/format.cpp \
    ../../gama/lib/gamalib/local/pobs/write.cpp \
    ../../gama/lib/gamalib/local/results/text/underline.cpp \
    ../../gama/lib/gamalib/observation.cpp \
    ../../gama/lib/gamalib/observation/write/angle.cpp \
    ../../gama/lib/gamalib/observation/write/direction.cpp \
    ../../gama/lib/gamalib/observation/write/distance.cpp \
    ../../gama/lib/gamalib/observation/write/hdiff.cpp \
    ../../gama/lib/gamalib/observation/write/sdistance.cpp \
    ../../gama/lib/gamalib/observation/write/xyz.cpp \
    ../../gama/lib/gamalib/observation/write/xyzdiff.cpp \
    ../../gama/lib/gamalib/observation/write/zangle.cpp \
    ../../gama/lib/gamalib/pointid.cpp \
    ../../gama/lib/gamalib/skipcomm.cpp \
    ../../gama/lib/gamalib/xml/gkfparser.cpp

GNU_gama_expat_1_1 {
# expat1.1
SOURCES += ../../gama/lib/expat/xmlparse/xmlparse.c \
    ../../gama/lib/expat/xmlparse/hashtable.c \
    ../../gama/lib/expat/xmltok/xmltok.c \
    ../../gama/lib/expat/xmltok/xmlrole.c \
    ../../gama/lib/expat/xmlwf/codepage.c
}

# matvec
HEADERS += ../../gama/lib/matvec/array.h \
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
    ../../gama/lib/matvec/vec.h \
# gnu_gama
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
# gamalib
    ../../gama/lib/gamalib/angobs.h \
    ../../gama/lib/gamalib/bpoint.h \
    ../../gama/lib/gamalib/c/api/capi_exception.h \
    ../../gama/lib/gamalib/c/api/capi_gkfparser.h \
    ../../gama/lib/gamalib/c/api/capi_locnet.h \
    ../../gama/lib/gamalib/c/api/capi_output_file.h \
    ../../gama/lib/gamalib/c/api/capi_private_exception.h \
    ../../gama/lib/gamalib/c_api.h \
    ../../gama/lib/gamalib/cluster.h \
    ../../gama/lib/gamalib/exception.h \
    ../../gama/lib/gamalib/float.h \
    ../../gama/lib/gamalib/itstream.h \
    ../../gama/lib/gamalib/language.h \
    ../../gama/lib/gamalib/linearization.h \
    ../../gama/lib/gamalib/local/acord/approx_heights.h \
    ../../gama/lib/gamalib/local/acord/approx_vectors.h \
    ../../gama/lib/gamalib/local/acord.h \
    ../../gama/lib/gamalib/local/acord/reduce_observations.h \
    ../../gama/lib/gamalib/local/acord/reduce_to_ellipsoid.h \
    ../../gama/lib/gamalib/local/gamadata.h \
    ../../gama/lib/gamalib/local/lcoords.h \
    ../../gama/lib/gamalib/local/linearization/angle.h \
    ../../gama/lib/gamalib/local/linearization/direction.h \
    ../../gama/lib/gamalib/local/linearization/distance.h \
    ../../gama/lib/gamalib/local/linearization.h \
    ../../gama/lib/gamalib/local/linearization/hdiff.h \
    ../../gama/lib/gamalib/local/linearization/sdistance.h \
    ../../gama/lib/gamalib/local/linearization/xyzdiff.h \
    ../../gama/lib/gamalib/local/linearization/xyz.h \
    ../../gama/lib/gamalib/local/linearization/zangle.h \
    ../../gama/lib/gamalib/local/lpoint.h \
    ../../gama/lib/gamalib/local/median/g2d_cogo.h \
    ../../gama/lib/gamalib/local/median/g2d_coordinates.h \
    ../../gama/lib/gamalib/local/median/g2d_exception.h \
    ../../gama/lib/gamalib/local/median/g2d_helper.h \
    ../../gama/lib/gamalib/local/median/g2d_point.h \
    ../../gama/lib/gamalib/local/network_chol.h \
    ../../gama/lib/gamalib/local/network_env.h \
    ../../gama/lib/gamalib/local/network_gso.h \
    ../../gama/lib/gamalib/local/network.h \
    ../../gama/lib/gamalib/local/network_svd.h \
    ../../gama/lib/gamalib/local/orientation.h \
    ../../gama/lib/gamalib/local/pobs/bearing.h \
    ../../gama/lib/gamalib/local/pobs/format.h \
    ../../gama/lib/gamalib/local/results/text/adjusted_observations.h \
    ../../gama/lib/gamalib/local/results/text/adjusted_unknowns.h \
    ../../gama/lib/gamalib/local/results/text/approximate_coordinates.h \
    ../../gama/lib/gamalib/local/results/text/error_ellipses.h \
    ../../gama/lib/gamalib/local/results/text/fixed_points.h \
    ../../gama/lib/gamalib/local/results/text/general_parameters.h \
    ../../gama/lib/gamalib/local/results/text/network_description.h \
    ../../gama/lib/gamalib/local/results/text/outlying_abs_terms.h \
    ../../gama/lib/gamalib/local/results/text/reduced_observations.h \
    ../../gama/lib/gamalib/local/results/text/reduced_observations_to_ellipsoid.h \
    ../../gama/lib/gamalib/local/results/text/residuals_observations.h \
    ../../gama/lib/gamalib/local/results/text/test_linearization.h \
    ../../gama/lib/gamalib/local/results/text/underline.h \
    ../../gama/lib/gamalib/local/revision/angle.h \
    ../../gama/lib/gamalib/local/revision/direction.h \
    ../../gama/lib/gamalib/local/revision/distance.h \
    ../../gama/lib/gamalib/local/revision.h \
    ../../gama/lib/gamalib/local/revision/hdiff.h \
    ../../gama/lib/gamalib/local/revision/sdistance.h \
    ../../gama/lib/gamalib/local/revision/xyzdiff.h \
    ../../gama/lib/gamalib/local/revision/xyz.h \
    ../../gama/lib/gamalib/local/revision/zangle.h \
    ../../gama/lib/gamalib/matvec.h \
    ../../gama/lib/gamalib/medianf.h \
    ../../gama/lib/gamalib/observation.h \
    ../../gama/lib/gamalib/pointid.h \
    ../../gama/lib/gamalib/readsabw.h \
    ../../gama/lib/gamalib/revision.h \
    ../../gama/lib/gamalib/skipcomm.h \
    ../../gama/lib/gamalib/xml/gkfparser.h \
    ../config.h

GNU_gama_expat_1_1 {
# expat1.1
HEADERS += ../../gama/lib/expat/xmlwf/codepage.h \
    ../../gama/lib/expat/xmltok/xmlrole.h \
    ../../gama/lib/expat/xmlparse/hashtable.h \
    ../../gama/lib/expat/xmlparse/xmlparse.h \
    ../../gama/lib/expat/xmltok/xmltok.h
}
