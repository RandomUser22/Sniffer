#ifndef PACKETSNIFFINGWIDGET_H
#define PACKETSNIFFINGWIDGET_H

// includes from standart library
#include <cstdint>

// includes from QT
#include <QWidget>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

// includes from current sub-project
#include "selectinterfacedialog.h"
#include "networkinterface.h"
#include "packagedetailsdialog.h"
#include "logicfacade.h"

namespace Ui {
class PacketSniffingWidget;
}

class PacketSniffingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PacketSniffingWidget(QWidget *parent = 0);
    ~PacketSniffingWidget();

private slots:
    void on_checkBox_toggled(bool checked);
    void on_select_interface_button_clicked();
    void onInterfaceSelected(NetworkInterfacePtr inter);
    void on_start_button_clicked();
    void on_stop_button_clicked();
    void onPackageSniffed(PacketPtr capturedPacket);
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    void setupWidgetDisplay();

    Ui::PacketSniffingWidget *ui;

    NetworkInterfacePtr interfaceToSniff;
    LogicFacadePtr logicFacade;
    uint16_t nrOfPacketsToSniff;
    uint16_t nrOfPacketsSniffed;
    QList<PacketPtr> listOfCaptuedPackages;
};

#endif // PACKETSNIFFINGWIDGET_H
