#pragma once

#include <QObject>
#include <QString>
#include "../defines.h"

namespace delta3 {

class Network;

class AbstrProto : public QObject
{
	Q_OBJECT

public:
    explicit AbstrProto(ProtocolMode mode, Network* net = NULL,
						qint16 clientId = 0, QObject *parent = 0);
	~AbstrProto();

    QString getClientCaption();
	
signals:
	
protected slots:
	virtual void onDataReceived() = 0;

protected:
	Network	*network_;
	qint16	clientId_;

	ProtocolMode protoMode_;

};

}
