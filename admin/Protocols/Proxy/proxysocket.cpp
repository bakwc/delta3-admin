#include "proxysocket.h"

ProxySocket::ProxySocket(int socketDescriptor, QObject *parent) :
    QTcpSocket(parent)
{
    qDebug() << "ProxyServer";
    setSocketDescriptor(socketDescriptor);
}

void ProxySocket::readyRead()
{
    //BUG: can't read from stream :(
    qDebug() << "ProxySocket::readyRead";
}
