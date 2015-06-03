#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T15:23:54
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = logic
TEMPLATE = lib

DEFINES += LOGIC_LIBRARY

SOURCES += \
    logicfacade.cpp \
    networkinterfacemanager.cpp \
    sniffingmanager.cpp \
    accesspointmanager.cpp

win32:SOURCES += networkinterfacemanagerwin.cpp \
            sniffingmanagerwin.cpp \
            accesspointmanagerwin.cpp

HEADERS +=\
    logic_global.h \
    logicfacade.h \
    networkinterfacemanager.h \
    sniffingmanager.h \
    accesspointmanager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

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

# include for pcap
unix:!macx: LIBS += -L$$PWD/../external/pcap/libpcap/ -lpcap

unix:INCLUDEPATH += $$PWD/../external/pcap/libpcap
unix:DEPENDPATH += $$PWD/../external/pcap/libpcap

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap
win32:LIBS += -lWS2_32

win32:INCLUDEPATH += $$PWD/../external/pcap/winpcap/Include
win32:DEPENDPATH += $$PWD/../external/pcap/winpcap/Include
