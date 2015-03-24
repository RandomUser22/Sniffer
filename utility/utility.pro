#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T16:57:42
#
#-------------------------------------------------

QT       -= gui

TARGET = utility
TEMPLATE = lib

DEFINES += UTILITY_LIBRARY

# sources
SOURCES += utility.cpp
SOURCES += stringutil.cpp

#headers
HEADERS += utility_global.h
HEADERS += utility.h
HEADERS += stringutil.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
