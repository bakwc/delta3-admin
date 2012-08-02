#pragma once

#include "abstrproto.h"
#include <QImage>

namespace delta3  {

class Graphics : public AbstrProto
{
	Q_OBJECT
public:
    explicit Graphics(Network *net = NULL,
					  qint16 clientId = 0, QObject *parent = 0);

    qint16 clientWidth() const { return clientWidht_; }
    qint16 clientHeight() const { return clientHeight_; }
	
signals:
    void ready(int clW, int clH);
    void imageReady(QImage &img);
	
protected slots:
	void onDataReceived();

	void onReady(QByteArray &arr);
    void onMove(qint16 x, qint16 y);
    void onClick(qint16 x, qint16 y, delta3::GMCLICK click);
    void onKey(int key);

private:
    qint16 clientWidht_;
    qint16 clientHeight_;

    //GraphicsMode
};

}
