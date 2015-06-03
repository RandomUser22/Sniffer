#-------------------------------------------------
#
# Project created by QtCreator 2015-05-10T15:23:12
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = gui
TEMPLATE = lib

DEFINES += GUI_LIBRARY

SOURCES += \
    mainwindow.cpp \
    packetsniffingwidget.cpp \
    selectinterfacedialog.cpp \
    interfacedetailsdialog.cpp \
    packagedetailsdialog.cpp \
    accesspointinformationwidget.cpp \
    generalanalysiswidget.cpp \
    qcustomplot.cpp

HEADERS +=\
        gui_global.h \
    mainwindow.h \
    packetsniffingwidget.h \
    selectinterfacedialog.h \
    interfacedetailsdialog.h \
    packagedetailsdialog.h \
    accesspointinformationwidget.h \
    generalanalysiswidget.h \
    qcustomplot.h

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../logic/release/ -llogic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../logic/debug/ -llogic
else:unix: LIBS += -L$$OUT_PWD/../logic/ -llogic

INCLUDEPATH += $$PWD/../logic
DEPENDPATH += $$PWD/../logic

FORMS += \
    mainwindow.ui \
    packetsniffingwidget.ui \
    selectinterfacedialog.ui \
    interfacedetailsdialog.ui \
    packagedetailsdialog.ui \
    accesspointinformationwidget.ui \
    generalanalysiswidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../external/qcustomplot/lib/win/qcustomplot.dll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../external/qcustomplot/lib/win/qcustomplot.dll
else:unix: LIBS += -L$$OUT_PWD/../external/qcustomplot/lib/unix/ -lqcustomplot

INCLUDEPATH += $$PWD/../external/qcustomplot/include/
DEPENDPATH += $$PWD/../external/qcustomplot/include/

# include for pcap
unix:!macx: LIBS += -L$$PWD/../external/pcap/libpcap/ -lpcap

unix:INCLUDEPATH += $$PWD/../external/pcap/libpcap
unix:DEPENDPATH += $$PWD/../external/pcap/libpcap

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../external/pcap/winpcap/Lib/ -lwpcap
win32:LIBS += -lWS2_32

win32:INCLUDEPATH += $$PWD/../external/pcap/winpcap/Include
win32:DEPENDPATH += $$PWD/../external/pcap/winpcap/Include
