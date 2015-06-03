#ifndef ACCESSPOINTMANAGER_H
#define ACCESSPOINTMANAGER_H

// includes from standard library
#include <memory>
#include <string>
#include <sstream>

// includes from QT
#include <QObject>

// includes from project
#include "wlaninterface.h"
#include "wlanavailableconnection.h"

// pointer definition
class AccessPointManager;
typedef std::shared_ptr<AccessPointManager> AccessPointManagerPtr;

class AccessPointManager : public QObject
{
    Q_OBJECT
public:
    // destructor
    ~AccessPointManager();

    // static instance and remove
    static AccessPointManagerPtr getInstance();
    static void removeInstance();

    WlanInterfacePtr getDetailedAccessPointInformation(NetworkInterfacePtr value);
    void getSignalStrenght(WlanInterfacePtr inter);

signals:
    void signalStrChanged(uint32_t value);

private:
    // constructor, copy-constructor, operator=
    explicit AccessPointManager(QObject *parent = 0);
    AccessPointManager(AccessPointManager const&);
    void operator=(AccessPointManager const&);

    // single instance
    static AccessPointManagerPtr instance;

};

#endif // ACCESSPOINTMANAGER_H
