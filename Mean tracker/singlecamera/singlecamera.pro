TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_objdetect -lopencv_calib3d -lopencv_imgproc


SOURCES += main.cpp

