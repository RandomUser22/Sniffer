#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T15:22:59
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main

TEMPLATE = app

SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../util/release/ -lutil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../util/debug/ -lutil
else:unix: LIBS += -L$$OUT_PWD/../util/ -lutil

INCLUDEPATH += $$PWD/../util
DEPENDPATH += $$PWD/../util

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../exception/release/ -lexception
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../exception/debug/ -lexception
else:unix: LIBS += -L$$OUT_PWD/../exception/ -lexception

INCLUDEPATH += $$PWD/../exception
DEPENDPATH += $$PWD/../exception

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../entity/release/ -lentity
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../entity/debug/ -lentity
else:unix: LIBS += -L$$OUT_PWD/../entity/ -lentity

INCLUDEPATH += $$PWD/../entity
DEPENDPATH += $$PWD/../entity

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../sql/release/ -lsql
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../sql/debug/ -lsql
else:unix: LIBS += -L$$OUT_PWD/../sql/ -lsql

INCLUDEPATH += $$PWD/../sql
DEPENDPATH += $$PWD/../sql

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../file/release/ -lfile
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../file/debug/ -lfile
else:unix: LIBS += -L$$OUT_PWD/../file/ -lfile

INCLUDEPATH += $$PWD/../file
DEPENDPATH += $$PWD/../file

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logic/release/ -llogic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logic/debug/ -llogic
else:unix: LIBS += -L$$OUT_PWD/../logic/ -llogic

INCLUDEPATH += $$PWD/../logic
DEPENDPATH += $$PWD/../logic

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gui/release/ -lgui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gui/debug/ -lgui
else:unix: LIBS += -L$$OUT_PWD/../gui/ -lgui

INCLUDEPATH += $$PWD/../gui
DEPENDPATH += $$PWD/../gui

# include for pcap
unix:!macx: LIBS += -L$$PWD/../external/pcap/libpcap/ -lpcap

unix:INCLUDEPATH += $$PWD/../external/pcap/libpcap
unix:DEPENDPATH += $$PWD/../external/pcap/libpcap

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap
win32:LIBS += -lWS2_32

win32:INCLUDEPATH += $$PWD/../external/pcap/winpcap/Include
win32:DEPENDPATH += $$PWD/../external/pcap/winpcap/Include
