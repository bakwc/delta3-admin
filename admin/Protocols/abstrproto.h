#pragma once

#include <QObject>
#include <QString>
#include "../defines.h"

#if defined(DELTA3_ADMIN_LIBRARY)
#   define DELTA3_EXPORT Q_DECL_EXPORT
#else
#   define DELTA3_EXPORT Q_DECL_IMPORT
#endif

namespace delta3 {

class Network;

class DELTA3_EXPORT AbstrProto : public QObject
{
	Q_OBJECT

public:
    explicit AbstrProto(ProtocolMode mode, Network* net = NULL,
						qint16 clientId = 0, QObject *parent = 0);
	~AbstrProto();

	qint16 clientId() const { return clientId_; }
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
