#-------------------------------------------------
#
# Project created by QtCreator 2016-10-20T14:12:44
#
#-------------------------------------------------

QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KTWX_Log_Server
TEMPLATE = app


SOURCES += main.cpp \
    logserver.cpp \
    logdatactrl.cpp \
    logdatainfo.cpp \
    workrunnable.cpp \
    logwriter.cpp

HEADERS  += \
    logserver.h \
    logdatactrl.h \
    logdatainfo.h \
    workrunnable.h \
    logwriter.h

UI_DIR = ./tmp
MOC_DIR = ./tmp
OBJECTS_DIR = ./obj
DESTDIR = ../../bin


win32:CONFIG(release, debug|release):LIBS += -L$$PWD/../bin/ -lKTWX_IPC
else:win32:CONFIG(debug, debug|release):LIBS += -L$$PWD/../bin/ -lKTWX_IPC
else:unix:!macx:LIBS += -L$$PWD/../bin/ -lKTWX_IPC

INCLUDEPATH += $$PWD/../KTWX_IPC
DEPENDPATH += $$PWD/../KTWX_IPC


INCLUDEPATH += $$PWD/loglib
DEPENDPATH += $$PWD/loglib

unix:!macx|win32: LIBS += -L$$PWD/../bin/ -llog4cplus




unix:!macx|win32: LIBS += -L$$PWD/leakDetector/lib/Win64/ -lvld

INCLUDEPATH += $$PWD/leakDetector/include
DEPENDPATH += $$PWD/leakDetector/include
