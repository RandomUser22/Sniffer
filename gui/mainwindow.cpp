#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    snifferManager = SnifferManager::getInstance();
    connect(snifferManager, SIGNAL(packageCaptured(QStringList)),
            this, SLOT(onPackageCaptured(QStringList)));

    ui->tableWidget->setColumnCount(3);
}

MainWindow::~MainWindow()
{
    SnifferManager::removeInstance();
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
}

void MainWindow::on_actionOpen_triggered()
{
}

void MainWindow::on_actionAbout_triggered()
{
}

void MainWindow::on_select_interface_clicked()
{
    SelectInterface s(this);
    connect(&s, SIGNAL(interfaceSelect(QString)), this, SLOT(onInterfaceSelected(QString)));
    s.exec();
}

void MainWindow::on_start_sniff_clicked()
{
    snifferManager->setInterfaceToSniffOn(this->inter);
    snifferManager->startSniffing();
}

void MainWindow::onInterfaceSelected(QString inter)
{
    this->inter = inter;
    ui->interface_label->setText(this->inter);
}

void MainWindow::onPackageCaptured(QStringList payload)
{
    ui->lcdNumber->display(payload.at(0).toDouble());

    int lastRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(lastRow);

    ui->tableWidget->setItem(lastRow, 0, new QTableWidgetItem(payload.at(0)));
    ui->tableWidget->setItem(lastRow, 1, new QTableWidgetItem(payload.at(1)));
    ui->tableWidget->setItem(lastRow, 2, new QTableWidgetItem(payload.at(2)));

}
