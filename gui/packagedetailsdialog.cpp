#include "packagedetailsdialog.h"
#include "ui_packagedetailsdialog.h"

PackageDetailsDialog::PackageDetailsDialog(PacketPtr input, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PackageDetailsDialog),
    packetDisplayed(input)
{
    ui->setupUi(this);

    ui->listWidget->addItem("Ethernet");
    ui->listWidget->addItem("IP");
    switch (input->getIpHeader()->getProtocol()) {
    case ProtocolType_ICMP:
        ui->listWidget->addItem("ICMP");
        break;
    case ProtocolType_TCP:
        ui->listWidget->addItem("TCP");
        break;
    case ProtocolType_UDP:
        ui->listWidget->addItem("UDP");
        break;
    default:
        break;
    }
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setVisible(false);
}

PackageDetailsDialog::~PackageDetailsDialog()
{
    delete ui;
}

void PackageDetailsDialog::on_close_button_clicked()
{
    this->close();
}

void PackageDetailsDialog::on_listWidget_clicked(const QModelIndex &index)
{
    switch (index.row()) {
    case 0:
    {
        ui->tableView->setModel(packetDisplayed->getEthernetHeader().get());
    }
        break;
    case 1:
    {
        ui->tableView->setModel(packetDisplayed->getIpHeader().get());
    }
        break;
    case 2:
    {
        ui->tableView->setModel(packetDisplayed->getPayload().get());
    }
        break;
    default:
        break;
    }
}
