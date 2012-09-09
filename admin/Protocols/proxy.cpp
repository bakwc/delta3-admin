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

void Proxy::onDataReceived()        // Data from admin
{
    qDebug() << "SOMETHING COMES HERE!";
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == mode_))
        return;

    //qDebug() << network_->receivedData().data;
    socket_->write(network_->receivedData().data);  // Resend to browser
    socket_->close();   // Disconnect browser

    _clients--;
    qDebug() << "Clients:" << _clients;
}

void Proxy::slotReadyRead()     // Data from browser
{
    QByteArray arr = QByteArray(socket_->readAll());
    sendData(arr);              // Resend to admin
//    network_->sendLevelTwo(clientId_, mode_, _data);

    qDebug() << Q_FUNC_INFO << arr;
}

void Proxy::slotNewConnection()
{
    socket_ = proxyServer_->nextPendingConnection();
    connect(socket_, SIGNAL(readyRead()), SLOT(slotReadyRead()));

    _clients++;
    qDebug() << "Clients:" << _clients;

    //qDebug() << "\n" << Q_FUNC_INFO << "\n";
}

void Proxy::start(int port){
    proxyServer_->listen(QHostAddress::LocalHost,port);
    _clients=0;
}

void Proxy::stop(){
    proxyServer_->close();
}
