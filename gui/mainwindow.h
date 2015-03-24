#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gui_global.h"

#include <QMainWindow>
#include <QtDebug>

#include "selectinterface.h"

namespace Ui {
class GUISHARED_EXPORT MainWindow;
}

class GUISHARED_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionAbout_triggered();

    void on_select_interface_clicked();

    void on_start_sniff_clicked();

    void onInterfaceSelected(QString inter);

    void onPackageCaptured(QStringList payload);

private:
    Ui::MainWindow *ui;

    QString inter;

    SnifferManager *snifferManager;
};

#endif // MAINWINDOW_H
