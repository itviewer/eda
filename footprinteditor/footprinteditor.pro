# 包含私有头文件 module-private
QT += core gui widgets printsupport sql concurrent

CONFIG(release, debug|release):TARGET = footprinteditor
CONFIG(debug, debug|release):TARGET = footprinteditord

TEMPLATE = app

#DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += JSON_NOEXCEPTION
CONFIG += c++11

win32 {
    QMAKE_CXXFLAGS += -utf-8
}

DESTDIR = $$PWD/../out

include(../common/common.pri)

INCLUDEPATH += \
    app \

FORMS += \
    app/footprinteditor.ui

HEADERS += \
    app/footprinteditor.h

SOURCES += \
    app/footprinteditor.cpp \
    app/main.cpp

