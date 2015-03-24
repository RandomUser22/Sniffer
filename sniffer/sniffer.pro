#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T16:56:16
#
#-------------------------------------------------

QT       -= gui

TARGET = sniffer
TEMPLATE = lib

DEFINES += SNIFFER_LIBRARY

SOURCES += \
    sniffermanager.cpp

unix:SOURCES += interfacemanager.cpp
win32:SOURCES += interfacemanagerwin.cpp

HEADERS +=\
    sniffer_global.h \
    sniffermanager.h \
    NetworkInterface.h \
    interfacemanager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../utility/release/ -lutility
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../utility/debug/ -lutility
else:unix:!macx: LIBS += -L$$OUT_PWD/../utility/ -lutility

INCLUDEPATH += $$PWD/../utility
DEPENDPATH += $$PWD/../utility

unix:!macx: LIBS += -L$$PWD/../pcap/libpcap/ -lpcap

unix:INCLUDEPATH += $$PWD/../pcap/libpcap
unix:DEPENDPATH += $$PWD/../pcap/libpcap

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../pcap/winpcap/Lib/ -lwpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../pcap/winpcap/Lib/ -lwpcap
win32:LIBS += -lWS2_32

win32:INCLUDEPATH += $$PWD/../pcap/winpcap/Include
win32:DEPENDPATH += $$PWD/../pcap/winpcap/Include
