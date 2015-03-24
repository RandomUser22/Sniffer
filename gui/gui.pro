#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T16:56:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = lib
CONFIG += plugin

DEFINES += GUI_LIBRARY

SOURCES += \
    selectinterface.cpp \
    mainwindow.cpp \
    interfacelist.cpp \
    interfacelisttablemodel.cpp

HEADERS +=\
        gui_global.h \
    selectinterface.h \
    mainwindow.h \
    interfacelist.h \
    interfacelisttablemodel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    selectinterface.ui \
    mainwindow.ui \
    interfacelist.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../utility/release/ -lutility
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../utility/debug/ -lutility
else:unix:!macx: LIBS += -L$$OUT_PWD/../utility/ -lutility

INCLUDEPATH += $$PWD/../utility
DEPENDPATH += $$PWD/../utility

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../sniffer/release/ -lsniffer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../sniffer/debug/ -lsniffer
else:unix:!macx: LIBS += -L$$OUT_PWD/../sniffer/ -lsniffer

INCLUDEPATH += $$PWD/../sniffer
DEPENDPATH += $$PWD/../sniffer

unix:!macx: LIBS += -L$$PWD/../pcap/libpcap/ -lpcap

unix:INCLUDEPATH += $$PWD/../pcap/libpcap
unix:DEPENDPATH += $$PWD/../pcap/libpcap

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../pcap/winpcap/Lib/ -lwpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../pcap/winpcap/Lib/ -lwpcap

win32:INCLUDEPATH += $$PWD/../pcap/winpcap/Include
win32:DEPENDPATH += $$PWD/../pcap/winpcap/Include
