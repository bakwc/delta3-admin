#include "proxyserver.h"
#include "proxysocket.h"

ProxyServer::ProxyServer(QObject *parent) :
    QTcpServer(parent)
{

}

void ProxyServer::incomingConnection(int handle)
{
    qDebug() << "ProxyServer::incomingConnection" << handle;
    socket_ = new ProxySocket(handle);
}
