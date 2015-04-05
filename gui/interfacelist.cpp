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

    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(
                QAbstractItemView::SelectRows);

}

InterfaceList::~InterfaceList()
{
    delete ui;
}

void InterfaceList::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        SniffingInterfacePtr dev = (tableModel.
                       getSelectedInterface(index.row()));
        emit deviceSelected(dev);
        this->setResult(QDialog::Accepted);
        this->close();
    }
}

void InterfaceList::on_buttonBox_accepted()
{
    int index = ui->tableView->selectionModel()->currentIndex().row();

    SniffingInterfacePtr dev = (tableModel.
                   getSelectedInterface(index));
    emit deviceSelected(dev);
    this->setResult(QDialog::Accepted);
    this->close();
}
