#include "ethernetheader.h"

EthernetHeader::EthernetHeader(QObject *parent) :
    QAbstractTableModel(parent),
    macDestination(""),
    macSource(""),
    frameType("")
{

}

EthernetHeader::~EthernetHeader()
{

}
QString EthernetHeader::getMacDestination() const
{
    return macDestination;
}

void EthernetHeader::setMacDestination(const QString &value)
{
    macDestination = value;
}
void EthernetHeader::setMacDestination(const uint8_t *value)
{
    this->macDestination = Util::
            getStringFromUInt8Array(value,
                                    MAC_ADDRESS_SIZE);
    // make sure we have the appropiate size for a MAC address
    this->macDestination.truncate(12);

    // 'beautify' the data
    beautifyMacAddress(this->macDestination);
}
QString EthernetHeader::getMacSource() const
{
    return macSource;
}

void EthernetHeader::setMacSource(const QString &value)
{
    macSource = value;
}
void EthernetHeader::setMacSource(const uint8_t *value)
{
    this->macSource = Util::
            getStringFromUInt8Array(value,
                                    MAC_ADDRESS_SIZE);
    // make sure we have the appropiate size for a MAC address
    this->macSource.truncate(12);

    beautifyMacAddress(this->macSource);
}
QString EthernetHeader::getFrameType() const
{
    return frameType;
}

void EthernetHeader::setFrameType(const QString &value)
{
    frameType = value;
}

void EthernetHeader::setFrameType(const uint16_t &value)
{
    QByteArray temp = Util::getHexRepresentationFromUInt16(value);
    frameType = QString(temp);
}

int EthernetHeader::rowCount(const QModelIndex &parent) const
{
    return 3;
}

int EthernetHeader::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant EthernetHeader::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {
        if(col == 0 && row == 0)
        {
            return QString("MAC Destination");
        }
        if(col == 1 && row == 0)
        {
            return getMacDestination();
        }
        if(col == 0 && row == 1)
        {
            return QString("MAC Source");
        }
        if(col == 1 && row == 1)
        {
            return getMacSource();
        }
        if(col == 0 && row == 2)
        {
            return QString("Frame Type");
        }
        if(col == 1 && row == 2)
        {
            return getFrameType();
        }
    }
    return QVariant();
}

void EthernetHeader::beautifyMacAddress(QString &input)
{
    input = input.toUpper();
    for(int i = 2; i< input.size(); i=i+3){
        input.insert(i, ':');
    }
}




