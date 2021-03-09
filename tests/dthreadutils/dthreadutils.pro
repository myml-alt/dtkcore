QT += testlib concurrent
QT -= gui

TEMPLATE = app
CONFIG += c++11

!isEmpty(DTK_STATIC_LIB){
    DEFINES += DTK_STATIC_LIB
}

load(dtk_testcase)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/release/ -ldtkcore5.5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/debug/ -ldtkcore5.5
else:unix: LIBS += -L$$OUT_PWD/../../src/ -ldtkcore5.5

INCLUDEPATH += $$PWD/../../src
DEPENDPATH += $$PWD/../../src
QMAKE_RPATHDIR += $$OUT_PWD/../../src

QMAKE_LFLAGS += -Wl,--export-dynamic

SOURCES += \
    $$PWD/../../src/util/dthreadutils.cpp \
    ut_dthreadutils.cpp
