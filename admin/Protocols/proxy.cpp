#include <QTcpSocket>
#include <QTcpServer>
#include "proxy.h"
#include "../network.h"

using namespace delta3;

Proxy::Proxy(Network *net, qint16 clientId, QObject *parent) :
    AbstrProto(MOD_PROXY, net, clientId, parent)
{
    proxyServer_ = new QTcpServer(this);

    connect(proxyServer_, SIGNAL(newConnection()), SLOT(slotNewConnection()));
}

void Proxy::onDataReceived()
{
    qDebug() << "SOMETHING COMES HERE!";
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == mode_))
        return;

    qDebug() << network_->receivedData().data;
    socket_->write(network_->receivedData().data);
    socket_->close();
}

void Proxy::slotReadyRead()
{
    QByteArray arr = QByteArray(socket_->readAll());
    sendData(arr);
//    network_->sendLevelTwo(clientId_, mode_, _data);

    qDebug() << Q_FUNC_INFO << arr;
}

void Proxy::slotNewConnection()
{
    socket_ = proxyServer_->nextPendingConnection();
    connect(socket_, SIGNAL(readyRead()), SLOT(slotReadyRead()));

    //qDebug() << "\n" << Q_FUNC_INFO << "\n";
}

void Proxy::start(int port){
    proxyServer_->listen(QHostAddress::LocalHost,port);
}

void Proxy::stop(){
    proxyServer_->close();
}
