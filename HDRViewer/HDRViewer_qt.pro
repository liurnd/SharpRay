#-------------------------------------------------
#
# Project created by QtCreator 2014-05-21T11:06:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HDRViewer_qt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    rgbhistogram.cpp \
    imageviewer.cpp

HEADERS  += mainwindow.h \
    rgbhistogram.h \
    imageviewer.h

FORMS    += mainwindow.ui
