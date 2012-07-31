#include "graphform.h"
#include "ui_graphform.h"
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>

using namespace delta3;

GraphForm::GraphForm(Graphics *graph, QWidget *parent) :
    QWidget(parent),
	graph_(graph),
    ui(new Ui::GraphForm)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Graphics - ") + graph_->getClientCaption());

    connect(graph_, SIGNAL(ready(QImage&)), SLOT(onDataReceived(QImage&)));
    connect(this, SIGNAL(keyPress(int)), graph_, SLOT(onKey(int)));
    connect(this, SIGNAL(mMove(qint16,qint16)), graph_, SLOT(onMove(qint16,qint16)));
    connect(this, SIGNAL(mClick(qint16,qint16,delta3::GMCLICK)),
            graph_, SLOT(onClick(qint16,qint16,delta3::GMCLICK)));

	setAttribute(Qt::WA_DeleteOnClose);
}


GraphForm::~GraphForm()
{
    delete ui;
}


bool GraphForm::eventFilter(QObject *_o, QEvent *_e)
{
    qDebug() << Q_FUNC_INFO;

    if(_e->type() == QEvent::KeyPress){
        QKeyEvent* pKeyEvent = static_cast<QKeyEvent*>(_e);

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

//    if(x > delta3::MOUSE_ACCURACY)
//        x = delta3::MOUSE_ACCURACY;
//    else if(x < 0)
//        x = 0;

//    if(y > delta3::MOUSE_ACCURACY)
//        y = delta3::MOUSE_ACCURACY;
//    else if(y < 0)
//        y = 0;

    //emit mMove(x, y);
    ev->accept();

    //qDebug() << "    " << Q_FUNC_INFO;
}


void GraphForm::mousePressEvent(QMouseEvent *ev)
{

    ev->accept();

    //qDebug() << "    " << Q_FUNC_INFO;
}


void GraphForm::mouseReleaseEvent(QMouseEvent *ev)
{
    qint16 x = getClientMousePosX(ev->x());
    qint16 y = getClientMousePosY(ev->y());

    emit mClick(x, y,
                (delta3::GMCLICK)(delta3::GMCLICK_LEFT | delta3::GMCLICK_CLICK));

    ev->accept();

    qDebug() << Q_FUNC_INFO << x << y << ev->x() << ev->y() << graph_->clientWidth() << graph_->clientHeight();
}

void GraphForm::mouseDoubleClickEvent(QMouseEvent *ev)
{
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


void GraphForm::paintEvent(QPaintEvent *)
{
	QPainter p(this);

	p.drawImage(0, 0, image_);
}
