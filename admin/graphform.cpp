#include "graphform.h"
#include "ui_graphform.h"

GraphForm::GraphForm(
        Network *network, qint16 clientId, QWidget *parent) :
    QWidget(parent),
    network_(network),
    clientId_(clientId),
    ui(new Ui::GraphForm)
{
    ui->setupUi(this);
   // network->sendLevelTwo(clientId, MOD_GRAPH, "test");

    network_->activateMode(clientId, MOD_GRAPH);
    connect(network_, SIGNAL(dataIncome()),
                this, SLOT(onDataReceived()));

    ui->graphicsView->setScene(&scene);
}

GraphForm::~GraphForm()
{
    network_->deactivateMode(clientId_, MOD_GRAPH);
    delete ui;
}

void GraphForm::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == MOD_GRAPH))
        return;
    qDebug() << "GraphForm::onDataReceived()";
    bytePicIn.clear();
    bytePicIn = network_->receivedData().data;
    picIn.loadFromData(bytePicIn);
    scene.clear();
    scene.addPixmap(picIn);
}
