#-------------------------------------------------
#
# Project created by QtCreator 2015-04-01T21:56:05
#
#-------------------------------------------------

QT       -= gui

TARGET = entity
TEMPLATE = lib

DEFINES += ENTITY_LIBRARY

SOURCES += \
    pcapexception.cpp \
    packet.cpp \
    sniffinginterface.cpp

HEADERS +=\
        entity_global.h \
    pcapexception.h \
    packet.h \
    sniffinginterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
