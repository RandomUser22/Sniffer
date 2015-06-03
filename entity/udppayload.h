#ifndef UDPPAYLOAD_H
#define UDPPAYLOAD_H

// includes from QT
#include <QString>

// includes from project
#include "payload.h"

/* UDP header */
typedef struct udp_packet {
    /* source port */
    uint16_t 	source_port;
    /* destination port */
    uint16_t 	destination_port;
    /* sequence number */
    uint16_t 	lenght;
    /* acknowledgement number */
    uint16_t 	checksum;

}udp_packet;

// pointer definition
class UdpPayload;
typedef std::shared_ptr<UdpPayload> UdpPayloadPtr;

class UdpPayload : public Payload
{
public:
    UdpPayload();
    ~UdpPayload();

    QString getSourcePort() const;
    void setSourcePort(const QString &value);

    QString getDestPort() const;
    void setDestPort(const QString &value);

    QString getLenght() const;
    void setLenght(const QString &value);

    QString getChekcsum() const;
    void setChekcsum(const QString &value);

    // Payload interface
    void setRawData(const QByteArray &data);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QString sourcePort;
    QString destPort;
    QString lenght;
    QString chekcsum;

};

#endif // UDPPAYLOAD_H
