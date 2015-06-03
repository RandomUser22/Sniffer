#include "selectinterfacedialog.h"
#include "ui_selectinterfacedialog.h"

SelectInterfaceDialog::SelectInterfaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectInterfaceDialog),
    lf(LogicFacade::getInstance()),
    listOfNetworkInterfacess(),
    signalMapper(new QSignalMapper(this)),
    listOfColumnLabes()
{
    ui->setupUi(this);
    this->setVisible(false);

    ui->tableWidget->setColumnCount(3);
    listOfColumnLabes.append("Interface");
    listOfColumnLabes.append("Type");
    listOfColumnLabes.append("Details");
    ui->tableWidget->setHorizontalHeaderLabels(listOfColumnLabes);

    ui->tableWidget->
            setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setWordWrap(true);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()
            ->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    populateTable();

    this->setVisible(true);
}

SelectInterfaceDialog::~SelectInterfaceDialog()
{
    delete ui;
    delete signalMapper;
}

void SelectInterfaceDialog::populateTable()
{
    try
    {
        listOfNetworkInterfacess = lf->getListOfNetworkInterfacess();
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

            // set the 'details' buttons
            detailsButton = new QPushButton("Details", this);
            connect(detailsButton,SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(detailsButton, i);

            ui->tableWidget->setCellWidget(i, 2, detailsButton);
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

void SelectInterfaceDialog::onDetailsButtonClicked(int index)
{
    InterfaceDetailsDialog id(listOfNetworkInterfacess.at(index), this);
    id.exec();
}

void SelectInterfaceDialog::on_buttonBox_accepted()
{
    int selectedIndex = ui->tableWidget->currentRow();
    emit interfaceSelected(listOfNetworkInterfacess.at(selectedIndex));
}
