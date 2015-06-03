#include "interfacedetailsdialog.h"
#include "ui_interfacedetailsdialog.h"

InterfaceDetailsDialog::InterfaceDetailsDialog(
        NetworkInterfacePtr interfaceToSniff,
        QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterfaceDetailsDialog),
    sniffingInterface(interfaceToSniff)
{
    ui->setupUi(this);

    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->hide();

    ui->tableView->
            setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableView->setWordWrap(true);
    ui->tableView->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setShowGrid(false);

    ui->tableView->setModel(sniffingInterface.get());
}

InterfaceDetailsDialog::~InterfaceDetailsDialog()
{
    delete ui;
}

void InterfaceDetailsDialog::on_close_button_clicked()
{
    this->close();
}
