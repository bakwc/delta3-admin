#include "client.h"

Client::Client(QObject *parent):
    QObject(parent)
{
    qDebug() << id_ << idHash_;
}

QString Client::getHash() const
{
    return idHash_;
}

qint32 Client::getId() const
{
    return id_;
}

void Client::setHash(const QByteArray& hash)
{
    idHash_=hash.toHex();
}

void Client::setId(qint16 id)
{
    id_=id;
}

void Client::setOs(const QString& os)
{
    os_=os;
}

void Client::setDevice(const QString& device)
{
    device_=device;
}

void Client::setCaption(const QString& caption)
{
    caption_=caption;
}

QString Client::getOs() const
{
    return os_;
}

QString Client::getDevice() const
{
    return device_;
}

QString Client::getCaption() const
{
    return caption_;
}
