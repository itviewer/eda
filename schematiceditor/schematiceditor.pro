
# 包含私有头文件 module-private
QT += core gui widgets printsupport sql concurrent

CONFIG(release, debug|release):TARGET = schematiceditor
CONFIG(debug, debug|release):TARGET = schematiceditord

TEMPLATE = app

#DEFINES += QT_NO_DEBUG_OUTPUT
#DEFINES += JSON_NOEXCEPTION
CONFIG += c++11

win32 {
    QMAKE_CXXFLAGS += -utf-8

    RC_FILE = resource.rc
#    VERSION = 0.9.0.0
#    RC_ICONS = schematiceditor.ico
#    RC_LANG = 0x0804
#    QMAKE_TARGET_PRODUCT = "Idea EDA"
#    QMAKE_TARGET_COMPANY = "北京梦飞翔宇科技有限公司"
#    QMAKE_TARGET_DESCRIPTION = "原理图编辑器"
#    QMAKE_TARGET_COPYRIGHT = "Copyright 2014-2017 北京梦飞翔宇科技有限公司. All rights reserved."
}

DESTDIR = $$PWD/../out
TRANSLATIONS = i18n/schematiceditor_en.ts

include(../common/common.pri)
include(../partlibmanager/partlibmanager.pri)

INCLUDEPATH += \
    app \
    cmd \
    cmd/child \
    primitive \
    component \
    fsm \
    dialog \
    setting \
    navigator \
    partselector \

FORMS += \
    app/schematiceditor.ui \
    setting/globalsettinggeneral.ui \
    setting/globalsettingcolorscheme.ui \
    setting/globalsettingdesign.ui \
    setting/globalsettingtext.ui \
    setting/globalsettinglinewidth.ui \
    dialog/newpagedialog.ui \
    dialog/newcolorschemedialog.ui

HEADERS += \
    app/global.h \
    app/schematiceditor.h \
    app/schematicscene.h \
    app/schematicview.h \
    component/partitem.h \
    component/pinitem.h \
    component/wire.h \
    fsm/state.h \
    fsm/statearcitem.h \
    fsm/stateellipseitem.h \
    fsm/statelineitem.h \
    fsm/statemachine.h \
    fsm/statepartitem.h \
    fsm/statepixmapitem.h \
    fsm/statepolygonitem.h \
    fsm/statepolylineitem.h \
    fsm/staterectitem.h \
    fsm/stateselect.h \
    fsm/statetextitem.h \
    primitive/abstractcontrolpoint.h \
    primitive/arcitem.h \
    primitive/arcitemcontrolpoint.h \
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
    primitive/textitem.h \
    app/defaultproperty.h \
    setting/globalsetting.h \
    app/tabcontainer.h \
    app/schematicio.h \
    cmd/shapeitemaddcommand.h \
    cmd/shapeitemremovecommand.h \
    cmd/shapeitemmovecommand.h \
    cmd/shapeitemchanggeometryecommand.h \
    navigator/navigator.h \
    cmd/shapeitemrotatecommand.h \
    navigator/schematicnavigator.h \
    navigator/partnavigator.h \
    primitive/abstractshapeitem.h \
    cmd/shapeitemgrouprotatecommand.h \
    cmd/textitemaddcommand.h \
    cmd/textitemremovecommand.h \
    cmd/textitemchangepropertycommand.h \
    cmd/pixmapitemaddcommand.h \
    cmd/pixmapitemremovecommand.h \
    cmd/pixmapitemchangepropertycommand.h \
    primitive/cubicbezieritem.h \
    fsm/statecubicbezieritem.h \
    primitive/cubicbezieritemcontrolpoint.h \
    primitive/roundedrectitem.h \
    fsm/stateroundedrectitem.h \
    primitive/roundedrectitemcontrolpoint.h \
    partselector/partwidget.h \
    partselector/selectorscene.h \
    partselector/selectorview.h \
    partselector/partselector.h \
    partselector/parttable.h \
    partselector/partpreviewer.h \
    partselector/partpreviewitem.h \
    component/junctionitem.h \
    component/nodeitem.h \
    component/portitem.h \
    component/abstractpackageitem.h \
    component/poweritem.h \
    component/gnditem.h \
    component/busentryitem.h \
    component/busitem.h \
    component/offpageitem.h \
    component/noconnectitem.h \
    primitive/wiresegmentitem.h \
    primitive/wiresegmentitemcontrolpoint.h \
    fsm/statewiresegmentitem.h \
    cmd/itemundocommand.h \
    cmd/wiresegmentitemremovecommand.h \
    cmd/wiresegmentitemmovecommand.h \
    cmd/wiresegmentitemchangegeometrycommand.h \
    cmd/wireaddcommand.h \
    cmd/wireundocommand.h \
    cmd/partitemaddcommand.h \
    cmd/partitemremovecommand.h \
    cmd/junctionitemaddcommand.h \
    cmd/partitemmovecommand.h \
    cmd/child/wiresegmentitemappendcommand.h \
    cmd/child/wiresegmentitemmergecommand.h \
    cmd/child/wiresegmentitemprependcommand.h \
    cmd/child/wirespiltcommand.h \
    cmd/child/wiremergecommand.h \
    setting/globalsettinggeneral.h \
    setting/globalsettingcolorscheme.h \
    setting/globalsettingdesign.h \
    setting/globalsettingtext.h \
    setting/globalsettinglinewidth.h \
    navigator/parttypenavigator.h \
    navigator/netnavigator.h \
    navigator/schtreewidgetitem.h \
    component/pageborderitem.h \
    dialog/newpagedialog.h \
    app/settingio.h \
    dialog/newcolorschemedialog.h

