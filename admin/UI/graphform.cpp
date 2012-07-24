#include "graphform.h"
#include "ui_graphform.h"
#include <QKeyEvent>

using namespace delta3;

GraphForm::GraphForm(
		delta3::Network *network, qint16 clientId, QWidget *parent) :
    QWidget(parent),
    network_(network),
    clientId_(clientId),
    ui(new Ui::GraphForm)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Graph - ") + network_->getClientName(clientId_));
   // network->sendLevelTwo(clientId, MOD_GRAPH, "test");

	network_->activateMode(clientId, MOD_GRAPHICS);
    connect(network_, SIGNAL(dataIncome()),
                this, SLOT(onDataReceived()));

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->installEventFilter(this);
}

GraphForm::~GraphForm()
{
	network_->deactivateMode(clientId_, MOD_GRAPHICS);
    delete ui;
}

bool GraphForm::eventFilter(QObject *_o, QEvent *_e)
{
    if(_e->type() == QEvent::KeyPress){
        QKeyEvent* pKeyEvent = static_cast<QKeyEvent*>(_e);
        qDebug() << pKeyEvent->key();
        QByteArray buf;
        buf.append(GMOD_KEYPRESSED);
        buf.append((quint8)pKeyEvent->key());
		network_->sendLevelTwo(clientId_, MOD_GRAPHICS,
                                           buf);
        return true;
    }
    return false;
}

void GraphForm::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
			network_->receivedData().mode == MOD_GRAPHICS))
        return;
    qDebug() << "GraphForm::onDataReceived()";
    bytePicIn.clear();
    bytePicIn = network_->receivedData().data;
    picIn.loadFromData(bytePicIn);
    scene.clear();
    scene.addPixmap(picIn);
}
