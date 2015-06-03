#ifndef WLANAVAILABLECONNECTIONLIST_H
#define WLANAVAILABLECONNECTIONLIST_H

#include <QList>
#include <QAbstractTableModel>

#include "entity_global.h"
#include "wlanavailableconnection.h"

// pointer definition
class ENTITYSHARED_EXPORT WlanAvailableConnectionList;
typedef std::shared_ptr<WlanAvailableConnectionList> WlanAvailableConnectionListPtr;


class WlanAvailableConnectionList :
        public QAbstractTableModel
{
    Q_OBJECT
public:
    WlanAvailableConnectionList(QObject *parent = 0);
    ~WlanAvailableConnectionList();

    QList<WlanAvailableConnectionPtr> getListOfConnections();
    void addConnection(WlanAvailableConnectionPtr value);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QList<WlanAvailableConnectionPtr> listOfConnections;

};

#endif // WLANAVAILABLECONNECTIONLIST_H
