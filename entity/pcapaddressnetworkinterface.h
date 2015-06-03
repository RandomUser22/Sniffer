#ifndef PCAPADDRESSNETWORKINTERFACE_H
#define PCAPADDRESSNETWORKINTERFACE_H

// includes from standard memory
#include <memory>
#include <cstdint>

// includes from QT
#include <QString>

// includes from current sub-project
#include "entity_global.h"

class ENTITYSHARED_EXPORT PcapAddressNetworkInterface;
typedef std::shared_ptr<PcapAddressNetworkInterface> PcapAddressNetworkInterfacePtr;

class ENTITYSHARED_EXPORT PcapAddressNetworkInterface
{
public:
    PcapAddressNetworkInterface();
    virtual ~PcapAddressNetworkInterface();

    uint16_t getAddressFamilyNumber() const;
    void setAddressFamilyNumber(const uint16_t &value);

    QString getAddressFamilyName() const;
    void setAddressFamilyName(const QString &value);

    QString getAddress() const;
    void setAddress(const QString &value);

    QString getNetmask() const;
    void setNetmask(const QString &value);

    QString getBroadcastAddress() const;
    void setBroadcastAddress(const QString &value);

    QString getDestinationAddress() const;
    void setDestinationAddress(const QString &value);

private:
    uint16_t addressFamilyNumber;
    QString addressFamilyName;
    QString address;
    QString netmask;
    QString broadcastAddress;
    QString destinationAddress;
};

#endif // PCAPADDRESSNETWORKINTERFACE_H
