#include "proxy.h"
#include "../network.h"

using namespace delta3;

Proxy::Proxy(Network *net, qint16 clientId, QObject *parent) :
    AbstrProto(MOD_PROXY, net, clientId, parent)
{
}

void Proxy::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == protoMode_))
        return;
    qDebug() << "ProxyForm::onDataReceived()";

    QString message = QString::fromUtf8(network_->receivedData().data);

    emit ready(message);
}

void Proxy::onReady(QString &data)
{
    network_->sendLevelTwo(clientId_, protoMode_, data.toUtf8());
}
