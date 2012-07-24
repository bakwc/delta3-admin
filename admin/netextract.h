#pragma once
#include <QtGlobal>
#include <QByteArray>
#include <QString>
#include "defines.h"

namespace delta3 {

// -- Level One extracting functions
qint8			getProtoId(const QByteArray& data);
qint8			getProtoVerstion(const QByteArray& data);
Cspyp1Command	getCommand(const QByteArray& data);
qint16			getClientId(qint16 client, const QByteArray& data);
QByteArray		getClientHash(qint16 client, const QByteArray& data);
QString			getClientOs(qint16 client, const QByteArray& data);
QString			getClientDevice(qint16 client, const QByteArray& data);
QString			getClientCaption(qint16 client, const QByteArray& data);
qint32			getClientIp(qint16 client, const QByteArray& data);
qint16			getClientNumber(const QByteArray& data);
qint16			getClientId(const QByteArray& data);
qint32			getPacketLength(const QByteArray& data);
QByteArray		getPacketData(const QByteArray& data);

// -- Level Two extracting functions

Cspyp2Command	getCommand2(const QByteArray& data);
ProtocolMode	getMode2(const QByteArray& data);
qint32			getPacketLength2(const QByteArray& data);
QByteArray		getPacketData2(const QByteArray& data);

}
