#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T13:08:53
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = meanShiftFilter
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += J:\\opencv\build\include

LIBS += -LJ:\opencv\build\x86\vc10\lib \
    -lopencv_core246 \
    -lopencv_highgui246 \
    -lopencv_imgproc246 \
    -lopencv_features2d246 \
    -lopencv_calib3d246

SOURCES += main.cpp \
    meanshiftfilter.cpp

HEADERS += \
    meanshiftfilter.h


