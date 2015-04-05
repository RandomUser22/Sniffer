#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    inter(),
    snifferManager(SnifferManager::getInstance())
{
    // set the UI of the application
    ui->setupUi(this);
    initializeUi();

    // register the packet class so it can be used in the signal-slot mechanism
    qRegisterMetaType<PacketPtr>("PacketPtr");
    qRegisterMetaType<SniffingInterfacePtr>("SniffingInterfacePtr");

    // connect the signal for when receiving a packet
    connect(snifferManager.get(),
            SIGNAL(packageCaptured(unsigned int, PacketPtr)),
            this,
            SLOT(onPackageCaptured(unsigned int, PacketPtr)));
}

MainWindow::~MainWindow()
{
    SnifferManager::removeInstance();
    delete ui;
}

void MainWindow::initializeUi()
{
    // set the title of the main window
    this->setWindowTitle(QString::fromUtf8("Tomato"));

    // set the number of columns
    ui->tableWidget->setColumnCount(3);

    // set the label for each column
    ui->tableWidget->setHorizontalHeaderLabels(QString("ID;Size;Data").split(";"));

    // stretch the table over the full view
    ui->tableWidget->horizontalHeader()->
            setSectionResizeMode(QHeaderView::Stretch);

    // hide the vertical header
    ui->tableWidget->verticalHeader()->hide();

    // user can only select the rows
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // user cannot edit any cell
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // word wrap the text
    ui->tableWidget->setWordWrap(true);
}

void MainWindow::on_actionNew_triggered(){

}

void MainWindow::on_actionOpen_triggered(){

}

void MainWindow::on_actionAbout_triggered(){
}

void MainWindow::on_select_interface_clicked()
{
    SelectInterface s(this);
    connect(&s, SIGNAL(interfaceSelect(SniffingInterfacePtr)), this, SLOT(onInterfaceSelected(SniffingInterfacePtr)));
    s.exec();
}

void MainWindow::on_start_sniff_clicked()
{
    snifferManager->setInterfaceToSniffOn(this->inter->getPcapName());
    snifferManager->startSniffing();
}

void MainWindow::onInterfaceSelected(SniffingInterfacePtr inter)
{
    this->inter = inter;
    ui->interface_label->setText(this->inter->getDescription());
}

void MainWindow::onPackageCaptured(unsigned int pckCount,
                                   PacketPtr payload)
{
    ui->lcdNumber->display((int)pckCount);

    int lastRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(lastRow);

    ui->tableWidget->setItem(lastRow, 0, new QTableWidgetItem(QString::number(pckCount)));
    ui->tableWidget->setItem(lastRow, 1, new QTableWidgetItem(QString::number(payload->getSizeOfPacket())));
    ui->tableWidget->setItem(lastRow, 2, new QTableWidgetItem(QString((payload->getData()).toHex())));
}

void MainWindow::on_start_sniff_released(){
}

void MainWindow::closeEvent(QCloseEvent *bar)
{
    // prepare for closing
    SnifferManager::removeInstance();

    bar->accept();

}