SOURCES += \
    app/global.cpp \
    app/main.cpp \
    app/schematiceditor.cpp \
    app/schematicscene.cpp \
    app/schematicview.cpp \
    component/partitem.cpp \
    component/pinitem.cpp \
    component/wire.cpp \
    fsm/state.cpp \
    fsm/statearcitem.cpp \
    fsm/stateellipseitem.cpp \
    fsm/statelineitem.cpp \
    fsm/statemachine.cpp \
    fsm/statepartitem.cpp \
    fsm/statepixmapitem.cpp \
    fsm/statepolygonitem.cpp \
    fsm/statepolylineitem.cpp \
    fsm/staterectitem.cpp \
    fsm/stateselect.cpp \
    fsm/statetextitem.cpp \
    primitive/abstractcontrolpoint.cpp \
    primitive/arcitem.cpp \
    primitive/arcitemcontrolpoint.cpp \
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
    primitive/textitem.cpp \
    setting/globalsetting.cpp \
    app/tabcontainer.cpp \
    app/schematicio.cpp \
    cmd/shapeitemaddcommand.cpp \
    cmd/shapeitemremovecommand.cpp \
    cmd/shapeitemmovecommand.cpp \
    cmd/shapeitemchangegeometrycommand.cpp \
    navigator/navigator.cpp \
    cmd/shapeitemrotatecommand.cpp \
    navigator/schematicnavigator.cpp \
    navigator/partnavigator.cpp \
    app/defaultproperty.cpp \
    primitive/abstractshapeitem.cpp \
    cmd/shapeitemgrouprotatecommand.cpp \
    cmd/textitemaddcommand.cpp \
    cmd/textitemremovecommand.cpp \
    cmd/textitemchangepropertycommand.cpp \
    cmd/pixmapitemaddcommand.cpp \
    cmd/pixmapitemremovecommand.cpp \
    cmd/pixmapitemchangepropertycommand.cpp \
    primitive/cubicbezieritem.cpp \
    fsm/statecubicbezieritem.cpp \
    primitive/cubicbezieritemcontrolpoint.cpp \
    primitive/roundedrectitem.cpp \
    fsm/stateroundedrectitem.cpp \
    primitive/roundedrectitemcontrolpoint.cpp \
    partselector/partselector.cpp \
    partselector/parttable.cpp \
    partselector/partpreviewer.cpp \
    partselector/partpreviewitem.cpp \
    component/junctionitem.cpp \
    component/nodeitem.cpp \
    component/portitem.cpp \
    component/abstractpackageitem.cpp \
    component/poweritem.cpp \
    component/gnditem.cpp \
    component/busentryitem.cpp \
    component/busitem.cpp \
    component/offpageitem.cpp \
    component/noconnectitem.cpp \
    primitive/wiresegmentitem.cpp \
    primitive/wiresegmentitemcontrolpoint.cpp \
    fsm/statewiresegmentitem.cpp \
    cmd/itemundocommand.cpp \
    cmd/wiresegmentitemremovecommand.cpp \
    cmd/wiresegmentitemmovecommand.cpp \
    cmd/wiresegmentitemchangegeometrycommand.cpp \
    cmd/wireaddcommand.cpp \
    cmd/wireundocommand.cpp \
    cmd/partitemaddcommand.cpp \
    cmd/partitemremovecommand.cpp \
    cmd/junctionitemaddcommand.cpp \
    cmd/partitemmovecommand.cpp \
    cmd/child/wiresegmentitemappendcommand.cpp \
    cmd/child/wiresegmentitemmergecommand.cpp \
    cmd/child/wiresegmentitemprependcommand.cpp \
    cmd/child/wirespiltcommand.cpp \
    cmd/child/wiremergecommand.cpp \
    setting/globalsettinggeneral.cpp \
    setting/globalsettingcolorscheme.cpp \
    setting/globalsettingdesign.cpp \
    setting/globalsettingtext.cpp \
    setting/globalsettinglinewidth.cpp \
    navigator/parttypenavigator.cpp \
    navigator/netnavigator.cpp \
    navigator/schtreewidgetitem.cpp \
    component/pageborderitem.cpp \
    dialog/newpagedialog.cpp \
    app/settingio.cpp \
    dialog/newcolorschemedialog.cpp

RESOURCES += \
    test/test.qrc \
    resources/resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$DESTDIR/ -lparteditor
else:win32:CONFIG(debug, debug|release): LIBS += -L$$DESTDIR/ -lparteditord
else:unix: LIBS += -L$$DESTDIR/ -lparteditor


