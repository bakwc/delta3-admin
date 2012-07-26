#pragma once

#include "../abstrproto.h"
#include <QTcpServer>
#include <QHostAddress>

namespace delta3 {

class Proxy : public AbstrProto
{
    Q_OBJECT
public:
    explicit Proxy(Network *net = NULL,
                   qint16 clientId = 0,
                   QObject *parent = 0);

protected slots:
    void onDataReceived();

private:
    QTcpServer *_proxyServer;
private slots:
    void slotReadyRead(const QString &data);
};

}
