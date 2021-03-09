TEMPLATE = app
QT += dbus

SOURCES += \
    $$PWD/main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../src/release -ldtkcore5.5
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../src/debug -ldtkcore5.5
else:unix: LIBS += -L$$OUT_PWD/../../src -ldtkcore5.5

INCLUDEPATH += $$PWD/../../src
INCLUDEPATH += $$PWD/../../src/base

CONFIG(debug, debug|release) {
    unix:QMAKE_RPATHDIR += $$OUT_PWD/../../src
}
