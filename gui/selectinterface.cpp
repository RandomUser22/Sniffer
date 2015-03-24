#include "selectinterface.h"
#include "ui_selectinterface.h"

SelectInterface::SelectInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectInterface),
    inter("")
{
    ui->setupUi(this);
}

SelectInterface::~SelectInterface()
{
    delete ui;
}

void SelectInterface::on_buttonBox_accepted()
{
    inter = ui->lineEdit->text();
    emit interfaceSelect(inter);
}

void SelectInterface::on_list_clicked()
{
    InterfaceList l(this);
    connect(&l, SIGNAL(deviceSelected(QString)), this, SLOT(onDeviceSelected(QString)));
    l.exec();
}

void SelectInterface::onDeviceSelected(QString device)
{
    ui->lineEdit->setText(device);
}
