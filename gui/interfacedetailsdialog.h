#ifndef INTERFACEDETAILSDIALOG_H
#define INTERFACEDETAILSDIALOG_H

// includes from QT
#include <QDialog>

// includes from project
#include "networkinterface.h"

namespace Ui {
class InterfaceDetailsDialog;
}

class InterfaceDetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InterfaceDetailsDialog(
            NetworkInterfacePtr interfaceToSniff,
            QWidget *parent = 0);
    ~InterfaceDetailsDialog();

private slots:
    void on_close_button_clicked();

private:

    Ui::InterfaceDetailsDialog *ui;
    NetworkInterfacePtr sniffingInterface;

};

#endif // INTERFACEDETAILSDIALOG_H
