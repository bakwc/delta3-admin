#pragma once
#include <QtGlobal>
#include <QByteArray>
#include <QString>
#include "defines.h"

#if defined(DELTA3_ADMIN_LIBRARY)
#   define DELTA3_EXPORT Q_DECL_EXPORT
#else
#   define DELTA3_EXPORT Q_DECL_IMPORT
#endif

namespace delta3 {

// -- Level One extracting functions
qint8			DELTA3_EXPORT getProtoId(const QByteArray& data);
qint8			DELTA3_EXPORT getProtoVersion(const QByteArray& data);
Cspyp1Command	DELTA3_EXPORT getCommand(const QByteArray& data);
qint16			DELTA3_EXPORT getClientId(qint16 client, const QByteArray& data);
QByteArray		DELTA3_EXPORT getClientHash(qint16 client, const QByteArray& data);
QString			DELTA3_EXPORT getClientOs(qint16 client, const QByteArray& data);
QString			DELTA3_EXPORT getClientDevice(qint16 client, const QByteArray& data);
QString			DELTA3_EXPORT getClientCaption(qint16 client, const QByteArray& data);
qint32			DELTA3_EXPORT getClientIp(qint16 client, const QByteArray& data);
qint16			DELTA3_EXPORT getClientNumber(const QByteArray& data);
qint16			DELTA3_EXPORT getClientId(const QByteArray& data);
qint32			DELTA3_EXPORT getPacketLength(const QByteArray& data);
QByteArray		DELTA3_EXPORT getPacketData(const QByteArray& data);

// -- Level Two extracting functions

Cspyp2Command	DELTA3_EXPORT getCommand2(const QByteArray& data);
ProtocolMode	DELTA3_EXPORT getMode2(const QByteArray& data);
qint32			DELTA3_EXPORT getPacketLength2(const QByteArray& data);
QByteArray		DELTA3_EXPORT getPacketData2(const QByteArray& data);

}
