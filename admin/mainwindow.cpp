#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    network_ = new Network(this);
    connect(network_,SIGNAL(listUpdated()),
            this,SLOT(onRedraw()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_activated()
{
    network_->connectToServer();
}

void MainWindow::onRedraw()
{
    qDebug() << "onRedraw()";
    QListWidget *list=ui->listWidget;
    QListWidgetItem *item;
    list->clear();
    for(auto i  = network_->getClients().begin();
             i != network_->getClients().end(); i++)
    {
        item = new QListWidgetItem(i.value()->getHash() );
        item->setWhatsThis(QString("%1")
                        .arg( i.value()->getId() ));
        list->addItem(item);
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

    //TODO: menu with select connection mode

    TelnetForm *telnet = new TelnetForm(
                network_,
                item->whatsThis().toInt());
            // REVIEW: potential memory leak?

    telnet->show();
}
