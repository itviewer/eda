
# 包含私有头文件 module-private
QT += core gui widgets printsupport sql concurrent

CONFIG(release, debug|release):TARGET = PCBEditor
CONFIG(debug, debug|release):TARGET = PCBEditord

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
    cmd \
    setting \
    fsm \
    primitive \
    navigator

FORMS += \
    app/pcbeditor.ui \
    setting/globalsettinggeneral.ui \
    setting/globalsettingbackup.ui

HEADERS += \
    app/pcbeditor.h \
    app/pcbview.h \
    app/pcbscene.h \
    app/global.h \
    primitive/abstractshapeitem.h \
    primitive/polylineitem.h \
    primitive/polylineitemcontrolpoint.h \
    setting/globalsetting.h \
    primitive/abstractcontrolpoint.h \
    setting/globalsettinggeneral.h \
    setting/globalsettingbackup.h \
    component/paditem.h \
    fsm/state.h \
    fsm/statemachine.h \
    fsm/statearcitem.h \
    fsm/statecubicbezieritem.h \
    fsm/stateellipseitem.h \
    fsm/statelineitem.h \
    fsm/statepixmapitem.h \
    fsm/statepolygonitem.h \
    fsm/statepolylineitem.h \
    fsm/staterectitem.h \
    fsm/stateroundedrectitem.h \
    fsm/stateselect.h \
    fsm/statetextitem.h \
    primitive/arcitem.h \
    primitive/arcitemcontrolpoint.h \
    primitive/cubicbezieritem.h \
    primitive/cubicbezieritemcontrolpoint.h \
    primitive/ellipseitem.h \
    primitive/ellipseitemcontrolpoint.h \
    primitive/lineitem.h \
    primitive/lineitemcontrolpoint.h \
    primitive/pixmapitem.h \
    primitive/polygonitem.h \
    primitive/polygonitemcontrolpoint.h \
    primitive/rectitem.h \
    primitive/rectitemcontrolpoint.h \
    primitive/roundedrectitem.h \
    primitive/roundedrectitemcontrolpoint.h \
    primitive/textitem.h \
    navigator/navigator.h \
    app/setting.h \
    app/defaultproperty.h

SOURCES += \
    app/pcbeditor.cpp \
    app/main.cpp \
    app/pcbview.cpp \
    app/pcbscene.cpp \
    app/global.cpp \
    primitive/abstractshapeitem.cpp \
    primitive/polylineitem.cpp \
    primitive/polylineitemcontrolpoint.cpp \
    setting/globalsetting.cpp \
    primitive/abstractcontrolpoint.cpp \
    setting/globalsettinggeneral.cpp \
    setting/globalsettingbackup.cpp \
    component/paditem.cpp \
    fsm/state.cpp \
    fsm/statemachine.cpp \
    fsm/statearcitem.cpp \
    fsm/statecubicbezieritem.cpp \
    fsm/stateellipseitem.cpp \
    fsm/statelineitem.cpp \
    fsm/statepixmapitem.cpp \
    fsm/statepolygonitem.cpp \
    fsm/statepolylineitem.cpp \
    fsm/staterectitem.cpp \
    fsm/stateroundedrectitem.cpp \
    fsm/stateselect.cpp \
    fsm/statetextitem.cpp \
    primitive/arcitem.cpp \
    primitive/arcitemcontrolpoint.cpp \
    primitive/cubicbezieritem.cpp \
    primitive/cubicbezieritemcontrolpoint.cpp \
    primitive/ellipseitem.cpp \
    primitive/ellipseitemcontrolpoint.cpp \
    primitive/lineitem.cpp \
    primitive/lineitemcontrolpoint.cpp \
    primitive/pixmapitem.cpp \
    primitive/polygonitem.cpp \
    primitive/polygonitemcontrolpoint.cpp \
    primitive/rectitem.cpp \
    primitive/rectitemcontrolpoint.cpp \
    primitive/roundedrectitem.cpp \
    primitive/roundedrectitemcontrolpoint.cpp \
    primitive/textitem.cpp \
    navigator/navigator.cpp \
    app/setting.cpp \
    app/defaultproperty.cpp

RESOURCES += \
    test/test.qrc