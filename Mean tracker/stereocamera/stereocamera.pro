TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT       += core gui

LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -lopencv_calib3d -lopencv_imgproc

SOURCES += main.cpp \
    videoreader.cpp

HEADERS += \
    videoreader.h

