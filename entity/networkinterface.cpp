#include "networkinterface.h"

NetworkInterface::NetworkInterface(QObject *parent) :
    QAbstractTableModel(parent),
    pcapName(""),
    pcapDescription(""),
    name(""),
    description(""),
    adapterType(entity::adapter_type_unknown),
    ipAddress(""),
    ipMask(""),
    adapterAddress(""),
    gateway(""),
    dhcpEnabled(false),
    dhcpServer(""),
    nrOfProperties(18),
    pcapLoopback(false),
    pcapAddress(PcapAddressNetworkInterfacePtr(new PcapAddressNetworkInterface()))

{

}

NetworkInterface::~NetworkInterface()
{

}
QString NetworkInterface::getPcapName() const
{
    return pcapName;
}

void NetworkInterface::setPcapName(const QString &value)
{
    pcapName = value;
}
QString NetworkInterface::getPcapDescription() const
{
    return pcapDescription;
}

void NetworkInterface::setPcapDescription(const QString &value)
{
    pcapDescription = value;
}
QString NetworkInterface::getName() const
{
    return name;
}

void NetworkInterface::setName(const QString &value)
{
    name = value;
}
QString NetworkInterface::getDescription() const
{
    return description;
}

void NetworkInterface::setDescription(const QString &value)
{
    description = value;
}
entity::AdapterType NetworkInterface::getAdapterType() const
{
    return adapterType;
}

void NetworkInterface::setAdapterType(const entity::AdapterType &value)
{
    adapterType = value;
    setAdapterTypeName(value);
}
QString NetworkInterface::getIpAddress() const
{
    return ipAddress;
}

void NetworkInterface::setIpAddress(const QString &value)
{
    ipAddress = value;
}
QString NetworkInterface::getIpMask() const
{
    return ipMask;
}

void NetworkInterface::setIpMask(const QString &value)
{
    ipMask = value;
}
QString NetworkInterface::getAdapterAddress() const
{
    return adapterAddress;
}

void NetworkInterface::setAdapterAddress(const QString &value)
{
    adapterAddress = value;
}
QString NetworkInterface::getGateway() const
{
    return gateway;
}

void NetworkInterface::setGateway(const QString &value)
{
    gateway = value;
}
bool NetworkInterface::getDhcpEnabled() const
{
    return dhcpEnabled;
}

void NetworkInterface::setDhcpEnabled(bool value)
{
    dhcpEnabled = value;
}
QString NetworkInterface::getDhcpServer() const
{
    return dhcpServer;
}

void NetworkInterface::setDhcpServer(const QString &value)
{
    dhcpServer = value;
}
uint8_t NetworkInterface::getNrOfProperties() const
{
    return nrOfProperties;
}
bool NetworkInterface::getPcapLoopback() const
{
    return pcapLoopback;
}

void NetworkInterface::setPcapLoopback(bool value)
{
    pcapLoopback = value;
}
PcapAddressNetworkInterfacePtr NetworkInterface::getPcapAddress() const
{
    return pcapAddress;
}

void NetworkInterface::setPcapAddress(PcapAddressNetworkInterfacePtr value)
{
    pcapAddress = value;
}
QString NetworkInterface::getAdapterTypeName() const
{
    return adapterTypeName;
}

int NetworkInterface::rowCount(const QModelIndex &parent) const
{
    (void) parent;
    return 18;
}

int NetworkInterface::columnCount(const QModelIndex &parent) const
{
    (void) parent;
    return 2;
}

