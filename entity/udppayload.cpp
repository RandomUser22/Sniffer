#include "udppayload.h"

UdpPayload::UdpPayload()
{

}

UdpPayload::~UdpPayload()
{

}
QString UdpPayload::getSourcePort() const
{
    return sourcePort;
}

void UdpPayload::setSourcePort(const QString &value)
{
    sourcePort = value;
}
QString UdpPayload::getDestPort() const
{
    return destPort;
}

void UdpPayload::setDestPort(const QString &value)
{
    destPort = value;
}
QString UdpPayload::getLenght() const
{
    return lenght;
}

void UdpPayload::setLenght(const QString &value)
{
    lenght = value;
}
QString UdpPayload::getChekcsum() const
{
    return chekcsum;
}

void UdpPayload::setChekcsum(const QString &value)
{
    chekcsum = value;
}

void UdpPayload::setRawData(const QByteArray &data)
{

}

int UdpPayload::rowCount(const QModelIndex &parent) const
{
    return 9;
}

int UdpPayload::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant UdpPayload::data(const QModelIndex &index, int role) const
{
    return QVariant();
}



