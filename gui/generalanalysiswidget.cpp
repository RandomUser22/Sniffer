#include "generalanalysiswidget.h"
#include "ui_generalanalysiswidget.h"

int z = 0;

GeneralAnalysisWidget::GeneralAnalysisWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralAnalysisWidget),
    logicFacade(LogicFacade::getInstance()),
    x(),
    y(),
    nrOfPacketsSniffed(0),
    timer(new QTimer(this))
{
    ui->setupUi(this);

    qRegisterMetaType<PacketPtr>("PacketPtr");
    connect(logicFacade.get(), SIGNAL(packageSniffed(PacketPtr)),
            this, SLOT(onPackageSniffed(PacketPtr)));

    ui->comboBox->addItem("Signal Strenght/time");
    ui->comboBox->addItem("Packets sniffed/time");
    ui->comboBox->addItem("TCP Packets sniffed/time");
    ui->comboBox->setEnabled(true);

    ui->stop_button->setEnabled(false);
    ui->start_button->setEnabled(false);

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    drawPlot(0);
}

GeneralAnalysisWidget::~GeneralAnalysisWidget()
{
    delete ui;
}

void GeneralAnalysisWidget::on_select_interface_button_clicked()
{
    SelectInterfaceDialog s(this);
    connect(&s, SIGNAL(interfaceSelected(NetworkInterfacePtr)),
            this, SLOT(onInterfaceSelected(NetworkInterfacePtr)));
    s.exec();
}

void GeneralAnalysisWidget::onInterfaceSelected(NetworkInterfacePtr inter)
{
    interfaceToAnalyze = inter;
    if(interfaceToAnalyze->getAdapterType() == entity::adapter_type_ieee80211)
    {
//        wlanIterfaceToAnalyze = inter;
    }
    ui->interface_label->setText(interfaceToAnalyze->getDescription());
    ui->start_button->setEnabled(true);
}

void GeneralAnalysisWidget::on_comboBox_activated(int index)
{

}

void GeneralAnalysisWidget::drawPlot(int index)
{
    switch (index) {
    case 0:
    case 1:
    case 2:
    {
        ui->plot_widget->addGraph(); // blue line
        ui->plot_widget->graph(0)->setPen(QPen(Qt::blue));
        ui->plot_widget->graph(0)->setAntialiasedFill(false);

        ui->plot_widget->addGraph(); // blue dot
        ui->plot_widget->graph(1)->setPen(QPen(Qt::blue));
        ui->plot_widget->graph(1)->setLineStyle(QCPGraph::lsNone);
        ui->plot_widget->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

        ui->plot_widget->xAxis->setTickLabelType(QCPAxis::ltDateTime);
        ui->plot_widget->xAxis->setDateTimeFormat("hh:mm:ss");
        ui->plot_widget->xAxis->setAutoTickStep(false);
        ui->plot_widget->xAxis->setTickStep(2);
        ui->plot_widget->axisRect()->setupFullAxesBox();

        // make left and bottom axes transfer their ranges to right and top axes:
        connect(ui->plot_widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_widget->xAxis2, SLOT(setRange(QCPRange)));
        connect(ui->plot_widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot_widget->yAxis2, SLOT(setRange(QCPRange)));

    }
        break;
    default:
        break;
    }
}

void GeneralAnalysisWidget::on_start_button_clicked()
{
    ui->stop_button->setEnabled(true);
    ui->start_button->setEnabled(false);
    ui->comboBox->setEnabled(false);

    QFuture<void> future;
    future = QtConcurrent::run(logicFacade.get(),
                               &LogicFacade::startSniffing, interfaceToAnalyze, 0);
    switch ((ui->comboBox->currentIndex())) {
    case 0:
//        future = QtConcurrent::run(logicFacade.get(),
//                                   &LogicFacade::getSignalStrenght, interfaceToAnalyze);
        break;
    case 1:
        // to be modified


        break;
    case 2:

        break;
    default:
        break;
    }

    timer->start(100);
}

void GeneralAnalysisWidget::on_stop_button_clicked()
{
    ui->stop_button->setEnabled(false);
    ui->start_button->setEnabled(true);
    ui->comboBox->setEditable(true);

    logicFacade->stopSniffing();
    nrOfPacketsSniffed = 0;

    timer->stop();
}

void GeneralAnalysisWidget::onPackageSniffed(PacketPtr capturedPacket)
{
    nrOfPacketsSniffed++;
}

void GeneralAnalysisWidget::update()
{
    ui->bottom_label->setText(QString("Sniffed %1 packets").arg(QString::number(nrOfPacketsSniffed)));
    // create graph and assign data to it:

    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
        double value0 = nrOfPacketsSniffed; //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
        // add data to lines:
        ui->plot_widget->graph(0)->addData(key, value0);
        // set data of dots:
        ui->plot_widget->graph(1)->clearData();
        ui->plot_widget->graph(1)->addData(key, value0);
        // remove data of lines that's outside visible range:
        ui->plot_widget->graph(0)->removeDataBefore(key-8);
        // rescale value (vertical) axis to fit the current data:
        ui->plot_widget->graph(0)->rescaleValueAxis();
        lastPointKey = key;
        nrOfPacketsSniffed = 0;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->plot_widget->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->plot_widget->replot();

    //    x.push_back(z);
    //    z++;
    //    y.push_back(nrOfPacketsSniffed);
    //    qDebug("x size: %d", x.size());
    //    qDebug("y size: %d", y.size());
    //    nrOfPacketsSniffed = 0;

    //    ui->plot_widget->clearGraphs();
    //    ui->plot_widget->addGraph();
    //    ui->plot_widget->graph()->setData(x, y);
    //    ui->plot_widget->replot();
}
