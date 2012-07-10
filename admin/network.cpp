#include "network.h"

Network::Network(QObject *parent):
    QObject(parent)
{
    socket_ = new QTcpSocket(this);
    QObject::connect(socket_, SIGNAL(readyRead()),
                     this, SLOT(onDataReceived()));

    QObject::connect(socket_, SIGNAL(connected()),
                     this,SLOT(onConnected()));
}

void Network::connect()
{
    if (socket_->state()!=QTcpSocket::UnconnectedState)
        return;

    socket_->connectToHost(QHostAddress("127.0.0.1"),1235);
                                    // TODO: request from user

}

void Network::onDataReceived()
{
    qDebug("onDataReceived()");
    QByteArray data=socket_->readAll();
    parseData(data);
}

void Network::parseData(const QByteArray &data)
{
    parseList(data);
}

bool Network::parseList(const QByteArray &data)
{
    QRegExp re("l:(.+):");
    if (re.indexIn(data) == -1)
        return false;

    qDebug("parseList()");

    QStringList clients = re.cap(1).split(";");

    clients_.clear();
    for (auto i = clients.begin();(i + 1) < clients.end(); i += 2)
    {
        qint32 id = (*i).toInt();
        QString hash = *(i + 1);
        //qDebug() << id << hash;
        if (hash.size() != 32) continue;
        Client *client = new Client(this, hash, id);
        clients_.insert(id, client);
    }
    emit listUpdated();
    return true;
}
void Network::onConnected()
{
    socket_->write("cspyadm:1:admin:admin:");
    socket_->write("l:");
    socket_->flush();
}

 const Clients& Network::getClients()
 {
     return clients_;
 }
