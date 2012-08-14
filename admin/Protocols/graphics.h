#pragma once

#include "abstrproto.h"
#include <QImage>

namespace delta3  {

class DELTA3_EXPORT Graphics : public AbstrProto
{
	Q_OBJECT
public:
    explicit Graphics(Network *net = NULL,
					  qint16 clientId = 0, QObject *parent = 0);

    enum GraphicsMode
    {
        GMOD_INFO       = 1,
        GMOD_IMGFULL    = 2,
        GMOD_IMGDIFF    = 3,
        GMOD_KEYEV      = 4,
        GMOD_MMOV       = 5,
        GMOD_MCLICK     = 6,
        GMOD_IMG        = 7
    };

    enum GMCLICK {
        GMCLICK_LEFT    = 1,
        GMCLICK_RIGHT   = 2,
        GMCLICK_MIDDLE  = 4,
        GMCLICK_DOWN    = 8,
        GMCLICK_UP      = 16,
        GMCLICK_CLICK   = 32,
        GMCLICK_DCLICK  = 64
    };

    struct ImgStruct {
        quint16 x, y;
        QImage img;
        ImgStruct(quint16 dX, quint16 dY,const QImage &Img) :
            x(dX), y(dY), img(Img) {}
    };

    typedef QList<delta3::Graphics::ImgStruct> ImgStructList;

    quint16 clientWidth() const { return clientWidht_; }
    quint16 clientHeight() const { return clientHeight_; }
	
signals:
    void ready(int clW, int clH, int q);
    void imageReady(QImage &img);
    void images(delta3::Graphics::ImgStructList &imgList);
	
protected slots:
	void onDataReceived();

	void onReady(QByteArray &arr);
    void onMove(qint16 x, qint16 y);
    void onClick(qint16 x, qint16 y, delta3::Graphics::GMCLICK click);
    void onKey(int key);

private:
    qint16 clientWidht_;
    qint16 clientHeight_;

    //GraphicsMode
};

}
