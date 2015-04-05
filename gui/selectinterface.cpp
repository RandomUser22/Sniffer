#include "selectinterface.h"
#include "ui_selectinterface.h"

SelectInterface::SelectInterface(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectInterface),
    inter()
{
    ui->setupUi(this);

    qRegisterMetaType<SniffingInterfacePtr>("SniffingInterfacePtr");
}

SelectInterface::~SelectInterface()
{
    delete ui;
}

void SelectInterface::on_buttonBox_accepted()
{
    emit interfaceSelect(inter);
}

void SelectInterface::on_list_clicked()
{
    InterfaceList l(this);
    connect(&l, SIGNAL(deviceSelected(SniffingInterfacePtr)), this, SLOT(onDeviceSelected(SniffingInterfacePtr)));
    l.exec();
}

void SelectInterface::onDeviceSelected(SniffingInterfacePtr device)
{
    inter = device;
    ui->lineEdit->setText(device->getDescription());
}
