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
    network_->connect();
}

void MainWindow::onRedraw()
{
    for(auto i=network_->getClients().begin(),
             i!=network_->getClients().end(), i++)
    {
    }
}
