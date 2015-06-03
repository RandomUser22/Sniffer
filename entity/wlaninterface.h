#ifndef WLANINTERFACE_H
#define WLANINTERFACE_H

#include "networkinterface.h"
#include "entity_global.h"
#include "wlanavailableconnection.h"
#include "enum_wlanconnection.h"
#include "wlanavailableconnectionlist.h"

// pointer definition
class ENTITYSHARED_EXPORT WlanInterface;
typedef std::shared_ptr<WlanInterface> WlanInterfacePtr;

class ENTITYSHARED_EXPORT WlanInterface : public NetworkInterface
{
public:
    WlanInterface(QObject *parent = 0);
    ~WlanInterface();

    QString getGuid() const;
    void setGuid(const QString &value);

    QString getWlanDescription() const;
    void setWlanDescription(const QString &value);

    WlanConnectionType getConnectionType() const;
    QString getConnectionTypeName() const;
    void setConnectionType(const WlanConnectionType &value);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    WlanAvailableConnectionListPtr getConnctionsList();
    void addWlanConnction(WlanAvailableConnectionPtr availableConnction);

private:
    QString guid;
    QString wlanDescription;
    WlanConnectionType connectionType;
    WlanAvailableConnectionListPtr connctionsList;
};

#endif // WLANINTERFACE_H
