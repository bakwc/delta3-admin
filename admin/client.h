#pragma once
#include <QObject>
#include <QString>
#include <QDebug>

class Client: public QObject
{
    Q_OBJECT
public:
    Client(QObject *parent,const QString& _clientHash,qint32 _id);
    QString getHash() const;
private:
    QString clientIdHash_;
    qint32 clientId_;
};
