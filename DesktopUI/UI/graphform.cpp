#include "graphform.h"
#include "ui_graphform.h"
#include <QKeyEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QPainter>
#include <QTime>

using namespace delta3;

GraphForm::GraphForm(Graphics *graph, QWidget *parent) :
    QWidget(parent), graph_(graph), ui(new Ui::GraphForm), pressButtons_(0)
{
    for (ParseClick &cl : mouseButton) {
        cl.count = 0;
        cl.timerId = 0;
    }

    mouseButton[0].mouse = delta3::Graphics::GMCLICK_LEFT;
    mouseButton[1].mouse = delta3::Graphics::GMCLICK_RIGHT;
    mouseButton[2].mouse = delta3::Graphics::GMCLICK_MIDDLE;

    ui->setupUi(this);
    this->setWindowTitle(tr("Graphics - ") + graph_->getClientCaption());

    connect(graph_, SIGNAL(imageReady(QImage&)), SLOT(onDataReceived(QImage&)));
    connect(graph_, SIGNAL(ready(int,int, int)), this, SLOT(onReady(int,int, int)));
    connect(graph_, SIGNAL(images(delta3::Graphics::ImgStructList&)),
            SLOT(images(delta3::Graphics::ImgStructList&)));

    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_OpaquePaintEvent);
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

/* Function increments the counter of clicks
 * and start a timer if it is not running.
 * For each mouse button has its own timer.
 * It's allows press mitiple buttons together
 */
void GraphForm::mousePressEvent(QMouseEvent *ev)
{
    qint16 x = getClientMousePosX(ev->x());
    qint16 y = getClientMousePosY(ev->y());

    pressButtons_ = ev->buttons();

    if (pressButtons_ & Qt::LeftButton)
        graphMouseEvent(0, x, y);

    if (pressButtons_ & Qt::RightButton)
        graphMouseEvent(1, x, y);

    if (pressButtons_ & Qt::MidButton)
        graphMouseEvent(2, x, y);

    ev->accept();
}

/* Computes which button was released
 * and increment the counter of clicks or send release signal,
 * when timer is not working
 */
void GraphForm::mouseReleaseEvent(QMouseEvent *ev)
{
    qint16 x = getClientMousePosX(ev->x());
    qint16 y = getClientMousePosY(ev->y());

    pressButtons_ ^= ev->buttons();

    if (pressButtons_ & Qt::LeftButton) {
        if (mouseButton[0].count > 0)
            mouseButton[0].count += 1;
        else
            emit mClick(x, y, delta3::Graphics::GMCLICK(
                            delta3::Graphics::GMCLICK_LEFT | delta3::Graphics::GMCLICK_UP));
    }

    if (pressButtons_ & Qt::RightButton) {
        if (mouseButton[1].count > 0)
            mouseButton[1].count += 1;
        else
            emit mClick(x, y, delta3::Graphics::GMCLICK(
                            delta3::Graphics::GMCLICK_RIGHT | delta3::Graphics::GMCLICK_UP));
    }

    if (pressButtons_ & Qt::MidButton) {
        if (mouseButton[2].count > 0)
            mouseButton[2].count += 1;
        else
            emit mClick(x, y, delta3::Graphics::GMCLICK(
                            delta3::Graphics::GMCLICK_MIDDLE | delta3::Graphics::GMCLICK_UP));
    }

    ev->accept();
}


void GraphForm::keyPressEvent(QKeyEvent *ev)
{
    emit keyPress(ev->key());
    ev->accept();
}

/* Find mouse button end send click event or double click event.
 * If mouse button up + mouse button down not a multiple of 2,
 * so mouse button was sandwiched and signal will be send to press
 */
void GraphForm::timerEvent(QTimerEvent *ev)
{
    for (int i = 0; i < MBUTTONSCOUNT; ++i) {
        if (mouseButton[i].timerId == ev->timerId()) {
            if (mouseButton[i].count >= 4)
                emit mClick(mouseButton[i].x, mouseButton[i].y,
                            delta3::Graphics::GMCLICK(
                                mouseButton[i].mouse | delta3::Graphics::GMCLICK_DCLICK));
            else if (mouseButton[i].count >= 2)
                emit mClick(mouseButton[i].x, mouseButton[i].y,
                            delta3::Graphics::GMCLICK(
                                mouseButton[i].mouse | delta3::Graphics::GMCLICK_CLICK));

            if (mouseButton[i].count % 2)
                emit mClick(mouseButton[i].x, mouseButton[i].y,
                            delta3::Graphics::GMCLICK(
                                mouseButton[i].mouse | delta3::Graphics::GMCLICK_DOWN));

            killTimer(ev->timerId());
            mouseButton[i].count = 0;
            mouseButton[i].timerId = 0;
        }
    }
}


void GraphForm::graphMouseEvent(int q, quint16 x, quint16 y)
{
    mouseButton[q].count += 1;

    if (mouseButton[q].timerId == 0) {
        mouseButton[q].x = x;
        mouseButton[q].y = y;
        mouseButton[q].timerId = startTimer(CLICKTIME);
    }
}

void GraphForm::onDataReceived(QImage &img)
{
	image_ = img;
    repaint();
}


void GraphForm::onReady(int clW, int clH, int q)
{
    resize(clW/q, clH/q);

    connect(this, SIGNAL(keyPress(int)), graph_, SLOT(onKey(int)));
    connect(this, SIGNAL(mMove(qint16,qint16)), graph_, SLOT(onMove(qint16,qint16)));
    connect(this, SIGNAL(mClick(qint16,qint16,delta3::Graphics::GMCLICK)),
            graph_, SLOT(onClick(qint16,qint16,delta3::Graphics::GMCLICK)));
}

void GraphForm::images(QList<Graphics::ImgStruct> &imgList)
{
    imgStrctList = imgList;
    repaint();
}


void GraphForm::paintEvent(QPaintEvent *ev)
{
	QPainter p(this);

    //p.drawImage(iX, iY, image_);

    for (int i=0; i < imgStrctList.size(); ++i) {
        const delta3::Graphics::ImgStruct &imgStrct = imgStrctList[i];
        p.drawImage(imgStrct.x, imgStrct.y, imgStrct.img);

//        qDebug() << Q_FUNC_INFO << i << imgStrct.x << imgStrct.y;
    }

    ev->accept();
}
