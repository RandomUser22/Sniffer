#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

// includes from standard memory
#include <memory>
#include <cstdint>

// includes from QT
#include <QString>
#include <QAbstractTableModel>
#include <QColor>
#include <QBrush>

// includes from current sub-project
#include "entity_global.h"
#include "enum_adaptertype.h"
#include "pcapaddressnetworkinterface.h"

class ENTITYSHARED_EXPORT NetworkInterface;
typedef std::shared_ptr<NetworkInterface> NetworkInterfacePtr;

class ENTITYSHARED_EXPORT NetworkInterface : public QAbstractTableModel
{
    Q_OBJECT
public:
    NetworkInterface(QObject *parent = 0);
    virtual ~NetworkInterface();

    QString getPcapName() const;
    void setPcapName(const QString &value);

    QString getPcapDescription() const;
    void setPcapDescription(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    entity::AdapterType getAdapterType() const;
    void setAdapterType(const entity::AdapterType &value);

    QString getIpAddress() const;
    void setIpAddress(const QString &value);

    QString getIpMask() const;
    void setIpMask(const QString &value);

    QString getAdapterAddress() const;
    void setAdapterAddress(const QString &value);

    QString getGateway() const;
    void setGateway(const QString &value);

    bool getDhcpEnabled() const;
    void setDhcpEnabled(bool value);

    QString getDhcpServer() const;
    void setDhcpServer(const QString &value);

    uint8_t getNrOfProperties() const;

    bool getPcapLoopback() const;
    void setPcapLoopback(bool value);

    PcapAddressNetworkInterfacePtr getPcapAddress() const;
    void setPcapAddress(PcapAddressNetworkInterfacePtr value);

    QString getAdapterTypeName() const;

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    void setAdapterTypeName(const QString &value);
    void setAdapterTypeName(const entity::AdapterType &value);

    QString pcapName;
    QString pcapDescription;
    bool pcapLoopback;
    PcapAddressNetworkInterfacePtr pcapAddress;
    QString name;
    QString description;
    entity::AdapterType adapterType;
    QString adapterTypeName;
    QString ipAddress;
    QString ipMask;
    QString adapterAddress;
    QString gateway;
    bool dhcpEnabled;
    QString dhcpServer;
    uint8_t nrOfProperties;

};

#endif // NETWORKINTERFACE_H
