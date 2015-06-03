#ifndef LOGICFACADE_H
#define LOGICFACADE_H

// includes from standard library
#include <memory>
#include <cstdint>

// includes from QT
#include <QObject>
#include <QList>

// includes from current sub-project
#include "logic_global.h"
#include "networkinterfacemanager.h"
#include "sniffingmanager.h"
#include "packet.h"
#include "accesspointmanager.h"
#include "wlanavailableconnection.h"

// includes from other sub-projects
#include "networkinterface.h"

// pointer definition
class LOGICSHARED_EXPORT LogicFacade;
typedef std::shared_ptr<LogicFacade> LogicFacadePtr;

class LOGICSHARED_EXPORT LogicFacade : public QObject
{
    Q_OBJECT
public:
    // destructor
    virtual ~LogicFacade();

    // static instance set and remove
    static LogicFacadePtr getInstance();
    static void removeInstance();

    // public methods
    QList<NetworkInterfacePtr> getListOfNetworkInterfacess();
    void startSniffing(NetworkInterfacePtr inter, uint32_t nrOfPacketsToSniff = 0);
    void stopSniffing();
    WlanInterfacePtr getDetailedAccessPointInformation(NetworkInterfacePtr value);
    void getSignalStrenght(WlanInterfacePtr inter);

signals:
    void packageSniffed(PacketPtr capturedPacket);
    void signalStrenghtChanged(uint32_t value);

private slots:
    void onPackageCaptured(PacketPtr capturedPacket);
    void onSignalStrenghtChanged(uint32_t value);

private:
    // constructor, copy-constructor, operator=
    LogicFacade();
    LogicFacade(LogicFacade const&);
    void operator=(LogicFacade const&);

    // single instance
    static LogicFacadePtr instance;

    NetworkInterfaceManagerPtr networkInterfaceManager;
    SniffingManagerPtr sniffingManager;
    AccessPointManagerPtr accessPointManager;
};

#endif // LOGICFACADE_H
