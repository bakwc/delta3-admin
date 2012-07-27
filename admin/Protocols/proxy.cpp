#include <QTcpSocket>
#include <QTcpServer>
#include "proxy.h"
#include "../network.h"

using namespace delta3;

Proxy::Proxy(Network *net, qint16 clientId, QObject *parent) :
    AbstrProto(MOD_PROXY, net, clientId, parent)
{
    proxyServer_ = new QTcpServer(this);
    proxyServer_->listen(QHostAddress::LocalHost,8080);

    connect(proxyServer_, SIGNAL(newConnection()), SLOT(slotNewConnection()));
}

void Proxy::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == protoMode_))
        return;

    qDebug() << Q_FUNC_INFO;
    qDebug() << network_->receivedData().data;
    socket_->write(network_->receivedData().data);
}

void Proxy::slotReadyRead()
{
    network_->sendLevelTwo(clientId_, protoMode_, socket_->readAll());

    qDebug() << Q_FUNC_INFO;
}

void Proxy::slotNewConnection()
{
    socket_ = proxyServer_->nextPendingConnection();
    connect(socket_, SIGNAL(readyRead()), SLOT(slotReadyRead()));

    qDebug() << Q_FUNC_INFO;
}
