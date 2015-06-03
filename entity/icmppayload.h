#ifndef ICMPPAYLOAD_H
#define ICMPPAYLOAD_H

// includes from QT
#include <QString>

// includes from project
#include "payload.h"

/* UDP header */
typedef struct icmp_packet {
    /* source port */
    uint8_t 	type_of_message;
    /* destination port */
    uint8_t 	code;
    /* sequence number */
    uint16_t 	checksum;
    /* acknowledgement number */
    uint16_t 	identifier;
    uint16_t 	sequence_number;

}icmp_packet;

// pointer definition
class IcmpPayload;
typedef std::shared_ptr<IcmpPayload> IcmpPayloadPtr;

class IcmpPayload : public Payload
{
public:
    IcmpPayload();
    ~IcmpPayload();

    QString getTypeOfMessage() const;
    void setTypeOfMessage(const QString &value);

    QString getCode() const;
    void setCode(const QString &value);

    QString getChecksum() const;
    void setChecksum(const QString &value);

    QString getIndentifier() const;
    void setIndentifier(const QString &value);

    QString getSequenceNumber() const;
    void setSequenceNumber(const QString &value);

    // Payload interface
    void setRawData(const QByteArray &data);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QString typeOfMessage;
    QString code;
    QString checksum;
    QString indentifier;
    QString sequenceNumber;


};

#endif // ICMPPAYLOAD_H
