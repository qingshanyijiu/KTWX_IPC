#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T15:42:36
#
#-------------------------------------------------

QT       -=  gui

TARGET = KTWX_Log_Client
TEMPLATE = lib

DEFINES += KTWX_LOG_CLIENT_LIBRARY

SOURCES += ktwx_log_client.cpp \
    logclientimpl.cpp

HEADERS += ktwx_log_client.h \
    logclientimpl.h \
    KTWX_Log_Client_Def.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


UI_DIR = ./tmp
MOC_DIR = ./tmp
OBJECTS_DIR = ./obj
DESTDIR = ../bin



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../bin/ -lKTWX_IPC
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../bin/ -lKTWX_IPC
else:unix:!macx: LIBS += -L$$PWD/../bin/ -lKTWX_IPC

INCLUDEPATH += $$PWD/../KTWX_IPC
DEPENDPATH += $$PWD/../KTWX_IPC
