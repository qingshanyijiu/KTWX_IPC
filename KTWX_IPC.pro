TEMPLATE = subdirs

SUBDIRS += \
    KTWX_IPC \
    KTWX_Log_Server \
#    KTWX_Log_Client	\
#    KTWX_Log_Test


CONFIG(debug, debug|release){
    QMAKE_LFLAGS_DEBUG   += -Wl,-rpath="../bin/",-Bsymbolic
} else {
    QMAKE_LFLAGS_RELEASE += -Wl,-rpath="../bin/",-Bsymbolic
}
