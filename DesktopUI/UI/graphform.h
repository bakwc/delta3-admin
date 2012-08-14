#pragma once

#include <QWidget>
#include "network.h"
#include "defines.h"
#include "Protocols/graphics.h"

namespace Ui {
class GraphForm;
}

class GraphForm : public QWidget
{
    Q_OBJECT

    static const int CLICKTIME      = 300;
    static const int MBUTTONSCOUNT  = 3;
    
public:
	explicit GraphForm(delta3::Graphics* graph, QWidget* parent = 0);
    ~GraphForm();

signals:
	void ready(QByteArray &arr);
    void mMove(qint16, qint16);
    void mClick(qint16, qint16, delta3::Graphics::GMCLICK);
    void keyPress(int key);

private slots:
	void onDataReceived(QImage &img);
    void onReady(int clW, int clH, int q);
    void images(delta3::Graphics::ImgStructList &imgList);

protected:
	void paintEvent(QPaintEvent *);
    bool eventFilter(QObject* obj, QEvent* ev);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
	delta3::Graphics	*graph_;
	QImage				image_; // mb it's a not very well idea ;|
	Ui::GraphForm		*ui;
    delta3::Graphics::ImgStructList imgStrctList;
    quint8  pressButtons_;
    int iX, iY;

    struct ParseClick {
        int             timerId;
        int             count;
        quint16         x, y;
        delta3::Graphics::GMCLICK mouse;
    } mouseButton[MBUTTONSCOUNT];

    qint16 getClientMousePosX(int mPos) {
        qint16 v = 1.0 * mPos / width() * graph_->clientWidth();
        return (v < 0) ? 0 : v;
    }

    qint16 getClientMousePosY(int mPos) {
        qint16 v = 1.0 * mPos / height() * graph_->clientHeight();
        return (v < 0) ? 0 : v;
    }

    void graphMouseEvent(int q, quint16 x, quint16 y);

};
