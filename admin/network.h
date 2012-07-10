#pragma once
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QMap>
#include <QRegExp>
#include <QStringList>
#include "client.h"

typedef QMap<qint32,Client*> Clients;

class Network: public QObject
{
    Q_OBJECT
public:
    Network(QObject *parent);
    void connect();
    const Clients& getClients();
signals:
    void listUpdated();
private slots:
    void onDataReceived();
    void onConnected();
private:
    void parseData(const QByteArray &data);
    bool parseList(const QByteArray &data);
private:
    QTcpSocket *socket_;
    Clients clients_;
};
