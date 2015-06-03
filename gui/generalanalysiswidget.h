#ifndef GENERALANALYSISWIDGET_H
#define GENERALANALYSISWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QVector>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QAtomicInt>
#include <QTimer>

#include "networkinterface.h"
#include "selectinterfacedialog.h"
#include "logicfacade.h"

namespace Ui {
class GeneralAnalysisWidget;
}

class GeneralAnalysisWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralAnalysisWidget(QWidget *parent = 0);
    ~GeneralAnalysisWidget();

private slots:
    void on_select_interface_button_clicked();
    void onInterfaceSelected(NetworkInterfacePtr inter);
    void on_comboBox_activated(int index);
    void on_start_button_clicked();
    void on_stop_button_clicked();
    void onPackageSniffed(PacketPtr capturedPacket);
    void update();

private:
    void drawPlot(int index);

    Ui::GeneralAnalysisWidget *ui;
    NetworkInterfacePtr interfaceToAnalyze;
    WlanInterfacePtr wlanIterfaceToAnalyze;
    LogicFacadePtr logicFacade;
    QVector<double> x;
    QVector<double> y;
    QAtomicInt nrOfPacketsSniffed;
    QTimer *timer;
};

#endif // GENERALANALYSISWIDGET_H
