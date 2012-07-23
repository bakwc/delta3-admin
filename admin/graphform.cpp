#include "graphform.h"
#include "ui_graphform.h"
#include <QKeyEvent>
#include <QMouseEvent>
GraphForm::GraphForm(
        Network *network, qint16 clientId, QWidget *parent) :
    QWidget(parent),
    network_(network),
    clientId_(clientId),
    ui(new Ui::GraphForm)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Graph - ") + network_->getClientName(clientId_));
   // network->sendLevelTwo(clientId, MOD_GRAPH, "test");

    network_->activateMode(clientId, MOD_GRAPH);
    connect(network_, SIGNAL(dataIncome()),
                this, SLOT(onDataReceived()));
    setMouseTracking(true);
    ui->label->installEventFilter(this);
}

GraphForm::~GraphForm()
{
    network_->deactivateMode(clientId_, MOD_GRAPH);
    delete ui;
}

void GraphForm::mouseMoveEvent(QMouseEvent * me){
    qDebug() << "MOUSE release" << me->x() << me->y();
    QByteArray buf;
    buf.append(GMOD_MCLICK);
    buf.append((quint8)(me->button() + 20));
    buf.append(toBytes((quint16)(me->x() - 10)));
    buf.append(toBytes((quint16)(me->y() - 10)));
    network_->sendLevelTwo(clientId_, MOD_GRAPH,
                                       buf);
}

void GraphForm::mouseDoubleClickEvent(QMouseEvent *){

}

void GraphForm::mousePressEvent(QMouseEvent *me){
    qDebug() << "MOUSE press" << me->x() << me->y();
    QByteArray buf;
    buf.append(GMOD_MCLICK);
    buf.append((quint8)me->button());
    buf.append(toBytes((quint16)(me->x() - 10)));
    buf.append(toBytes((quint16)(me->y() - 10)));
    network_->sendLevelTwo(clientId_, MOD_GRAPH,
                                       buf);
}

void GraphForm::keyPressEvent(QKeyEvent * pKeyEvent){
    qDebug() << pKeyEvent->key();
    QByteArray buf;
    buf.append(GMOD_KEYEV);
    buf.append((quint8)pKeyEvent->key());
    network_->sendLevelTwo(clientId_, MOD_GRAPH,
                                       buf);
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
    QSize size = QSize(picIn.size().width()/2,picIn.size().height()/2);
    ui->label->resize(size);
    ui->label->setPixmap(picIn.scaled(ui->label->size(),
                                                    Qt::KeepAspectRatio,
                                                    Qt::SmoothTransformation));
}
