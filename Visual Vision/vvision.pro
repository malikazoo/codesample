#-------------------------------------------------
#
# Project created by QtCreator 2015-12-07T22:41:16
#
#-------------------------------------------------

QT       += core gui

LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vvision
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    filter/filter.cpp \
    viewer.cpp \
    filtermap.cpp \
    filterfactory.cpp \
    filterregister.cpp \
    filter/fgrayscale.cpp \
    filter/fcolor.cpp \
    viewscene.cpp \
    data/data.cpp \
    input/input.cpp \
    output/output.cpp \
    input/ivideo.cpp \
    data/dimage3.cpp \
    data/dimage1.cpp \
    data/dnone.cpp \
    data/dpoint.cpp \
    data/dline.cpp \
    general.cpp \
    output/oscreen.cpp \
    listgph.cpp \
    listgphscene.cpp \
    gphlistitem.cpp \
    inputfactorybase.cpp \
    listitem.cpp \
    outputfactorybase.cpp \
    filter/fsplit.cpp \
    filter/fcombine.cpp \
    vview.cpp \
    mapobj.cpp \
    input/iimage.cpp \
    filebrowser.cpp \
    filter/fsobel.cpp \
    input/iimageconfig.cpp \
    input/ivideoconfig.cpp \
    output/oscreenconfig.cpp \
    filter/fsobeldialog.cpp \
    filter/fcolordialog.cpp \
    filter/fcombinedialog.cpp \
    filter/fgrayscaledialog.cpp \
    filter/fsplitdialog.cpp \
    filter/fdialate.cpp \
    filter/ferode.cpp \
    filter/ferodedialog.cpp \
    filter/flaplacian.cpp \
    filter/fblur.cpp \
    filter/flaplaciandialog.cpp \
    filter/fblurdialog.cpp \
    filter/fdialatedialog.cpp \
    input/icamera.cpp \
    input/icameradialog.cpp \
    filter/fthreshold.cpp \
    filter/fthresholddialog.cpp \
    data/dint.cpp \
    data/dreal.cpp \
    filter/fresize.cpp \
    filter/fresizedialog.cpp \
    filter/fhoughcircle.cpp \
    filter/fhoughcircledialog.cpp \
    filter/fdrawcircle.cpp \
    filter/fdrawcircledialog.cpp \
    data/dcircle.cpp \
    data/dlist.cpp \
    data/dmatrix.cpp \
    filter/fcanny.cpp \
    filter/fcannydialog.cpp \
    filter/fhoughlines.cpp \
    filter/fdrawlines.cpp \
    filter/fdrawlinesdialog.cpp \
    filter/fhoughlinedialog.cpp \
    filter/fdistance.cpp \
    filter/fdistancedialog.cpp \
    data/dhistogram.cpp \
    filter/fhistogram.cpp \
    filter/fdisplayhistogram.cpp \
    filter/fdisplayhistogramdialog.cpp \
    data/dsize.cpp \
    filter/fcorner.cpp \
    filter/fcornerdialog.cpp \
    filter/fgoodfeaturestotrack.cpp \
    filter/fgoodfeaturestotrackdialog.cpp \
    filter/fdrawpoints.cpp \
    filter/fdrawpointsdialog.cpp

HEADERS  += mainwindow.h \
    filter/filter.h \
    viewer.h \
    filtermap.h \
    filterfactory.h \
    filterregister.h \
    filter/fgrayscale.h \
    filter/fcolor.h \
    viewscene.h \
    data/data.h \
    input/input.h \
    output/output.h \
    input/ivideo.h \
    data/dimage3.h \
    data/dimage1.h \
    data/dnone.h \
    data/dpoint.h \
    data/dline.h \
    general.h \
    output/oscreen.h \
    listgph.h \
    listgphscene.h \
    gphlistitem.h \
    inputfactorybase.h \
    listitem.h \
    outputfactorybase.h \
    filter/fsplit.h \
    filter/fcombine.h \
    vview.h \
    mapobj.h \
    input/iimage.h \
    filebrowser.h \
    filter/fsobel.h \
    input/iimageconfig.h \
    input/ivideoconfig.h \
    output/oscreenconfig.h \
    filter/fsobeldialog.h \
    filter/fcolordialog.h \
    filter/fcombinedialog.h \
    filter/fgrayscaledialog.h \
    filter/fsplitdialog.h \
    filter/fdialate.h \
    filter/ferode.h \
    filter/ferodedialog.h \
    filter/flaplacian.h \
    filter/fblur.h \
    filter/flaplaciandialog.h \
    filter/fblurdialog.h \
    filter/fdialatedialog.h \
    input/icamera.h \
    input/icameradialog.h \
    filter/fthreshold.h \
    filter/fthresholddialog.h \
    data/dint.h \
    data/dreal.h \
    filter/fresize.h \
    filter/fresizedialog.h \
    filter/fhoughcircle.h \
    filter/fhoughcircledialog.h \
    filter/fdrawcircle.h \
    filter/fdrawcircledialog.h \
    data/dcircle.h \
    data/dlist.h \
    data/dmatrix.h \
    filter/fcanny.h \
    filter/fcannydialog.h \
    filter/fhoughlines.h \
    filter/fdrawlines.h \
    filter/fdrawlinesdialog.h \
    filter/fhoughlinedialog.h \
    filter/fdistance.h \
    filter/fdistancedialog.h \
    data/dhistogram.h \
    filter/fhistogram.h \
    filter/fdisplayhistogram.h \
    filter/fdisplayhistogramdialog.h \
    data/dsize.h \
    filter/fcorner.h \
    filter/fcornerdialog.h \
    filter/fgoodfeaturestotrack.h \
    filter/fgoodfeaturestotrackdialog.h \
    filter/fdrawpoints.h \
    filter/fdrawpointsdialog.h



FORMS    += mainwindow.ui \
    input/iimageconfig.ui \
    input/ivideoconfig.ui \
    output/oscreenconfig.ui \
    filter/fsobeldialog.ui \
    filter/fcolordialog.ui \
    filter/fcombinedialog.ui \
    filter/fgrayscaledialog.ui \
    filter/fsplitdialog.ui \
    filter/ferodedialog.ui \
    filter/flaplaciandialog.ui \
    filter/fblurdialog.ui \
    filter/fdialatedialog.ui \
    input/icameradialog.ui \
    filter/fthresholddialog.ui \
    filter/fresizedialog.ui \
    filter/fhoughcircledialog.ui \
    filter/fdrawcircledialog.ui \
    filter/fcannydialog.ui \
    filter/fdrawlinesdialog.ui \
    filter/fhoughlinedialog.ui \
    filter/fdistancedialog.ui \
    filter/fdisplayhistogramdialog.ui \
    filter/fcornerdialog.ui \
    filter/fgoodfeaturestotrackdialog.ui \
    filter/fdrawpointsdialog.ui

RESOURCES += \
    datatype.qrc
