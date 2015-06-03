#ifndef TCPPAYLOAD_H
#define TCPPAYLOAD_H

// includes from QT
#include <QString>

// includes from project
#include "entity_global.h"
#include "payload.h"

#define TH_OFF(th)      	(((th)->offset & 0xf0) >> 4)
#define TH_FIN  			0x01
#define TH_SYN  			0x02
#define TH_RST  			0x04
#define TH_PUSH 			0x08
#define TH_ACK  			0x10
#define TH_URG  			0x20
#define TH_ECE  			0x40
#define TH_CWR  			0x80
#define TH_FLAGS        	(TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)


/* TCP header */
typedef struct tcp_packet {
    /* source port */
    uint16_t 	source_port;
    /* destination port */
    uint16_t 	destination_port;
    /* sequence number */
    uint32_t 	sequence_number;
    /* acknowledgement number */
    uint32_t 	ack;
    /* data offset, rsvd */
    uint8_t     offset;
    /* flag-uri */
    uint8_t  	flags;
    /* window size */
    uint16_t 	window;
    /* checksum */
    uint16_t 	checksum;
    /* urgent pointer */
    uint16_t 	urgent_pointer;

}tcp_packet;

// pointer definition
class ENTITYSHARED_EXPORT TcpPayload;
typedef std::shared_ptr<TcpPayload> TcpPayloadPtr;

class ENTITYSHARED_EXPORT TcpPayload : public Payload
{
public:
    TcpPayload();
    ~TcpPayload();

    QString getSourcePort() const;
    void setSourcePort(const QString &value);
    void setSourcePort(const uint16_t& value);

    QString getDestPort() const;
    void setDestPort(const QString &value);
    void setDestPort(const uint16_t& value);

    QString getSequenceNumber() const;
    void setSequenceNumber(const QString &value);
    void setSequenceNumber(const uint32_t &value);

    QString getAck() const;
    void setAck(const QString &value);
    void setAck(const uint32_t &value);

    QString getOffsetTcp() const;
    void setOffsetTcp(const QString &value);
    void setOffsetTcp(const uint8_t &value);

    QString getFlags() const;
    void setFlags(const QString &value);
    void setFlags(const uint8_t &value);

    QString getWindow() const;
    void setWindow(const QString &value);
    void setWindow(const uint16_t &value);

    QString getChekcsumTcp() const;
    void setChekcsumTcp(const QString &value);
    void setChekcsumTcp(const uint16_t &value);

    QString getUrgetPointer() const;
    void setUrgetPointer(const QString &value);
    void setUrgetPointer(const uint16_t &value);

    // Payload interface
    void setRawData(const QByteArray &data);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    QString sourcePort;
    QString destPort;
    QString sequenceNumber;
    QString ack;
    QString offsetTcp;
    QString flags;
    QString window;
    QString chekcsumTcp;
    QString urgetPointer;


};

#endif // TCPPAYLOAD_H
