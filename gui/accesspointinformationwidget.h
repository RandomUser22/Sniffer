#ifndef ACCESSPOINTINFORMATIONWIDGET_H
#define ACCESSPOINTINFORMATIONWIDGET_H

// includes from QT
#include <QDialog>
#include <QMessageBox>
#include <QSignalMapper>
#include <QPushButton>
#include <QApplication>
#include <QCloseEvent>

// includes from systems
#include "logicfacade.h"
#include "interfacedetailsdialog.h"
#include "wlaninterface.h"

namespace Ui {
class AccessPointInformationWidget;
}

class AccessPointInformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AccessPointInformationWidget(QWidget *parent = 0);
    ~AccessPointInformationWidget();

private slots:
    void onDetailsButtonClicked(int index);


signals:
    void interfaceSelected(NetworkInterfacePtr inter);

private:
    void populateTopTable();
    void populateBottomTabWidget();

    Ui::AccessPointInformationWidget *ui;
    LogicFacadePtr lf;
    QList<WlanInterfacePtr> listOfNetworkInterfacess;
    QSignalMapper *signalMapper;
    QStringList listOfColumnLabes;
};

#endif // ACCESSPOINTINFORMATIONWIDGET_H
