#pragma once
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QMap>
#include <QRegExp>
#include <QStringList>
#include <QByteArray>
#include <QString>
#include "client.h"
#include "defines.h"

typedef QMap<qint32, Client *> Clients;

class Network: public QObject
{
    Q_OBJECT
public:
    struct Income
    {
        qint32 from;
        ProtocolMode mode;
        QByteArray data;
    };

public:
    Network(QObject *parent);
    void connectToServer();
    const Clients& getClients() const;
    QString getClientName(qint32 id) const;
    void sendLevelOne(qint32 dest, const QByteArray& data);
    void sendLevelTwo(qint32 dest, ProtocolMode mode, const QByteArray& data);
    void activateMode(qint32 client, ProtocolMode mode);
    void deactivateMode(qint32 client, ProtocolMode mode);
    const Income& receivedData() const;
signals:
    void listUpdated();
    void dataIncome();
private slots:
    void onDataReceived();
    void onConnected();
private:
    void parseData(const QByteArray &data); // parsing level 1 proto
    bool parseList(const QByteArray &data);
    bool parseResponse(const QByteArray &data);
    void parseProtoTwo(qint32 from, const QByteArray &data); // parsing level 2 proto
    bool parseMessage(qint32 from, const QByteArray &data);
private:
    QTcpSocket *socket_;
    Clients clients_;
    Income income_;
};
