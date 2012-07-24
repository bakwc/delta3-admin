#pragma once

#include <QObject>
#include "defines.h"

namespace delta3 {

class Network;

class AbstrProto : public QObject
{
	Q_OBJECT

public:
	explicit AbstrProto(ProtocolMode mode, Network* net = nullptr,
						qint16 clientId = 0, QObject *parent = 0);
	~AbstrProto();
	
signals:
	
protected slots:
	virtual void onDataReceived() = 0;

protected:
	Network	*network_;
	qint16	clientId_;

	ProtocolMode protoMode_;

};

}
