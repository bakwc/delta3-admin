#include <QTcpSocket>
#include "proxy.h"
#include "../network.h"

using namespace delta3;

Proxy::Proxy(Network *net, qint16 clientId, QObject *parent) :
    AbstrProto(MOD_PROXY, net, clientId, parent)
{
    _proxyServer = new QTcpServer;
    _proxyServer->listen(QHostAddress::Any, 8080);

    _inSocket = new QTcpSocket;

    connect(_proxyServer, SIGNAL(newConnection()), SLOT(slotNewConnection()));
    connect(_inSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
}

void Proxy::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == protoMode_))
        return;

    qDebug() << "ProxyForm::onDataReceived()";
    QByteArray _http = QByteArray(network_->receivedData().data);

    _inSocket->write(_http);
}

void Proxy::slotReadyRead()
{
    qDebug() << "Proxy::slotReadyRead" ;
    QByteArray data = _inSocket->readAll();
    network_->sendLevelTwo(clientId_, protoMode_, data);
}

void Proxy::slotNewConnection()
{
    _socketDescriptor = _proxyServer->socketDescriptor();
    _inSocket->setSocketDescriptor(_socketDescriptor);
    qDebug() << "ProxyForm::slotNewConnection()" << _inSocket->socketDescriptor();
    _inSocket->waitForReadyRead();
}
