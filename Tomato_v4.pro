TEMPLATE = subdirs

CONFIG += ordered

## todo:: acces point
## nume, puterea

SUBDIRS += \
    utility \
    entity \
    sniffer \
    gui \
    main

unix:!macx: LIBS += -L$$PWD/pcap/libpcap/ -lpcap

INCLUDEPATH += $$PWD/pcap/libpcap
DEPENDPATH += $$PWD/pcap/libpcap

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/pcap/winpcap/Lib/ -lwpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/pcap/winpcap/Lib/ -lwpcapd

INCLUDEPATH += $$PWD/pcap/winpcap/Include
DEPENDPATH += $$PWD/pcap/winpcap/Include

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/utility/release/ -lutility
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/utility/debug/ -lutility
else:unix:!macx: LIBS += -L$$OUT_PWD/utility/ -lutility

INCLUDEPATH += $$PWD/utility
DEPENDPATH += $$PWD/utility

# include the entity lib
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/entity/release/ -lentity
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/entity/debug/ -lentity
else:unix:!macx: LIBS += -L$$OUT_PWD/../entity/ -lentity

INCLUDEPATH += $$PWD/entity
DEPENDPATH += $$PWD/entity

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/sniffer/release/ -lsniffer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/sniffer/debug/ -lsniffer
else:unix:!macx: LIBS += -L$$OUT_PWD/sniffer/ -lsniffer

INCLUDEPATH += $$PWD/sniffer
DEPENDPATH += $$PWD/sniffer

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/gui/release/ -lgui
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/gui/debug/ -lgui
else:unix:!macx: LIBS += -L$$OUT_PWD/gui/ -lgui

INCLUDEPATH += $$PWD/gui
DEPENDPATH += $$PWD/gui




