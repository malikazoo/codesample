#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T17:24:59
#
#-------------------------------------------------

TEMPLATE = app
TARGET = meanShiftTracking

LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_calib3d -lopencv_imgproc


QT       += core gui widgets \
            multimedia \
            multimediawidgets

SOURCES += main.cpp \
    interactivewindow.cpp \
    interactivevideocontroller.cpp \
    interactivegraphicsview.cpp \
    targetdetector.cpp \
    videosurface.cpp \
    targetdetectortester.cpp

HEADERS += \
    interactivewindow.h \
    interactivevideocontroller.h \
    interactivegraphicsview.h \
    targetdetector.h \
    videosurface.h \
    targetdetectortester.h
