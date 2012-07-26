#include "proxyserver.h"
#include "proxy.h"
#include "../../network.h"

using namespace delta3;

Proxy::Proxy(Network *net, qint16 clientId, QObject *parent) :
    AbstrProto(MOD_PROXY, net, clientId, parent)
{
    _proxyServer = new ProxyServer;
    _proxyServer->listen(QHostAddress::LocalHost, 8080);
}

void Proxy::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == protoMode_))
        return;

    qDebug() << "ProxyForm::onDataReceived()";
    QByteArray _http = QByteArray(network_->receivedData().data);

    //_inSocket->write(_http);
}
