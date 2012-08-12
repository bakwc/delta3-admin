#include "telnet.h"
#include "../network.h"
#include <QKeyEvent>

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


bool Telnet::event(QEvent *ev)
{
    if (ev->type() == QEvent::KeyPress) {
        QKeyEvent *kEv = static_cast<QKeyEvent*>(ev);
        qDebug() << Q_FUNC_INFO << "KeyPress" << kEv->text() << kEv->key();

        if (kEv->key() == Qt::Key_Up) {
            QByteArray send;
            send.append(TMOD_CMD);
            send.append(TMODCMD_UP);
            sendData(send);
        } else if (kEv->key() == Qt::Key_Down) {
            QByteArray send;
            send.append(TMOD_CMD);
            send.append(TMODCMD_DOWN);
            sendData(send);
        } else if (kEv->modifiers() == Qt::ControlModifier &&
                kEv->key() == Qt::Key_C) {
            QByteArray send;
            send.append(TMOD_CMD);
            send.append(TMODCMD_BREAK);
            sendData(send);
        }
    }

    AbstrProto::event(ev);
}
