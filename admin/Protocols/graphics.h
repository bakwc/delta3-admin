#pragma once

#include "abstrproto.h"
#include <QImage>

#if defined(DELTA3_ADMIN_LIBRARY)
#   define DELTA3_EXPORT Q_DECL_EXPORT
#else
#   define DELTA3_EXPORT Q_DECL_IMPORT
#endif


namespace delta3  {

class DELTA3_EXPORT Graphics : public AbstrProto
{
	Q_OBJECT
public:
    explicit Graphics(Network *net = NULL,
					  qint16 clientId = 0, QObject *parent = 0);
	
signals:
	void ready(QImage &img);
	
protected slots:
	void onDataReceived();

public slots:
	void onReady(QByteArray &arr);
};

}
