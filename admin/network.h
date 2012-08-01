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

#if defined(DELTA3_ADMIN_LIBRARY)
#   define DELTA3_EXPORT Q_DECL_EXPORT
#else
#   define DELTA3_EXPORT Q_DECL_IMPORT
#endif

namespace delta3 {

typedef QMap<qint32, Client *> Clients;

class DELTA3_EXPORT Network: public QObject
{
    Q_OBJECT

    struct DELTA3_EXPORT Income
	{
		qint16 from;
		ProtocolMode mode;
		QByteArray data;
	};

public:
    Network(QHostAddress adr = QHostAddress("127.0.0.1"),
            QObject *parent = NULL);

    void			connectToServer();
    const Clients&	getClients()	const;
    Client			*getClient(qint16 clientId)	const;
    QString			getClientName(qint16 id)	const;
    QString			getClientCapt(qint16 id)	const;
    void			sendLevelOne(qint16 dest, const QByteArray& data);
    void			sendLevelTwo(qint16 dest, ProtocolMode mode, const QByteArray& data);
    void			activateMode(qint16 client, ProtocolMode mode);
    void			deactivateMode(qint16 client, ProtocolMode mode);
    void			setClientCaption(qint16 client, const QString& info);
    const Income&	receivedData()	const;

    void			setHostAddres(QHostAddress adr) { adr_ = adr; }
    const QHostAddress&	hostAddres() const { return adr_; }

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
	QTcpSocket		*socket_;
	Clients			clients_;
	Income			income_;
	QByteArray		buf_;
	QHostAddress	adr_;
};

}
