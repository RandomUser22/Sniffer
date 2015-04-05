#include "interfacelisttablemodel.h"

#define NR_OF_COLUMS 3

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
        if(col == 0){
            return listOfItems.at(row)->getDescription();
        }
        if(col == 1){
            return listOfItems.at(row)->getIpAddress();
        }
        if(col == 2){
            return listOfItems.at(row)->getPcapName();
        }
    }
    return QVariant();
}

QVariant InterfaceListTableModel::headerData(
        int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Name");

        case 1:
            return tr("Address");

        case 2:
            return tr("Details");

        default:
            return QVariant();
        }
    }
    return QVariant();
}

SniffingInterfacePtr InterfaceListTableModel::getSelectedInterface(int input)
{
    if(input < listOfItems.size())
        return listOfItems.at(input);
    else
        return listOfItems.at(0);
}
