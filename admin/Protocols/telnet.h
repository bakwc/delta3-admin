#pragma once

#include "abstrproto.h"
#include <QString>

namespace delta3 {

class Telnet : public AbstrProto
{
	Q_OBJECT
public:
    explicit Telnet(Network* net = NULL,
					qint16 clientId = 0, QObject *parent = 0);
	
signals:
	void ready(QString& data);
	
protected slots:
	void onDataReceived();

public slots:
	void onReady(QString &data);
};

}
