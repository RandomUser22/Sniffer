#include "wlaninterface.h"

WlanInterface::WlanInterface(QObject *parent) :
    NetworkInterface(parent),
    guid(""),
    wlanDescription(""),
    connectionType(WlanConnectionType_unknown),
    connctionsList(WlanAvailableConnectionListPtr(new WlanAvailableConnectionList()))
{

}

WlanInterface::~WlanInterface()
{

}
WlanConnectionType WlanInterface::getConnectionType() const
{
    return connectionType;
}

QString WlanInterface::getConnectionTypeName() const
{
    QString toReturn = "";
    switch (connectionType) {
    case WlanConnectionType_not_ready:
        toReturn = "not ready";
        break;
    case WlanConnectionType_connected:
        toReturn = "connected";
        break;
    case WlanConnectionType_ad_hoc_network_formed:
        toReturn = "ad hoc network";
        break;
    case WlanConnectionType_disconecting:
        toReturn = "disconecting";
        break;
    case WlanConnectionType_disconected:
        toReturn = "disconected";
        break;
    case WlanConnectionType_associating:
        toReturn = "associating";
        break;
    case WlanConnectionType_discovering:
        toReturn = "discovering";
        break;
    case WlanConnectionType_authenticateing:
        toReturn = "authenticateing";
        break;
    case WlanConnectionType_unknown:
    default:
        toReturn = "unknown";
        break;
    }
    return toReturn;
}

void WlanInterface::setConnectionType(const WlanConnectionType &value)
{
    connectionType = value;
}

int WlanInterface::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return 21;
}

int WlanInterface::columnCount(const QModelIndex &parent) const
{
    (void)parent;
    return 2;
}

QVariant WlanInterface::data(const QModelIndex &index, int role) const
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
        if(col == 0 && row == 18)
        {
            return QString("WLAN GUID");
        }
        if(col == 1 && row == 18)
        {
            return QString("%1").arg(getGuid());
        }
        if(col == 0 && row == 19)
        {
            return QString("WLAN description");
        }
        if(col == 1 && row == 19)
        {
            return QString("%1").arg(getWlanDescription());
        }
        if(col == 0 && row == 20)
        {
            return QString("WLAN connection state");
        }
        if(col == 1 && row == 20)
        {
            return QString("%1").arg(getConnectionTypeName());
        }
    }
    if (role == Qt::BackgroundRole)
    {
        QColor blueColor(153, 204, 255);
        QColor redColor(255, 204, 153);
        QColor greenColor(204, 255, 153);
        if(row <= 8)
        {
            QBrush blueBackground(blueColor);
            return blueBackground;
        }
        else if ((row > 8) && (row <= 17))
        {
            QBrush redBackground(redColor);
            return redBackground;
        }
        else
        {
            QBrush greenBackground(greenColor);
            return greenBackground;
        }
    }
    return QVariant();
}
WlanAvailableConnectionListPtr WlanInterface::getConnctionsList()
{
    return connctionsList;
}

void WlanInterface::addWlanConnction(WlanAvailableConnectionPtr availableConnction)
{
    qDebug("ccc -- 1");
    connctionsList->addConnection(availableConnction);
}

QString WlanInterface::getWlanDescription() const
{
    return wlanDescription;
}

void WlanInterface::setWlanDescription(const QString &value)
{
    wlanDescription = value;
}

QString WlanInterface::getGuid() const
{
    return guid;
}

void WlanInterface::setGuid(const QString &value)
{
    guid = value;
}


