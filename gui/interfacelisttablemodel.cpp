#include "interfacelisttablemodel.h"

#define NR_OF_COLUMS 2

InterfaceListTableModel::InterfaceListTableModel(QObject *parent)
        : QAbstractTableModel(parent)
{
    listOfItems = InterfaceManager::getListOfInterfacess();
}

InterfaceListTableModel::~InterfaceListTableModel()
{

}

int InterfaceListTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return listOfItems.size();
}

int InterfaceListTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return NR_OF_COLUMS;
}

QVariant InterfaceListTableModel::data(
        const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    if (role == Qt::DisplayRole)
    {
        return listOfItems.at(row).
                at(col);
    }
    return QVariant();
}
