#ifndef PACKET_H
#define PACKET_H

// includes from standard memory
#include <memory>
#include <cstdint>

// includes from QT
#include <QObject>
#include <QString>
#include <QByteArray>

// includes from current project
#include "entity_global.h"
#include "networkinclude.h"
#include "ethernetheader.h"
#include "ipheader.h"
#include "payload.h"
#include "tcppayload.h"
#include "udppayload.h"
#include "icmppayload.h"

// pointer definition
class ENTITYSHARED_EXPORT Packet;
typedef std::shared_ptr<Packet> PacketPtr;

class ENTITYSHARED_EXPORT Packet : public QObject
{
    Q_OBJECT
public:
    Packet();
    virtual ~Packet();

    EthernetHeaderPtr getEthernetHeader() const;
    IpHeaderPtr getIpHeader() const;
    PayloadPtr getPayload() const;

    uint32_t getSizeOfPacket() const;
    void setSizeOfPacket(const uint32_t &value);

    void setRawData(const uint8_t *input);
private:
    uint32_t sizeOfPacket;
    QByteArray rawData;

    EthernetHeaderPtr ethernetHeader;
    IpHeaderPtr ipHeader;
    PayloadPtr payload;

    bool validIpHeader;
};

#endif // PACKET_H
