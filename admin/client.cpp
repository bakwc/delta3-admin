#include "client.h"

Client::Client(QObject *parent,const QString& _clientHash,qint32 _id):
    QObject(parent), clientIdHash_(_clientHash),clientId_(_id)
{
    qDebug() << clientId_ << clientIdHash_;
}

QString Client::getHash() const
{
    return clientIdHash_;
}
