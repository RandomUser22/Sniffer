#ifndef INTERFACELISTTABLEMODEL_H
#define INTERFACELISTTABLEMODEL_H

#include <QAbstractTableModel>

#include "interfacemanager.h"
#include "sniffermanager.h"

class InterfaceListTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    InterfaceListTableModel(QObject *parent);
    virtual ~InterfaceListTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(
            const QModelIndex &index,
            int role = Qt::DisplayRole) const;

private:
    QList<QStringList> listOfItems;

};

#endif // INTERFACELISTTABLEMODEL_H
