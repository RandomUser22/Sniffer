#include "wlanavailableconnectionlist.h"

WlanAvailableConnectionList::WlanAvailableConnectionList(QObject *parent) :
    QAbstractTableModel(parent),
    listOfConnections()
{

}

WlanAvailableConnectionList::~WlanAvailableConnectionList()
{

}

int WlanAvailableConnectionList::rowCount(const QModelIndex &parent) const
{
    return listOfConnections.size();
}

int WlanAvailableConnectionList::columnCount(const QModelIndex &parent) const
{
    return WlanAvailableConnection::getNumberOfProperties();
}

QVariant WlanAvailableConnectionList::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {
        for(int i = 0; i< listOfConnections.size(); i++)
        {
            if(col == 0 && row == i)
            {
                return listOfConnections.at(i)->getProfileName();
            }
            if(col == 1 && row == i)
            {
                return listOfConnections.at(i)->getSsid();
            }
            if(col == 2 && row == i)
            {
                return listOfConnections.at(i)->getBbsTypeName();
            }
            if(col == 3 && row == i)
            {
                return listOfConnections.at(i)->getNrOfBssIdsString();
            }
            if(col == 4 && row == i)
            {
                return (listOfConnections.at(i)->getConnectable())?"yes":"no";
            }
            if(col == 5 && row == i)
            {
                return listOfConnections.at(i)->getConnectableReason();
            }
            if(col == 6 && row == i)
            {
                return listOfConnections.at(i)->getNrOfPhySupportedString();
            }
            if(col == 7 && row == i)
            {
                return listOfConnections.at(i)->getSignalQualityString();
            }
            if(col == 8 && row == i)
            {
                return listOfConnections.at(i)->getIrssiString();
            }
            if(col == 9 && row == i)
            {
                return (listOfConnections.at(i)->getSecurity())?"yes":"no";
            }
            if(col == 10 && row == i)
            {
                return listOfConnections.at(i)->getAuthAlgorithm();
            }
            if(col == 11 && row == i)
            {
                return listOfConnections.at(i)->getCipherAlgorithm();
            }
            if(col == 12 && row == i)
            {
                return (listOfConnections.at(i)->getCurrentlyConnected())?"yes":"no";
            }
            if(col == 13 && row == i)
            {
                return (listOfConnections.at(i)->getProfile())?"yes":"no";
            }
        }
    }
    return QVariant();
}

QVariant WlanAvailableConnectionList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Profile Name");
            case 1:
                return QString("SSID");
            case 2:
                return QString("BSS Type");
            case 3:
                return QString("Nr of BSS IDs");
            case 4:
                return QString("Connectable");
            case 5:
                return QString("Connectable Reason");
            case 6:
                return QString("Nr of PHY supported");
            case 7:
                return QString("Signal Quality");
            case 8:
                return QString("IRSSI");
            case 9:
                return QString("Security");
            case 10:
                return QString("Auth algotithm");
            case 11:
                return QString("Cipher algotithm");
            case 12:
                return QString("Currentlly connected");
            case 13:
                return QString("Profile");
            default:
                return QString("");
            }
        }
    }
    return QVariant();
}
#include <QDebug>
QList<WlanAvailableConnectionPtr> WlanAvailableConnectionList::getListOfConnections()
{
    return listOfConnections;
}

void WlanAvailableConnectionList::addConnection(WlanAvailableConnectionPtr value)
{
    listOfConnections.push_back(value);
}


