#ifndef INTERFACELIST_H
#define INTERFACELIST_H

#include <QDialog>

#include "interfacelisttablemodel.h"

namespace Ui {
class InterfaceList;
}

class InterfaceList : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceList(QWidget *parent = 0);
    ~InterfaceList();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_buttonBox_accepted();

signals:
    void deviceSelected(SniffingInterfacePtr device);

private:
    Ui::InterfaceList *ui;

    InterfaceListTableModel tableModel;
};

#endif // INTERFACELIST_H
