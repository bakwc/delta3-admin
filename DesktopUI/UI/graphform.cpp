#include "graphform.h"
#include "ui_graphform.h"
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>

using namespace delta3;

GraphForm::GraphForm(Graphics *graph, QWidget *parent) :
    QWidget(parent), graph_(graph), ui(new Ui::GraphForm), pressButtons_(0)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Graphics - ") + graph_->getClientCaption());

    connect(graph_, SIGNAL(imageReady(QImage&)), SLOT(onDataReceived(QImage&)));
    connect(graph_, SIGNAL(ready(int,int)), this, SLOT(onReady(int,int)));

    setAttribute(Qt::WA_DeleteOnClose);
}


GraphForm::~GraphForm()
{
    delete ui;
}


bool GraphForm::eventFilter(QObject *obj, QEvent *ev)
{
    qDebug() << Q_FUNC_INFO;

    if (ev->type() == QEvent::KeyPress){
        QKeyEvent* pKeyEvent = static_cast<QKeyEvent*>(ev);

        qDebug() << Q_FUNC_INFO << "KEY: " << pKeyEvent->key();

        emit keyPress(pKeyEvent->key());

        return true;
    }
    return false;
}


void GraphForm::mouseMoveEvent(QMouseEvent *ev)
{
    qint16 x = getClientMousePosX(ev->x());
    qint16 y = getClientMousePosY(ev->y());

    //emit mMove(x, y);

    ev->accept();

    //qDebug() << "    " << Q_FUNC_INFO;
}


void GraphForm::mousePressEvent(QMouseEvent *ev)
{
    qint16 x = getClientMousePosX(ev->x());
    qint16 y = getClientMousePosY(ev->y());
    
    pressButtons_ = ev->buttons();
    pressButtons_ |= delta3::GMCLICK_DOWN;

    emit mClick(x, y, (delta3::GMCLICK)pressButtons_);

    ev->accept();

    //qDebug() << "    " << Q_FUNC_INFO;
}


void GraphForm::mouseReleaseEvent(QMouseEvent *ev)
{
    qint16 x = getClientMousePosX(ev->x());
    qint16 y = getClientMousePosY(ev->y());

    pressButtons_ = ev->buttons();
    pressButtons_ |= delta3::GMCLICK_UP;

    emit mClick(x, y, (delta3::GMCLICK)pressButtons_);

    ev->accept();
}

void GraphForm::mouseDoubleClickEvent(QMouseEvent *ev)
{
    qint16 x = getClientMousePosX(ev->x());
    qint16 y = getClientMousePosY(ev->y());

    pressButtons_ = ev->buttons();
    pressButtons_ |= delta3::GMCLICK_DCLICK;

    emit mClick(x, y, (delta3::GMCLICK)pressButtons_);

    ev->accept();
}


void GraphForm::keyPressEvent(QKeyEvent *ev)
{
    emit keyPress(ev->key());
    ev->accept();
}

void GraphForm::onDataReceived(QImage &img)
{
	image_ = img;
    repaint();
}

void GraphForm::onReady(int clW, int clH)
{
    resize(clW, clH);

    connect(this, SIGNAL(keyPress(int)), graph_, SLOT(onKey(int)));
    connect(this, SIGNAL(mMove(qint16,qint16)), graph_, SLOT(onMove(qint16,qint16)));
    connect(this, SIGNAL(mClick(qint16,qint16,delta3::GMCLICK)),
            graph_, SLOT(onClick(qint16,qint16,delta3::GMCLICK)));
}


void GraphForm::paintEvent(QPaintEvent *ev)
{
	QPainter p(this);

    p.drawImage(0, 0, image_);

    ev->accept();
}
