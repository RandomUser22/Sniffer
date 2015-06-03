#include "packetsniffingwidget.h"
#include "ui_packetsniffingwidget.h"

PacketSniffingWidget::PacketSniffingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PacketSniffingWidget),
    logicFacade(LogicFacade::getInstance()),
    interfaceToSniff(),
    nrOfPacketsToSniff(0),
    nrOfPacketsSniffed(0),
    listOfCaptuedPackages()
{
    ui->setupUi(this);
    qRegisterMetaType<PacketPtr>("PacketPtr");
    connect(logicFacade.get(), SIGNAL(packageSniffed(PacketPtr)),
            this, SLOT(onPackageSniffed(PacketPtr)));

    setupWidgetDisplay();
}

PacketSniffingWidget::~PacketSniffingWidget()
{
    delete ui;
}

void PacketSniffingWidget::setupWidgetDisplay()
{
    ui->start_button->setEnabled(false);
    ui->stop_button->setEnabled(false);
    ui->progressBar->setVisible(false);
    ui->text_nr_of_packets_label->setVisible(false);
    ui->nr_of_packets_label->setVisible(false);

    ui->checkBox->setChecked(true);
    ui->nr_of_packets_lineEdit->setEnabled(true);
    ui->nr_of_packets_lineEdit->setText("10");
    ui->nr_of_packets_lineEdit->setValidator(
                new QIntValidator(1, 50000, this));

    ui->tableWidget->setColumnCount(6);
    QStringList listOfColoumnHeaderNames;
    listOfColoumnHeaderNames.append("time");
    listOfColoumnHeaderNames.append("          source          ");
    listOfColoumnHeaderNames.append("        destination       ");
    listOfColoumnHeaderNames.append("protocol");
    listOfColoumnHeaderNames.append("length");
    listOfColoumnHeaderNames.append("info");
    ui->tableWidget->setHorizontalHeaderLabels(listOfColoumnHeaderNames);
    ui->tableWidget->
            setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setWordWrap(true);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(5, QHeaderView::Stretch);
}

void PacketSniffingWidget::on_checkBox_toggled(bool checked)
{
    ui->nr_of_packets_lineEdit->setEnabled(checked);
}

void PacketSniffingWidget::on_select_interface_button_clicked()
{
    SelectInterfaceDialog s(this);
    connect(&s, SIGNAL(interfaceSelected(NetworkInterfacePtr)),
            this, SLOT(onInterfaceSelected(NetworkInterfacePtr)));
    s.exec();
}

void PacketSniffingWidget::onInterfaceSelected(NetworkInterfacePtr inter)
{
    interfaceToSniff = inter;
    ui->sniffing_interface_label->setText(interfaceToSniff->getDescription());
    ui->start_button->setEnabled(true);
}

void PacketSniffingWidget::on_start_button_clicked()
{
    // TODO: beter thread handling
    ui->start_button->setEnabled(false);
    QFuture<void> future;
    try
    {
        if(ui->checkBox->isChecked())
        {
            nrOfPacketsToSniff = ui->nr_of_packets_lineEdit->text().toShort();
            nrOfPacketsSniffed = 0;
        }
        else
        {
            nrOfPacketsToSniff = 0;
        }
        future = QtConcurrent::run(logicFacade.get(),
                                   &LogicFacade::startSniffing, interfaceToSniff, nrOfPacketsToSniff);
        ui->checkBox->setDisabled(true);
        ui->stop_button->setEnabled(true);
    }
    catch(PcapException& e)
    {
        QMessageBox::warning(this,tr("Pcap exception"),tr(e.what()));
        ui->stop_button->setEnabled(false);
        ui->start_button->setEnabled(true);
    }
}

void PacketSniffingWidget::on_stop_button_clicked()
{
    ui->stop_button->setEnabled(false);
    logicFacade->stopSniffing();
    ui->start_button->setEnabled(true);
    ui->checkBox->setCheckable(true);
}
#include <QDebug>
void PacketSniffingWidget::onPackageSniffed(PacketPtr capturedPacket)
{

    listOfCaptuedPackages.push_back(capturedPacket);
    ui->tableWidget->insertRow(
                ui->tableWidget->rowCount());
    ui->tableWidget->
            setCellWidget(
                ui->tableWidget->rowCount()-1, 1,
                new QLabel(QString(capturedPacket
                                   ->getEthernetHeader()->getMacSource())));
    ui->tableWidget->
            setCellWidget(
                ui->tableWidget->rowCount()-1, 2,
                new QLabel(QString(capturedPacket
                                   ->getEthernetHeader()->getMacDestination())));
    ui->tableWidget->
            setCellWidget(
                ui->tableWidget->rowCount()-1, 3,
                new QLabel(QString(capturedPacket
                                   ->getIpHeader()->getProtocolName())));
    ui->tableWidget->
            setCellWidget(
                ui->tableWidget->rowCount()-1, 4,
                new QLabel(QString::number(capturedPacket
                                           ->getSizeOfPacket())));

    nrOfPacketsSniffed++;

    if((ui->checkBox->isChecked()) &&
            (nrOfPacketsSniffed == nrOfPacketsToSniff))
    {
        ui->start_button->setEnabled(true);
        ui->stop_button->setEnabled(false);
        ui->checkBox->setCheckable(true);
        ui->checkBox->setDisabled(false);
    }


}

void PacketSniffingWidget::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    PackageDetailsDialog pack(listOfCaptuedPackages.at(index.row()), this);
    pack.exec();
}
