# 包含私有头文件 module-private
QT += core gui widgets printsupport sql concurrent

CONFIG(release, debug|release):TARGET = PartEditor
CONFIG(debug, debug|release):TARGET = PartEditord

TEMPLATE = app

#DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += JSON_NOEXCEPTION
CONFIG += c++11

win32 {
    QMAKE_CXXFLAGS += -utf-8
}

DESTDIR = $$PWD/../out

include(../common/common.pri)
include(../PartLibManager/PartLibManager.pri)

INCLUDEPATH += \
    app \
    fsm \
    primitive \
    component \
    setting \
    dialog

FORMS += \
    app/parteditor.ui \
    setting/settinggrid.ui \
    setting/settingcolor.ui \
    setting/settingfont.ui \
    dialog/newpartdialog.ui

HEADERS += \
    app/parteditor.h \
    app/partview.h \
    app/global.h \
    app/partscene.h \
    fsm/state.h \
    fsm/statearcitem.h \
    fsm/statecubicbezieritem.h \
    fsm/stateellipseitem.h \
    fsm/statelineitem.h \
    fsm/statemachine.h \
    fsm/statepixmapitem.h \
    fsm/statepolygonitem.h \
    fsm/statepolylineitem.h \
    fsm/staterectitem.h \
    fsm/stateroundedrectitem.h \
    fsm/stateselect.h \
    fsm/statetextitem.h \
    primitive/abstractcontrolpoint.h \
    primitive/abstractshapeitem.h \
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
    primitive/polylineitem.h \
    primitive/polylineitemcontrolpoint.h \
    primitive/rectitem.h \
    primitive/rectitemcontrolpoint.h \
    primitive/roundedrectitem.h \
    primitive/roundedrectitemcontrolpoint.h \
    primitive/textitem.h \
    component/abstractpackageitem.h \
    app/defaultproperty.h \
    setting/settinggrid.h \
    setting/settingcolor.h \
    setting/settingfont.h \
    app/partio.h \
    dialog/newpartdialog.h

SOURCES += \
    app/main.cpp \
    app/parteditor.cpp \
    app/partview.cpp \
    app/global.cpp \
    app/partscene.cpp \
    fsm/state.cpp \
    fsm/statearcitem.cpp \
    fsm/statecubicbezieritem.cpp \
    fsm/stateellipseitem.cpp \
    fsm/statelineitem.cpp \
    fsm/statemachine.cpp \
    fsm/statepixmapitem.cpp \
    fsm/statepolygonitem.cpp \
    fsm/statepolylineitem.cpp \
    fsm/staterectitem.cpp \
    fsm/stateroundedrectitem.cpp \
    fsm/stateselect.cpp \
    fsm/statetextitem.cpp \
    primitive/abstractcontrolpoint.cpp \
    primitive/abstractshapeitem.cpp \
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
    primitive/polylineitem.cpp \
    primitive/polylineitemcontrolpoint.cpp \
    primitive/rectitem.cpp \
    primitive/rectitemcontrolpoint.cpp \
    primitive/roundedrectitem.cpp \
    primitive/roundedrectitemcontrolpoint.cpp \
    primitive/textitem.cpp \
    component/abstractpackageitem.cpp \
    app/defaultproperty.cpp \
    setting/settinggrid.cpp \
    setting/settingcolor.cpp \
    setting/settingfont.cpp \
    app/partio.cpp \
    dialog/newpartdialog.cpp

RESOURCES += \
    test/test.qrc


