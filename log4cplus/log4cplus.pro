#-------------------------------------------------
#
# Project created by QtCreator 2016-10-24T11:35:15
#
#-------------------------------------------------

QT       -= gui

TARGET = log4cplus
TEMPLATE = lib

DEFINES += LOG4CPLUS_LIBRARY

SOURCES += \
    appender.cxx \
    appenderattachableimpl.cxx \
    asyncappender.cxx \
    clogger.cxx \
    configurator.cxx \
    consoleappender.cxx \
    cygwin-win32.cxx \
    env.cxx \
    factory.cxx \
    fileappender.cxx \
    fileinfo.cxx \
    filter.cxx \
    global-init.cxx \
    hierarchy.cxx \
    hierarchylocker.cxx \
    layout.cxx \
    lockfile.cxx \
    logger.cxx \
    loggerimpl.cxx \
    loggingevent.cxx \
    loggingmacros.cxx \
    loglevel.cxx \
    loglog.cxx \
    logloguser.cxx \
    mdc.cxx \
    ndc.cxx \
    nteventlogappender.cxx \
    nullappender.cxx \
    objectregistry.cxx \
    pointer.cxx \
    property.cxx \
    qt5debugappender.cxx \
    queue.cxx \
    rootlogger.cxx \
    sleep.cxx \
    snprintf.cxx \
    stringhelper.cxx \
    stringhelper-clocale.cxx \
    stringhelper-cxxlocale.cxx \
    stringhelper-iconv.cxx \
    syncprims.cxx \
    threads.cxx \
    timehelper.cxx \
    tls.cxx \
    version.cxx \
    win32consoleappender.cxx \
    win32debugappender.cxx \
    patternlayout.cxx

unix {
    target.path = /usr/lib
    INSTALLS += target
}


INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

HEADERS += \
    include/log4cplus/appender.h \
    include/log4cplus/asyncappender.h \
    include/log4cplus/clogger.h \
    include/log4cplus/config.h \
    include/log4cplus/config.hxx \
    include/log4cplus/configurator.h \
    include/log4cplus/consoleappender.h \
    include/log4cplus/fileappender.h \
    include/log4cplus/fstreams.h \
    include/log4cplus/hierarchy.h \
    include/log4cplus/hierarchylocker.h \
    include/log4cplus/layout.h \
    include/log4cplus/log4judpappender.h \
    include/log4cplus/logger.h \
    include/log4cplus/loggingmacros.h \
    include/log4cplus/loglevel.h \
    include/log4cplus/mdc.h \
    include/log4cplus/msttsappender.h \
    include/log4cplus/ndc.h \
    include/log4cplus/nteventlogappender.h \
    include/log4cplus/nullappender.h \
    include/log4cplus/qt4debugappender.h \
    include/log4cplus/qt5debugappender.h \
    include/log4cplus/socketappender.h \
    include/log4cplus/streams.h \
    include/log4cplus/syslogappender.h \
    include/log4cplus/tchar.h \
    include/log4cplus/tracelogger.h \
    include/log4cplus/tstring.h \
    include/log4cplus/version.h \
    include/log4cplus/win32consoleappender.h \
    include/log4cplus/win32debugappender.h \
    include/log4cplus/boost/deviceappender.hxx \
    include/log4cplus/config/defines.hxx \
    include/log4cplus/config/macosx.h \
    include/log4cplus/config/win32.h \
    include/log4cplus/config/windowsh-inc.h \
    include/log4cplus/helpers/appenderattachableimpl.h \
    include/log4cplus/helpers/connectorthread.h \
    include/log4cplus/helpers/fileinfo.h \
    include/log4cplus/helpers/lockfile.h \
    include/log4cplus/helpers/loglog.h \
    include/log4cplus/helpers/logloguser.h \
    include/log4cplus/helpers/pointer.h \
    include/log4cplus/helpers/property.h \
    include/log4cplus/helpers/queue.h \
    include/log4cplus/helpers/sleep.h \
    include/log4cplus/helpers/snprintf.h \
    include/log4cplus/helpers/socket.h \
    include/log4cplus/helpers/socketbuffer.h \
    include/log4cplus/helpers/stringhelper.h \
    include/log4cplus/helpers/thread-config.h \
    include/log4cplus/helpers/timehelper.h \
    include/log4cplus/internal/cygwin-win32.h \
    include/log4cplus/internal/env.h \
    include/log4cplus/internal/internal.h \
    include/log4cplus/internal/socket.h \
    include/log4cplus/spi/appenderattachable.h \
    include/log4cplus/spi/factory.h \
    include/log4cplus/spi/filter.h \
    include/log4cplus/spi/loggerfactory.h \
    include/log4cplus/spi/loggerimpl.h \
    include/log4cplus/spi/loggingevent.h \
    include/log4cplus/spi/objectregistry.h \
    include/log4cplus/spi/rootlogger.h \
    include/log4cplus/thread/syncprims.h \
    include/log4cplus/thread/syncprims-pub-impl.h \
    include/log4cplus/thread/threads.h \
    include/log4cplus/thread/impl/syncprims-cxx11.h \
    include/log4cplus/thread/impl/syncprims-impl.h \
    include/log4cplus/thread/impl/syncprims-pmsm.h \
    include/log4cplus/thread/impl/syncprims-pthreads.h \
    include/log4cplus/thread/impl/syncprims-win32.h \
    include/log4cplus/thread/impl/threads-impl.h \
    include/log4cplus/thread/impl/tls.h


UI_DIR = ./tmp
MOC_DIR = ./tmp
OBJECTS_DIR = ./obj
DESTDIR = ../bin
