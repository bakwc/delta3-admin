#pragma once

#include "../abstrproto.h"

class ProxyServer;

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
    ProxyServer *_proxyServer;
};

}
