#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// includes from QT
#include <QMainWindow>

// includes from current project
#include "gui_global.h"
#include "packetsniffingwidget.h"
#include "accesspointinformationwidget.h"
#include "generalanalysiswidget.h"

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
    void on_access_point_information_button_clicked();

    void on_packet_sniffing_button_clicked();

    void on_analysis_button_clicked();

private:
    void setupWindowDisplay();

    Ui::MainWindow *ui;
    PacketSniffingWidget* psw;
    AccessPointInformationWidget* apiw;
    GeneralAnalysisWidget* gaw;
};

#endif // MAINWINDOW_H
