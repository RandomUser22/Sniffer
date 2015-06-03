#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T15:25:10
#
#-------------------------------------------------

QT       -= gui

TARGET = sql
TEMPLATE = lib

DEFINES += SQL_LIBRARY

SOURCES += sql.cpp

HEADERS += sql.h\
        sql_global.h

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

# include for pcap
unix:!macx: LIBS += -L$$PWD/../external/pcap/libpcap/ -lpcap

unix:INCLUDEPATH += $$PWD/../external/pcap/libpcap
unix:DEPENDPATH += $$PWD/../external/pcap/libpcap

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap
win32:LIBS += -lWS2_32

win32:INCLUDEPATH += $$PWD/../external/pcap/winpcap/Include
win32:DEPENDPATH += $$PWD/../external/pcap/winpcap/Include
