#include "telnet.h"
#include "../network.h"

using namespace delta3;


Telnet::Telnet(Network *net, qint16 clientId, QObject *parent) :
    AbstrProto(MOD_TELNET, net, clientId, parent)
{
}


void Telnet::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == protoMode_)) {
        qDebug() << Q_FUNC_INFO << "PROTOCOL ERROR";
        return;
    }

    qDebug() << "TelnetForm::onDataReceived()";

    const QByteArray &arr = network_->receivedData().data;

    switch ((quint8)arr[0]) {
    case TMOD_RESP: {
        int size = fromBytes<quint32>(arr.mid(1, 4));
        QString message = QString::fromUtf8(arr.mid(5, size));

        emit ready(message);

        qDebug() << Q_FUNC_INFO << message << size;
    }

    }
}


void Telnet::sendCommand(QString &data)
{
    QByteArray send, arr = data.toUtf8();

    send.append((quint8)TMOD_REQ);
    send.append(toBytes<quint32>(arr.size()));
    send.append(arr);

    //network_->sendLevelTwo(clientId_, protoMode_, send);
    sendData(send);
}


void Telnet::sendCommand(TMODCMD cmd)
{
    QByteArray send;
    send.append((quint8)TMOD_CMD);
    send.append((quint8)cmd);

    sendData(send);
}
