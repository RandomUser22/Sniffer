#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    psw(new PacketSniffingWidget(this)),
    apiw(new AccessPointInformationWidget(this)),
    gaw(new GeneralAnalysisWidget(this))
{
    ui->setupUi(this);

    apiw->setVisible(false);
    psw->setVisible(false);
    gaw->setVisible(false);

    setupWindowDisplay();
}

MainWindow::~MainWindow()
{
    delete apiw;
    delete psw;
    delete gaw;
    delete ui;
}

void MainWindow::setupWindowDisplay()
{
    QVBoxLayout* vboxLayout = new QVBoxLayout();

    vboxLayout->addWidget(gaw);
    apiw->setVisible(false);
    psw->setVisible(false);
    gaw->setVisible(true);
    vboxLayout->setMargin(0);
    vboxLayout->setSpacing(0);

    ui->application_mode_widget->setLayout(vboxLayout);
}

void MainWindow::on_access_point_information_button_clicked()
{
    QLayout* vboxLayout = ui->application_mode_widget->layout();
    vboxLayout->removeWidget(psw);
    vboxLayout->removeWidget(gaw);
    vboxLayout->addWidget(apiw);
    apiw->setVisible(true);
    psw->setVisible(false);
    gaw->setVisible(false);
}

void MainWindow::on_packet_sniffing_button_clicked()
{
    QLayout* vboxLayout = ui->application_mode_widget->layout();
    vboxLayout->removeWidget(apiw);
    vboxLayout->removeWidget(gaw);
    vboxLayout->addWidget(psw);
    apiw->setVisible(false);
    psw->setVisible(true);
    gaw->setVisible(false);
}

void MainWindow::on_analysis_button_clicked()
{
    QLayout* vboxLayout = ui->application_mode_widget->layout();
    vboxLayout->removeWidget(apiw);
    vboxLayout->removeWidget(psw);
    vboxLayout->addWidget(gaw);
    apiw->setVisible(false);
    psw->setVisible(false);
    gaw->setVisible(true);
}
