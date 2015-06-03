#include "accesspointinformationwidget.h"
#include "ui_accesspointinformationwidget.h"

AccessPointInformationWidget::AccessPointInformationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccessPointInformationWidget),
    lf(LogicFacade::getInstance()),
    listOfNetworkInterfacess(),
    signalMapper(new QSignalMapper(this)),
    listOfColumnLabes()
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(4);
    listOfColumnLabes.append("Interface");
    listOfColumnLabes.append("Type");
    listOfColumnLabes.append("Connection state");
    listOfColumnLabes.append("Details");
    ui->tableWidget->setHorizontalHeaderLabels(listOfColumnLabes);
    ui->tableWidget->setStyleSheet("QTableWidget {background-color: transparent;}"
                                   "QHeaderView::section {background-color: transparent;}"
                                   "QHeaderView {background-color: transparent;}"
                                   "QTableCornerButton::section {background-color: transparent;}");
    ui->tableWidget->setFrameStyle(QFrame::NoFrame);

    ui->tableWidget->
            setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setWordWrap(true);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    populateTopTable();
    populateBottomTabWidget();

    this->setVisible(true);
}

AccessPointInformationWidget::~AccessPointInformationWidget()
{
    delete ui;
}

void AccessPointInformationWidget::populateTopTable()
{
    try
    {
        QList<NetworkInterfacePtr> listOfInterfacess =
                lf->getListOfNetworkInterfacess();
        for(uint8_t i = 0; i < listOfInterfacess.size(); i++)
        {
            if(listOfInterfacess.at(i)->getAdapterType()
                    == entity::adapter_type_ieee80211)
            {
                qDebug("here0");
                qDebug("-%s", listOfInterfacess.at(i)->getDescription().toStdString().c_str());
                WlanInterfacePtr temp = lf->getDetailedAccessPointInformation(listOfInterfacess.at(i));
                if(temp)
                {
                    listOfNetworkInterfacess.push_back(temp);
                    qDebug("here4");
                }
            }
        }
        ui->tableWidget->setRowCount(listOfNetworkInterfacess.size());

        // each interface will have more details than those shown in this screen
        QPushButton* detailsButton;

        for(uint8_t i = 0; i < listOfNetworkInterfacess.size(); i++)
        {

            // set the label in first cell of the row
            ui->tableWidget->setItem(i, 0,
                                     new QTableWidgetItem(tr("%1").
                                                          arg(listOfNetworkInterfacess.at(i)
                                                              ->getDescription())));

            ui->tableWidget->setItem(i, 1,
                                     new QTableWidgetItem(tr("%1").
                                                          arg(listOfNetworkInterfacess.at(i)
                                                              ->getAdapterTypeName())));
            ui->tableWidget->setItem(i, 2,
                                     new QTableWidgetItem(tr("%1").
                                                          arg(listOfNetworkInterfacess.at(i)
                                                              ->getConnectionTypeName())));

            // set the 'details' buttons
            detailsButton = new QPushButton("Details", this);
            connect(detailsButton,SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(detailsButton, i);

            ui->tableWidget->setCellWidget(i, 3, detailsButton);
        }


        connect(signalMapper, SIGNAL(mapped(int)),
                this, SLOT(onDetailsButtonClicked(int)));
    }
    catch(PcapException& e)
    {
        QMessageBox::warning(this,tr("Pcap exception"),tr(e.what()));
        QApplication::postEvent( this, new QCloseEvent() );
    }
}

void AccessPointInformationWidget::populateBottomTabWidget()
{
    // add a tab for each WiFi interface
    for(int i = 0; i< listOfNetworkInterfacess.size(); i++)
    {
        qDebug("Here 5");
        QString idWlan = listOfNetworkInterfacess.at(i)->getDescription();

        QTableView *listOfConnections = new QTableView(ui->tabWidget);
        listOfConnections->horizontalHeader()
                ->setSectionResizeMode(QHeaderView::ResizeToContents);
        listOfConnections->
                setSelectionBehavior(QAbstractItemView::SelectRows);
        listOfConnections->setWordWrap(true);
        listOfConnections->setModel(listOfNetworkInterfacess.at(i)->getConnctionsList().get());

        ui->tabWidget->addTab(listOfConnections, idWlan);
    }
}

void AccessPointInformationWidget::onDetailsButtonClicked(int index)
{
    InterfaceDetailsDialog id(listOfNetworkInterfacess.at(index), this);
    id.exec();
}

