#pragma once
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QMap>
#include <QRegExp>
#include <QStringList>
#include <QByteArray>
#include <QString>
#include "utils.h"
#include "client.h"
#include "defines.h"

typedef QMap<qint32, Client *> Clients;

class Network: public QObject
{
    Q_OBJECT
public:
    struct Income
    {
        qint16 from;
        ProtocolMode mode;
        QByteArray data;
    };

public:
    Network(QObject *parent);
    void connectToServer();
    const Clients& getClients() const;
    const Client *getClient(qint16 clientId) const;
    QString getClientName(qint16 id) const;
    void sendLevelOne(qint16 dest, const QByteArray& data);
    void sendLevelTwo(qint16 dest, ProtocolMode mode, const QByteArray& data);
    void activateMode(qint16 client, ProtocolMode mode);
    void deactivateMode(qint16 client, ProtocolMode mode);
    const Income& receivedData() const;
signals:
    void listUpdated();
    void dataIncome();
private slots:
    void onDataReceived();
    void onConnected();
private:
    void parseList();
    void parsePing();
    void parseResponse();
    void parseProtoTwo(qint32 from, const QByteArray &data); // parsing level 2 proto
    void parseMessage(qint32 from, const QByteArray &data);

private:
    QTcpSocket *socket_;
    Clients clients_;
    Income income_;
    QByteArray buf_;
};
