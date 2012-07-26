#include "proxythread.h"
#include <QTcpSocket>

ProxyThread::ProxyThread(int socketDescriptor, QObject *parent) :
    QThread(parent), socketDescriptor_(socketDescriptor)
{
}

void ProxyThread::run()
{
    socket_ = new QTcpSocket;
    socket_->setSocketDescriptor(socketDescriptor_);
    connect(socket_, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    socket_->waitForReadyRead();
}

void ProxyThread::slotReadyRead()
{
     emit read(socket_->readAll());
}
