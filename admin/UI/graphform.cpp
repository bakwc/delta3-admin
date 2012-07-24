#include "graphform.h"
#include "ui_graphform.h"
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>

namespace delta3{

GraphForm::GraphForm(Graphics *graph, QWidget *parent) :
    QWidget(parent),
	graph_(graph),
    ui(new Ui::GraphForm)
{
    ui->setupUi(this);
	this->setWindowTitle(tr("Graph - "));// + network_->getClientName(clientId_));
   // network->sendLevelTwo(clientId, MOD_GRAPH, "test");

	connect(graph_, SIGNAL(ready(QImage&)), SLOT(onDataReceived(QImage&)));
    connect(this, SIGNAL(ready(QByteArray&)), graph_, SLOT(onReady(QByteArray&)));
    this->setMouseTracking(true);
    this->installEventFilter(this);
}

GraphForm::~GraphForm()
{
    delete ui;
}

void GraphForm::mouseMoveEvent(QMouseEvent * me){
    qDebug() << "MOUSE move" << me->x() << me->y();
    QByteArray buf;
    buf.append(GMOD_MMOV);
    buf.append(toBytes((quint16)me->x()));
    buf.append(toBytes((quint16)me->y()));
    emit ready(buf);
}

void GraphForm::mouseReleaseEvent(QMouseEvent * me){
    qDebug() << "MOUSE release" << me->x() << me->y();
    QByteArray buf;
    buf.append(GMOD_MCLICK);
    buf.append(toBytes((quint16)me->x()));
    buf.append(toBytes((quint16)me->y()));
    buf.append((quint8)(me->button() + 20));
    emit ready(buf);
}

void GraphForm::mousePressEvent(QMouseEvent *me){
    qDebug() << "MOUSE press" << me->x() << me->y();
    QByteArray buf;
    buf.append(GMOD_MCLICK);
    buf.append(toBytes((quint16)me->x()));
    buf.append(toBytes((quint16)me->y()));
    buf.append((quint8)me->button());
    emit ready(buf);
}

void GraphForm::keyPressEvent(QKeyEvent * pKeyEvent){
    qDebug() << pKeyEvent->key();
    QByteArray buf;
    buf.append(GMOD_KEYEV);
    buf.append((quint8)pKeyEvent->key());
    emit ready(buf);
}

void GraphForm::onDataReceived(QImage &img)
{
	image_ = img;
	repaint();
}

void GraphForm::paintEvent(QPaintEvent *)
{
	QPainter p(this);

	p.drawImage(0, 0, image_);
}
}
