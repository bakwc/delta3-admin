#pragma once

#include "abstrproto.h"
#include <QImage>

namespace delta3  {

class Graphics : public AbstrProto
{
	Q_OBJECT
public:
	explicit Graphics(Network *net = nullptr,
					  qint16 clientId = 0, QObject *parent = 0);
	
signals:
	void ready(QImage &img);
	
protected slots:
	void onDataReceived();

public slots:
	void onReady(QByteArray &arr);
};

}
