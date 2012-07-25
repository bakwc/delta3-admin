#pragma once

#include <QTcpServer>
#include <QString>
#include "abstrproto.h"

class QTcpSocket;
class QTcpServer;

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
    QTcpSocket *_inSocket;
    int _socketDescriptor;

private slots:
    void slotReadyRead();
    void slotNewConnection();
};

}
