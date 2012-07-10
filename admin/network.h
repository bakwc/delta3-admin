#pragma once
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QMap>
#include "client.h"

typedef QMap<qint32,Client*> Clients;

class Network: public QObject
{
    Q_OBJECT
public:

private:
    QTcpSocket *socket_;
    Clients clients_;
};
