#-------------------------------------------------
#
# Project created by QtCreator 2014-11-11T11:12:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videoConverter
TEMPLATE = app

LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_calib3d -lopencv_imgproc


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
