#include "netextract.h"
#include "utils.h"

namespace delta3 {

// -- Level One extracting functions

qint8 getProtoId(const QByteArray& data)
{
    return (qint8)(data[0]);
}

qint8 getProtoVersion(const QByteArray& data)
{
    return (qint8)(data[1]);
}

Cspyp1Command getCommand(const QByteArray& data)
{
    return (Cspyp1Command)(char)(data[2]);
}

qint16 getClientNumber(const QByteArray& data)
{
    QByteArray clientNum=data.mid(3,2);
    return fromBytes<quint16>(clientNum);
}

qint32 getPacketLength(const QByteArray& data)
{
    QByteArray clientNum=data.mid(5,4);
    return fromBytes<quint32>(clientNum);
}

qint16 getClientId(qint16 client, const QByteArray& data)
{
    QByteArray clientId=data.mid(5+client*CMD1_CLIENT_INFO_SIZE,2);
    return fromBytes<qint16>(clientId);
}

qint16 getClientId(const QByteArray& data)
{
    QByteArray clientId=data.mid(3,2);
    return fromBytes<qint16>(clientId);
}

QByteArray getClientHash(qint16 client, const QByteArray& data)
{
    /*
    QByteArray clientHash=data.mid(5+client*CMD1_CLIENT_INFO_SIZE+2,16);
    QString hash;
    QTextStream myStream(&hash);
    for (auto i=clientHash.begin()+3;i<clientHash.begin()+19;i++)
        myStream << hex << (qint8)(*i);
    return hash;*/
    return data.mid(5+client*CMD1_CLIENT_INFO_SIZE+2,16);
}

QString getClientOs(qint16 client, const QByteArray& data)
{
    return data.mid(5+client*CMD1_CLIENT_INFO_SIZE+18,20);
}

QString getClientDevice(qint16 client, const QByteArray& data)
{
    return data.mid(5+client*CMD1_CLIENT_INFO_SIZE+38,20);
}

QString getClientCaption(qint16 client, const QByteArray& data)
{
    return data.mid(5+client*CMD1_CLIENT_INFO_SIZE+62,30);
}

qint32 getClientIp(qint16 client, const QByteArray& data)
{
    QByteArray ip=data.mid(5+client*CMD1_CLIENT_INFO_SIZE+58,4);
    return fromBytes<qint32>(ip);
}

QByteArray getPacketData(const QByteArray& data)
{
	return data.mid(9, getPacketLength(data));
}


// -- Level Two extraction functions

Cspyp2Command getCommand2(const QByteArray& data)
{
    return (Cspyp2Command)data[2];
}

ProtocolMode getMode2(const QByteArray& data)
{
    return (ProtocolMode)data[3];
}

qint32 getPacketLength2(const QByteArray& data)
{
    QByteArray len=data.mid(4,4);
    return fromBytes<qint32>(len);
}

QByteArray getPacketData2(const QByteArray& data)
{
	return data.right(getPacketLength2(data));
}

}
