#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T15:25:35
#
#-------------------------------------------------

QT       -= gui

TARGET = exception
TEMPLATE = lib

DEFINES += EXCEPTION_LIBRARY

SOURCES += \
    pcapexception.cpp

HEADERS +=\
        exception_global.h \
    pcapexception.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../util/release/ -lutil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../util/debug/ -lutil
else:unix: LIBS += -L$$OUT_PWD/../util/ -lutil

INCLUDEPATH += $$PWD/../util
DEPENDPATH += $$PWD/../util
