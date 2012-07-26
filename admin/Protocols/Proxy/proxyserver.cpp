#include "proxyserver.h"
#include "proxythread.h"

ProxyServer::ProxyServer(QObject *parent) :
    QTcpServer(parent)
{
}

void ProxyServer::incomingConnection(int handle)
{
    qDebug() << "ProxyServer::incomingConnection" << handle;
    thread_ = new ProxyThread(handle);
    connect(thread_, SIGNAL(read(QString)), SLOT(read(QString)));
    //c

    thread_->start();
}

void ProxyServer::read(const QString &message)
{
    emit send(message);
}

void ProxyServer::slotProxyAnswer(const QByteArray &data)
{
    emit proxyAnswer(data);
}
