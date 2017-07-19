include(3rdparty/json/json.pri)
include(widgets/widgets.pri)
include(db/db.pri)

INCLUDEPATH += $$PWD

RESOURCES += \
    $$PWD/resources/common.qrc

HEADERS += \
    $$PWD/common.h \
    $$PWD/jsontype.h

SOURCES += \
    $$PWD/common.cpp \
    $$PWD/jsontype.cpp
