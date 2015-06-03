#include "pcapaddressnetworkinterface.h"

PcapAddressNetworkInterface::PcapAddressNetworkInterface()
    :addressFamilyNumber(0),
      addressFamilyName(""),
      address(""),
      netmask(""),
      broadcastAddress(""),
      destinationAddress("")
{

}

PcapAddressNetworkInterface::~PcapAddressNetworkInterface()
{

}
uint16_t PcapAddressNetworkInterface::getAddressFamilyNumber() const
{
    return addressFamilyNumber;
}

void PcapAddressNetworkInterface::setAddressFamilyNumber(const uint16_t &value)
{
    addressFamilyNumber = value;
}
QString PcapAddressNetworkInterface::getAddressFamilyName() const
{
    return addressFamilyName;
}

void PcapAddressNetworkInterface::setAddressFamilyName(const QString &value)
{
    addressFamilyName = value;
}
QString PcapAddressNetworkInterface::getAddress() const
{
    return address;
}

void PcapAddressNetworkInterface::setAddress(const QString &value)
{
    address = value;
}
QString PcapAddressNetworkInterface::getNetmask() const
{
    return netmask;
}

void PcapAddressNetworkInterface::setNetmask(const QString &value)
{
    netmask = value;
}
QString PcapAddressNetworkInterface::getBroadcastAddress() const
{
    return broadcastAddress;
}

void PcapAddressNetworkInterface::setBroadcastAddress(const QString &value)
{
    broadcastAddress = value;
}
QString PcapAddressNetworkInterface::getDestinationAddress() const
{
    return destinationAddress;
}

void PcapAddressNetworkInterface::setDestinationAddress(const QString &value)
{
    destinationAddress = value;
}







