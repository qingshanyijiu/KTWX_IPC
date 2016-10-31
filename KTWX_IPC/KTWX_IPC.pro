#-------------------------------------------------
#
# Project created by QtCreator 2016-09-21T16:22:00
#
#-------------------------------------------------

QT       -= gui
QT       += network widgets

TARGET = KTWX_IPC
TEMPLATE = lib

DEFINES += KTWX_IPC_LIBRARY

SOURCES += ktwx_ipc_api.cpp \
    server/serverimpl.cpp \
    client/mutilclientimpl.cpp \
    server/serverbase.cpp \
    server/workdispatchbase.cpp \
    client/clientbase.cpp \
    server/localserverimpl.cpp \
    server/qlocalserverex.cpp \
    server/localserverconnection.cpp \
    server/queuedispatcher.cpp \
    server/concurrencedispatcher.cpp \
    client/localsocketclient.cpp \
    memorypool.cpp

HEADERS += ktwx_ipc_api.h \
    ktwx_ipc_def.h \
    server/serverimpl.h \
    client/mutilclientimpl.h \
    SingletonInstance.h \
    server/serverbase.h \
    server/workdispatchbase.h \
    client/clientbase.h \
    server/localserverimpl.h \
    server/qlocalserverex.h \
    server/localserverconnection.h \
    server/queuedispatcher.h \
    server/concurrencedispatcher.h \
    client/localsocketclient.h \
    memorypool.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


UI_DIR = ./tmp
MOC_DIR = ./tmp
OBJECTS_DIR = ./obj
DESTDIR = ../../bin



unix:!macx|win32: LIBS += -L$$PWD/lib/ -llibtcmalloc_minimal

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
