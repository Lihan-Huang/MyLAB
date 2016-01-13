#-------------------------------------------------
#
# Project created by QtCreator 2016-01-10T17:19:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# C++ 11
CONFIG += c++11
TARGET = MyLAB
TEMPLATE = app

# OpenCV
INCLUDEPATH += /usr/local/include/opencv \
    /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_core.so \
    /usr/local/lib/libopencv_imgproc.so \
    /usr/local/lib/libopencv_highgui.so \
    /usr/local/lib/libopencv_imgcodecs.so

SOURCES += main.cpp\
        mainwindow.cpp \
    widgets/childwindow.cpp \
    widgets/imagewidget.cpp \
    tools/texteditor.cpp \
    tools/editor.cpp

HEADERS  += mainwindow.h \
    widgets/childwindow.h \
    widgets/imagewidget.h \
    tools/texteditor.h \
    tools/editor.h

FORMS    += mainwindow.ui \
    widgets/childwindow.ui \
    widgets/imagewidget.ui \
    tools/texteditor.ui
