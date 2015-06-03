#ifndef SNIFFINGMANAGER_H
#define SNIFFINGMANAGER_H

// includes from standard library
#include <cstdint>

// includes from QT
#include <QObject>
#include <QMutex>

// includes from project
#include "networkinterface.h"
#include "pcapexception.h"
#include "packet.h"

// includes from external libraries
#include <pcap.h>

// pointer definition
class SniffingManager;
typedef std::shared_ptr<SniffingManager> SniffingManagerPtr;

class SniffingManager : public QObject
{
    Q_OBJECT
public:
    // destructor
    virtual ~SniffingManager();

    // static instance set and remove
    static SniffingManagerPtr getInstance();
    static void removeInstance();

    // public methods
    void startSniffing(NetworkInterfacePtr inter, uint32_t nrOfPacketsToSniff = 0);
    void stopSniffing();

signals:
    void packageCaptured(PacketPtr capturedPacket);

private:
    // constructor, copy-constructor, operator=
    SniffingManager();
    SniffingManager(SniffingManager const&);
    void operator=(SniffingManager const&);

    // single instance
    static SniffingManagerPtr instance;

    pcap_t *handle;
    bool stopSingnaled;
    QMutex mutex;
};

#endif // SNIFFINGMANAGER_H
