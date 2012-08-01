#pragma once

#include "abstrproto.h"
#include <QString>

#if defined(DELTA3_ADMIN_LIBRARY)
#   define DELTA3_EXPORT Q_DECL_EXPORT
#else
#   define DELTA3_EXPORT Q_DECL_IMPORT
#endif

namespace delta3 {

class DELTA3_EXPORT Telnet : public AbstrProto
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
