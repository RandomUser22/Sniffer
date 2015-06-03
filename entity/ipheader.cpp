#include "ipheader.h"

IpHeader::IpHeader(QObject *parent) :
    QAbstractTableModel(parent),
    sizeIp(0),
    version(""),
    typeOfService(""),
    length(""),
    id(""),
    offsetIp(""),
    ttl(""),
    protocol(ProtocolType_unkown),
    checksumIp(""),
    ipSource(""),
    ipDest("")
{

}

IpHeader::~IpHeader()
{

}
uint32_t IpHeader::getSizeIp() const
{
    return sizeIp;
}

void IpHeader::setSizeIp(const uint32_t &value)
{
    sizeIp = value;
}

QString IpHeader::getVersion() const
{
    return version;
}

void IpHeader::setVersion(const QString &value)
{
    version = value;
}
void IpHeader::setVersion(const uint8_t &value)
{
    QByteArray aux;
    aux.append(value);
    version = QString(aux.toHex());
}
QString IpHeader::getTypeOfService() const
{
    return typeOfService;
}

void IpHeader::setTypeOfService(const QString &value)
{
    typeOfService = value;
}
void IpHeader::setTypeOfService(const uint8_t &value)
{
    QByteArray aux;
    aux.append(value);
    typeOfService = QString(aux.toHex());
}
QString IpHeader::getLength() const
{
    return length;
}

void IpHeader::setLength(const QString &value)
{
    length = value;
}
void IpHeader::setLength(const uint16_t &value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt16(value);
    length = QString(temp);

}
QString IpHeader::getId() const
{
    return id;
}

void IpHeader::setId(const QString &value)
{
    id = value;
}
void IpHeader::setId(const uint16_t &value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt16(value);
    id = QString(temp);
}
QString IpHeader::getOffsetIp() const
{
    return offsetIp;
}

void IpHeader::setOffsetIp(const QString &value)
{
    offsetIp = value;
}
void IpHeader::setOffsetIp(const uint16_t &value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt16(value);
    offsetIp = QString(temp);

}
QString IpHeader::getTtl() const
{
    return ttl;
}

void IpHeader::setTtl(const QString &value)
{
    ttl = value;
}
void IpHeader::setTtl(const uint8_t &value)
{
    QByteArray aux;
    aux.append(value);
    ttl = QString(aux.toHex());
}

// protocol
ProtocolType IpHeader::getProtocol() const
{
    return protocol;
}

QString IpHeader::getProtocolName() const
{
    QString toReturn = "unknown";
    switch (protocol) {
    case ProtocolType_ICMP:
        toReturn = "ICMP";
        break;
    case ProtocolType_TCP:
        toReturn = "TCP";
        break;
    case ProtocolType_UDP:
        toReturn = "UDP";
        break;
    default:
        break;
    }
    return toReturn;
}

uint8_t IpHeader::getProtocolValue() const
{
    return protocol;
}

void IpHeader::setProtocol(const uint8_t &value)
{
    uint8_t tempValue;
    QByteArray aux;
    aux.append(value);
    bool status = false;
    tempValue = QString(aux.toHex()).toUInt(&status, 16);
    qDebug("%d", tempValue);
    switch (tempValue) {
    case 1:
        protocol = ProtocolType_ICMP;
        break;
    case 6:
        protocol = ProtocolType_TCP;
        break;
    case 17:
        protocol = ProtocolType_UDP;
        break;
    default:
        protocol = ProtocolType_unkown;
        break;
    }
}
QString IpHeader::getChecksumIp() const
{
    return checksumIp;
}

void IpHeader::setChecksumIp(const QString &value)
{
    checksumIp = value;
}
void IpHeader::setChecksumIp(const uint16_t &value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt16(value);
    checksumIp = QString(temp);

}
QString IpHeader::getIpSource() const
{
    return ipSource;
}

void IpHeader::setIpSource(const QString &value)
{
    ipSource = value;
}
QString IpHeader::getIpDest() const
{
    return ipDest;
}

void IpHeader::setIpDest(const QString &value)
{
    ipDest = value;
}

int IpHeader::rowCount(const QModelIndex &parent) const
{
    return 10;
}

int IpHeader::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant IpHeader::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {
        if(col == 0 && row == 0)
        {
            return QString("Version");
        }
        if(col == 1 && row == 0)
        {
            return getVersion();
        }
        if(col == 0 && row == 1)
        {
            return QString("Type of Service");
        }
        if(col == 1 && row == 1)
        {
            return getTtl();
        }
        if(col == 0 && row == 2)
        {
            return QString("Lenght");
        }
        if(col == 1 && row == 2)
        {
            return getLength();
        }
        if(col == 0 && row == 3)
        {
            return QString("ID");
        }
        if(col == 1 && row == 3)
        {
            return getId();
        }
        if(col == 0 && row == 4)
        {
            return QString("Offset");
        }
        if(col == 1 && row == 4)
        {
            return getOffsetIp();
        }
        if(col == 0 && row == 5)
        {
            return QString("Time to live");
        }
        if(col == 1 && row == 5)
        {
            return getTtl();
        }
        if(col == 0 && row == 6)
        {
            return QString("Protocol");
        }
        if(col == 1 && row == 6)
        {
            return getProtocolName();
        }
        if(col == 0 && row == 7)
        {
            return QString("Checksum");
        }
        if(col == 1 && row == 7)
        {
            return getChecksumIp();
        }
        if(col == 0 && row == 8)
        {
            return QString("IP Source");
        }
        if(col == 1 && row == 8)
        {
            return getIpSource();
        }
        if(col == 0 && row == 9)
        {
            return QString("IP Destination");
        }
        if(col == 1 && row == 9)
        {
            return getIpDest();
        }
    }
    return QVariant();
}












