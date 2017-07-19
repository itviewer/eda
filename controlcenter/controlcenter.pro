#-------------------------------------------------
#
# Project created by QtCreator 2017-06-23T02:46:04
#
#-------------------------------------------------

QT       += core gui widgets sql remoteobjects

CONFIG(release, debug|release):TARGET = controlcenter
CONFIG(debug, debug|release):TARGET = controlcenterd

TEMPLATE = app

CONFIG += c++11

REPC_SOURCE = controlcenterrpc.rep

win32 {
    QMAKE_CXXFLAGS += -utf-8
}

DESTDIR = $$PWD/../out

include(../common/common.pri)

SOURCES += \
        main.cpp \
        controlcenter.cpp \
    controlcenterrpc.cpp

HEADERS += \
        controlcenter.h \
    controlcenterrpc.h \

FORMS += \
        controlcenter.ui
