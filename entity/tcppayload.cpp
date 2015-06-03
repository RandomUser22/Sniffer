#include "tcppayload.h"

TcpPayload::TcpPayload() :
    Payload(),
    sourcePort(""),
    destPort(""),
    sequenceNumber(""),
    ack(""),
    offsetTcp(""),
    flags(""),
    window(""),
    chekcsumTcp(""),
    urgetPointer("")
{

}

TcpPayload::~TcpPayload()
{

}
QString TcpPayload::getSourcePort() const
{
    return sourcePort;
}

void TcpPayload::setSourcePort(const QString &value)
{
    sourcePort = value;
}

void TcpPayload::setSourcePort(const uint16_t& value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt16(value);
    sourcePort = QString(temp);
}
QString TcpPayload::getDestPort() const
{
    return destPort;
}

void TcpPayload::setDestPort(const QString &value)
{
    destPort = value;
}
void TcpPayload::setDestPort(const uint16_t& value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt16(value);
    destPort = QString(temp);
}
QString TcpPayload::getSequenceNumber() const
{
    return sequenceNumber;
}

void TcpPayload::setSequenceNumber(const QString &value)
{
    sequenceNumber = value;
}

void TcpPayload::setSequenceNumber(const uint32_t &value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt32(value);
    sequenceNumber = QString(temp);
}
QString TcpPayload::getAck() const
{
    return ack;
}

void TcpPayload::setAck(const QString &value)
{
    ack = value;
}
void TcpPayload::setAck(const uint32_t &value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt32(value);
    ack = QString(temp);
}

QString TcpPayload::getOffsetTcp() const
{
    return offsetTcp;
}

void TcpPayload::setOffsetTcp(const QString &value)
{
    offsetTcp = value;
}
void TcpPayload::setOffsetTcp(const uint8_t &value)
{
    QByteArray aux;
    aux.append(value);
    offsetTcp = QString(aux.toHex());
}

QString TcpPayload::getFlags() const
{
    return flags;
}

void TcpPayload::setFlags(const QString &value)
{
    flags = value;
}

void TcpPayload::setFlags(const uint8_t &value)
{
    QByteArray aux;
    aux.append(value);
    flags = QString(aux.toHex());
}

QString TcpPayload::getWindow() const
{
    return window;
}

void TcpPayload::setWindow(const QString &value)
{
    window = value;
}

void TcpPayload::setWindow(const uint16_t &value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt16(value);
    window = QString(temp);
}

QString TcpPayload::getChekcsumTcp() const
{
    return chekcsumTcp;
}

void TcpPayload::setChekcsumTcp(const QString &value)
{
    chekcsumTcp = value;
}

void TcpPayload::setChekcsumTcp(const uint16_t &value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt16(value);
    chekcsumTcp = QString(temp);
}

QString TcpPayload::getUrgetPointer() const
{
    return urgetPointer;
}

void TcpPayload::setUrgetPointer(const QString &value)
{
    urgetPointer = value;
}

void TcpPayload::setUrgetPointer(const uint16_t &value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt16(value);
    urgetPointer = QString(temp);
}

#include <QDebug>
void TcpPayload::setRawData(const QByteArray &data)
{
    int size_tcp;
    const struct tcp_packet *tcp;
    tcp = reinterpret_cast<const struct tcp_packet*>(data.data());
    size_tcp = TH_OFF(tcp)*4;
    if (size_tcp < 20) {
        qDebug("   * Invalid TCP header length: %u bytes\n", size_tcp);

    }
    else
    {
        setSourcePort(ntohs(tcp->source_port));
        setDestPort(ntohs(tcp->destination_port));
        setSequenceNumber(tcp->sequence_number);
        setAck(tcp->ack);
        setOffsetTcp(tcp->offset);
        setFlags(tcp->flags);
        setWindow(tcp->window);
        setChekcsumTcp(tcp->checksum);
        setUrgetPointer(tcp->urgent_pointer);
    }
}

int TcpPayload::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 9;
}

int TcpPayload::columnCount(const QModelIndex &parent) const
{
    (void)parent;
    return 2;
}

QVariant TcpPayload::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {
        if(col == 0 && row == 0)
        {
            return QString("Source Port");
        }
        if(col == 1 && row == 0)
        {
            return getSourcePort();
        }
        if(col == 0 && row == 1)
        {
            return QString("Destination Port");
        }
        if(col == 1 && row == 1)
        {
            return getDestPort();
        }
        if(col == 0 && row == 2)
        {
            return QString("Sequence number");
        }
        if(col == 1 && row == 2)
        {
            return getSequenceNumber();
        }
        if(col == 0 && row == 3)
        {
            return QString("Acknolege");
        }
        if(col == 1 && row == 3)
        {
            return getAck();
        }
        if(col == 0 && row == 4)
        {
            return QString("Offset");
        }
        if(col == 1 && row == 4)
        {
            return getOffsetTcp();
        }
        if(col == 0 && row == 5)
        {
            return QString("Flags");
        }
        if(col == 1 && row == 5)
        {
            return getFlags();
        }
        if(col == 0 && row == 6)
        {
            return QString("Window");
        }
        if(col == 1 && row == 6)
        {
            return getWindow();
        }
        if(col == 0 && row == 7)
        {
            return QString("Checksum");
        }
        if(col == 1 && row == 7)
        {
            return getChekcsumTcp();
        }
        if(col == 0 && row == 8)
        {
            return QString("Urgent Pointer");
        }
        if(col == 1 && row == 8)
        {
            return getUrgetPointer();
        }
    }
    return QVariant();
}










