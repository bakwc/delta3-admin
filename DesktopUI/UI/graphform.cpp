#include "graphform.h"
#include "ui_graphform.h"
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>

using namespace delta3;

GraphForm::GraphForm(Graphics *graph, QWidget *parent) :
    QWidget(parent),
	graph_(graph),
    ui(new Ui::GraphForm)
{
    ui->setupUi(this);
	this->setWindowTitle(tr("Graphics - ") + graph_->clientId());

	connect(graph_, SIGNAL(ready(QImage&)), SLOT(onDataReceived(QImage&)));
	connect(this, SIGNAL(ready(QByteArray&)), graph_, SLOT(onReady(QByteArray&)));

	setAttribute(Qt::WA_DeleteOnClose);
}

GraphForm::~GraphForm()
{
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

		emit ready(buf);

        return true;
    }
    return false;
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
