#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gui_global.h"

#include <QMainWindow>
#include <QCloseEvent>
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

    void onInterfaceSelected(SniffingInterfacePtr inter);

    void onPackageCaptured(unsigned int pckCount,
                           PacketPtr payload);

    void on_start_sniff_released();

private:
    void initializeUi();

    void closeEvent(QCloseEvent *bar);

    Ui::MainWindow *ui;

    SniffingInterfacePtr inter;

    SnifferManagerPtr snifferManager;
};

#endif // MAINWINDOW_H
