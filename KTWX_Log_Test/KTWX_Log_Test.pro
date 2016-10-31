#-------------------------------------------------
#
# Project created by QtCreator 2016-10-21T14:02:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KTWX_Log_Test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logclient.cpp

HEADERS  += mainwindow.h \
    logclient.h

FORMS    += mainwindow.ui


UI_DIR = ./tmp
MOC_DIR = ./tmp
OBJECTS_DIR = ./obj
DESTDIR = ../bin



unix:!macx|win32: LIBS += -L$$PWD/../bin/ -lKTWX_Log_Client

INCLUDEPATH += $$PWD/../KTWX_Log_Client
DEPENDPATH += $$PWD/../KTWX_Log_Client
