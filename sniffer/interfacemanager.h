#ifndef INTERFACEMANAGER_H
#define INTERFACEMANAGER_H

#include "sniffer_global.h"

#include <QStringList>

#include "NetworkInterface.h"

// interfata utilizata pentru a ne intoarce lista de interfete prin care putem snifui pachete
class SNIFFERSHARED_EXPORT InterfaceManager
{
public:
    InterfaceManager();
    virtual ~InterfaceManager();

    // metoda utilizata pentru a ne returna numele, o descriere si numele actual al interfetei prin cae putem snifui
    static QList<QStringList> getListOfInterfacess();

    // metoda utilizata pentru a ne returna o lista detaliata a interfetei
    static QList<QStringList> getDetailsOfInterface(QString inter);

private:
    static QStringList getAdaptersInfo(QString adaptName = "");
    static QString getAdapterType(UINT type);
};

#endif // INTERFACEMANAGER_H
