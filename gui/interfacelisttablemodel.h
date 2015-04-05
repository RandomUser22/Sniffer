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
    QVariant headerData(
            int section, Qt::Orientation orientation, int role) const;

    SniffingInterfacePtr getSelectedInterface(int input);

private:
    QList<SniffingInterfacePtr> listOfItems;

};

#endif // INTERFACELISTTABLEMODEL_H
