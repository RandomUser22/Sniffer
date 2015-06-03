#ifndef SELECTINTERFACEDIALOG_H
#define SELECTINTERFACEDIALOG_H

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

namespace Ui {
class SelectInterfaceDialog;
}

class SelectInterfaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectInterfaceDialog(QWidget *parent = 0);
    ~SelectInterfaceDialog();

private slots:
    void onDetailsButtonClicked(int index);
    void on_buttonBox_accepted();

signals:
    void interfaceSelected(NetworkInterfacePtr inter);

private:
    void populateTable();

    Ui::SelectInterfaceDialog *ui;
    LogicFacadePtr lf;
    QList<NetworkInterfacePtr> listOfNetworkInterfacess;
    QSignalMapper *signalMapper;
    QStringList listOfColumnLabes;
};

#endif // SELECTINTERFACEDIALOG_H
