#-------------------------------------------------
#
# Project created by QtCreator 2014-11-26T17:00:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = meantracker
TEMPLATE = app

LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -lopencv_calib3d -lopencv_imgproc


SOURCES += main.cpp\
        mainwindow.cpp \
    videoreader.cpp \
    picviewer.cpp \
    meanshifttracker.cpp

HEADERS  += mainwindow.h \
    videoreader.h \
    picviewer.h \
    meanshifttracker.h

FORMS    += mainwindow.ui

