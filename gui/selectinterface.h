#ifndef SELECTINTERFACE_H
#define SELECTINTERFACE_H

#include <QDialog>
#include "interfacelist.h"

namespace Ui {
class SelectInterface;
}

class SelectInterface : public QDialog
{
    Q_OBJECT

public:
    explicit SelectInterface(QWidget *parent = 0);
    ~SelectInterface();

private slots:
    void on_buttonBox_accepted();

    void on_list_clicked();

    void onDeviceSelected(QString device);

signals:
    void interfaceSelect(QString inter);

private:
    Ui::SelectInterface *ui;

    QString inter;
};

#endif // SELECTINTERFACE_H