QVariant NetworkInterface::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {
        if(col == 0 && row == 0)
        {
            return QString("Pcap Device Name");
        }
        if(col == 1 && row == 0)
        {
            return getPcapName();
        }
        if(col == 0 && row == 1)
        {
            return QString("Pcap Description");
        }
        if(col == 1 && row == 1)
        {
            return getDescription();
        }
        if(col == 0 && row == 2)
        {
            return QString("Pcap Loopback");
        }
        if(col == 1 && row == 2)
        {
            return QString("%1").arg(getPcapLoopback()?"yes":"no");
        }
        if(col == 0 && row == 3)
        {
            return QString("Pcap Address Family Number");
        }
        if(col == 1 && row == 3)
        {
            return QString("%1").arg(getPcapAddress()->getAddressFamilyNumber());
        }
        if(col == 0 && row == 4)
        {
            return QString("Pcap Address Family Name");
        }
        if(col == 1 && row == 4)
        {
            return QString("%1").arg(getPcapAddress()->getAddressFamilyName());
        }
        if(col == 0 && row == 5)
        {
            return QString("Pcap Address");
        }
        if(col == 1 && row == 5)
        {
            return QString("%1").arg(getPcapAddress()->getAddress());
        }
        if(col == 0 && row == 6)
        {
            return QString("Pcap Destination Address");
        }
        if(col == 1 && row == 6)
        {
            return QString("%1").arg(getPcapAddress()->getDestinationAddress());
        }
        if(col == 0 && row == 7)
        {
            return QString("Pcap Broadcast Address");
        }
        if(col == 1 && row == 7)
        {
            return QString("%1").arg(getPcapAddress()->getBroadcastAddress());
        }
        if(col == 0 && row == 8)
        {
            return QString("Pcap NetMask");
        }
        if(col == 1 && row == 8)
        {
            return QString("%1").arg(getPcapAddress()->getNetmask());
        }
        if(col == 0 && row == 9)
        {
            return QString("Name");
        }
        if(col == 1 && row == 9)
        {
            return QString("%1").arg(getName());
        }
        if(col == 0 && row == 10)
        {
            return QString("Description");
        }
        if(col == 1 && row == 10)
        {
            return QString("%1").arg(getDescription());
        }
        if(col == 0 && row == 11)
        {
            return QString("Adapter type");
        }
        if(col == 1 && row == 11)
        {
            return QString("%1").arg(getAdapterTypeName());
        }
        if(col == 0 && row == 12)
        {
            return QString("IP address");
        }
        if(col == 1 && row == 12)
        {
            return QString("%1").arg(getIpAddress());
        }
        if(col == 0 && row == 13)
        {
            return QString("IP mask");
        }
        if(col == 1 && row == 13)
        {
            return QString("%1").arg(getIpMask());
        }
        if(col == 0 && row == 14)
        {
            return QString("Adapter address");
        }
        if(col == 1 && row == 14)
        {
            return QString("%1").arg(getAdapterAddress());
        }
        if(col == 0 && row == 15)
        {
            return QString("GateWay");
        }
        if(col == 1 && row == 15)
        {
            return QString("%1").arg(getGateway());
        }
        if(col == 0 && row == 16)
        {
            return QString("DHCP enabled");
        }
        if(col == 1 && row == 16)
        {
            return QString("%1").arg(getDhcpEnabled()?"yes":"no");
        }
        if(col == 0 && row == 17)
        {
            return QString("DHCP server");
        }
        if(col == 1 && row == 17)
        {
            return QString("%1").arg(getDhcpServer());
        }
    }
    if (role == Qt::BackgroundRole)
    {
        QColor blueColor(153, 204, 255);
        QColor redColor(255, 204, 153);
        if(row > 8)
        {
            QBrush redBackground(redColor);
            return redBackground;
        }
        else
        {
            QBrush blueBackground(blueColor);
            return blueBackground;
        }
    }
    return QVariant();
}

void NetworkInterface::setAdapterTypeName(const QString &value)
{
    adapterTypeName = value;
}

void NetworkInterface::setAdapterTypeName(const entity::AdapterType &value)
{
    switch (value) {
    case entity::adapter_type_other:
        adapterTypeName = QString("Other");
        break;
    case entity::adapter_type_ethernet:
        adapterTypeName = QString("Ethernet");
        break;
    case entity::adapter_type_tokenring:
        adapterTypeName = QString("Tokenring");
        break;
    case entity::adapter_type_fddi:
        adapterTypeName = QString("FDDI");
        break;
    case entity::adapter_type_ppp:
        adapterTypeName = QString("PPP");
        break;
    case entity::adapter_type_loopback:
        adapterTypeName = QString("Loopback");
        break;
    case entity::adapter_type_slip:
        adapterTypeName = QString("Slip");
        break;
    case entity::adapter_type_ieee80211:
        adapterTypeName = QString("WiFi");
        break;
    case entity::adapter_type_unknown:
    default:
        adapterTypeName = QString("Unknown");
        break;
    }
}


















