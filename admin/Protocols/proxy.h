#pragma once

#include "abstrproto.h"

class QTcpServer;
class QTcpSocket;

namespace delta3 {

class DELTA3_EXPORT Proxy : public AbstrProto
{
    Q_OBJECT
public:
    explicit Proxy(Network *net = NULL,
                   qint16 clientId = 0,
                   QObject *parent = 0);
    void start(int port);
    void stop();

protected slots:
    void onDataReceived();

private slots:
    void slotReadyRead();
    void slotNewConnection();

private:
    QTcpServer *proxyServer_;
    QTcpSocket *socket_;
    qint32 _clients;
};

}
