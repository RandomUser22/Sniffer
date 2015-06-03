#ifndef NETWORKINTERFACEMANAGER_H
#define NETWORKINTERFACEMANAGER_H

// includes from standard library
#include <memory>
#include <sstream>

// includes from QT
#include <QList>
#include <QStringList>

// includes from other subproject
#include "networkinterface.h"
#include "pcapexception.h"
#include "enum_adaptertype.h"

// includes from external libraries
#include <pcap.h>

// pointer definition
class NetworkInterfaceManager;
typedef std::shared_ptr<NetworkInterfaceManager> NetworkInterfaceManagerPtr;

class NetworkInterfaceManager
{
public:
    // destructor
    virtual ~NetworkInterfaceManager();

    // static instance set and remove
    static NetworkInterfaceManagerPtr getInstance();
    static void removeInstance();

    // public methods
    QList<NetworkInterfacePtr> getListOfSniffingInterfacess();

private:
    // constructor, copy-constructor, operator=
    NetworkInterfaceManager();
    NetworkInterfaceManager(NetworkInterfaceManager const&);
    void operator=(NetworkInterfaceManager const&);

    // single instance
    static NetworkInterfaceManagerPtr instance;
};

#endif // NETWORKINTERFACEMANAGER_H
