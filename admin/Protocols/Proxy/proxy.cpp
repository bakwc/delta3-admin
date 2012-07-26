#include <QThread>
#include "proxy.h"
#include "proxyserver.h"
#include "../../network.h"

using namespace delta3;

Proxy::Proxy(Network *net, qint16 clientId, QObject *parent) :
    AbstrProto(MOD_PROXY, net, clientId, parent)
{
 //   proxyServer_ = new ProxyServer;
 //   proxyServer_->listen(QHostAddress::LocalHost, 8080);

  //  connect(proxyServer_, SIGNAL(send(QString)), SLOT(slotReadyRead(QString)));
    //connect(SIGNAL(on))

    _proxyServer = new QTcpServer(this);
    _proxyServer->listen(QHostAddress("0.0.0.0"),8080);
}

void Proxy::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == protoMode_))
        return;

    qDebug() << "ProxyForm::onDataReceived()";
    //QByteArray http_ = QByteArray(network_->receivedData().data);

    //_inSocket->write(http_);
}

void Proxy::slotReadyRead(const QString &data)
{
    //network_->sendLevelTwo(clientId_, protoMode_, data.toUtf8());
    //qDebug() << data;
}
