#ifndef PACKAGEDETAILSDIALOG_H
#define PACKAGEDETAILSDIALOG_H

// includes from QT
#include <QDialog>

// includes from project
#include "packet.h"

namespace Ui {
class PackageDetailsDialog;
}

class PackageDetailsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PackageDetailsDialog(PacketPtr input, QWidget *parent = 0);
    ~PackageDetailsDialog();

private slots:
    void on_close_button_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::PackageDetailsDialog *ui;
    PacketPtr packetDisplayed;
};

#endif // PACKAGEDETAILSDIALOG_H
