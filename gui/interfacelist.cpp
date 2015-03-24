#include "interfacelist.h"
#include "ui_interfacelist.h"

InterfaceList::InterfaceList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterfaceList),
    tableModel(parent)
{
    ui->setupUi(this);

    // setting the table view
    ui->tableView->setWordWrap(true);
    ui->tableView->setModel(&tableModel);
    ui->tableView->horizontalHeader()->
            setSectionResizeMode(QHeaderView::Stretch);

}

InterfaceList::~InterfaceList()
{
    delete ui;
}

void InterfaceList::on_listWidget_doubleClicked(const QModelIndex &index)
{
//    if(index.isValid())
//    {
//        QListWidgetItem* widgetItem = ui->listWidget->item(index.row());
//        QString dev = widgetItem->text();
//        emit deviceSelected(dev);
//        this->setResult(QDialog::Accepted);
//        this->close();
//    }

}
