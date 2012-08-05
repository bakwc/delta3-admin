#pragma once

#include "abstrproto.h"

namespace delta3 {

class DELTA3_EXPORT File : public AbstrProto
{
	Q_OBJECT
public:
    explicit File(Network *net = NULL,
				  qint16 clientId = 0, QObject *parent = 0);
	
signals:
	void ready(QString &d);

protected slots:
	void onDataReceived();

public slots:
	void onReady(QString &d);
};

}
