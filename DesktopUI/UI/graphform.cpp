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

    connect(graph_, SIGNAL(imageReady(QImage&)), SLOT(onDataReceived(QImage&)));
    connect(this, SIGNAL(keyPress(int)), graph_, SLOT(onKey(int)));
    connect(this, SIGNAL(mMove(qint16,qint16)), graph_, SLOT(onMove(qint16,qint16)));
    connect(this, SIGNAL(mClick(qint16,qint16,delta3::GMCLICK)),
            graph_, SLOT(onClick(qint16,qint16,delta3::GMCLICK)));
    //connect(graph_, SIGNAL(ready(int,int)), this, SLOT(onReady(int,int)));

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


    ev->accept();

    //qDebug() << "    " << Q_FUNC_INFO;
}


void GraphForm::mousePressEvent(QMouseEvent *ev)
{
    int v = ev->x();
    qint16 x = getClientMousePosX( (v < 0) ? 0 : v );
    v = ev->y();
    qint16 y = getClientMousePosY( (v < 0) ? 0 : v );

    quint8 click = ev->buttons();
    click |= delta3::GMCLICK_DOWN;

    emit mClick(x, y, (delta3::GMCLICK)click);

    ev->accept();

    //qDebug() << "    " << Q_FUNC_INFO;
}


void GraphForm::mouseReleaseEvent(QMouseEvent *ev)
{
    int v = ev->x();
    qint16 x = getClientMousePosX( (v < 0) ? 0 : v );
    v = ev->y();
    qint16 y = getClientMousePosY( (v < 0) ? 0 : v );

    quint8 click = ev->buttons();
    click |= delta3::GMCLICK_UP;

    //emit mClick(x, y, (delta3::GMCLICK)click);

    ev->accept();
}

void GraphForm::mouseDoubleClickEvent(QMouseEvent *ev)
{
    int v = ev->x();
    qint16 x = getClientMousePosX( (v < 0) ? 0 : v );
    v = ev->y();
    qint16 y = getClientMousePosY( (v < 0) ? 0 : v );

    quint8 click = ev->buttons();
    click |= delta3::GMCLICK_DCLICK;

    emit mClick(x, y, (delta3::GMCLICK)click);

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
    resize(img.width(), img.height());
    repaint();
}

void GraphForm::onReady(int clW, int clH)
{
    resize(clW, clH);
}


void GraphForm::paintEvent(QPaintEvent *ev)
{
	QPainter p(this);

    //p.scale(1.0 * width() / image_.width(), 1.0 * height() / image_.height());
    p.drawImage(0, 0, image_);

    ev->accept();
}
