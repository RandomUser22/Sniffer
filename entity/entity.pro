#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T15:24:07
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = entity
TEMPLATE = lib

DEFINES += ENTITY_LIBRARY

SOURCES += \
    ethernetheader.cpp \
    networkinterface.cpp \
    pcapaddressnetworkinterface.cpp \
    packet.cpp \
    ipheader.cpp \
    subpacket.cpp \
    payload.cpp \
    tcppayload.cpp \
    udppayload.cpp \
    icmppayload.cpp \
    wlaninterface.cpp \
    wlanavailableconnection.cpp \
    wlanavailableconnectionlist.cpp

HEADERS +=\
        entity_global.h \
    ethernetheader.h \
    networkinterface.h \
    enum_adaptertype.h \
    pcapaddressnetworkinterface.h \
    packet.h \
    ipheader.h \
    subpacket.h \
    payload.h \
    tcppayload.h \
    udppayload.h \
    icmppayload.h \
    networkinclude.h \
    enum_protocoltype.h \
    wlaninterface.h \
    wlanavailableconnection.h \
    enum_wlanconnection.h \
    enum_wlanbsstype.h \
    wlanavailableconnectionlist.h

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

win32: LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap

INCLUDEPATH += $$PWD/../external/pcap/winpcap/Lib
DEPENDPATH += $$PWD/../external/pcap/winpcap/Lib

# include for pcap
unix:!macx: LIBS += -L$$PWD/../external/pcap/libpcap/ -lpcap

unix:INCLUDEPATH += $$PWD/../external/pcap/libpcap
unix:DEPENDPATH += $$PWD/../external/pcap/libpcap

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap
win32:LIBS += -lWS2_32

win32:INCLUDEPATH += $$PWD/../external/pcap/winpcap/Include
win32:DEPENDPATH += $$PWD/../external/pcap/winpcap/Include
