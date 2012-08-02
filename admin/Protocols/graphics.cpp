#include "graphics.h"
#include "../network.h"

using namespace delta3;

Graphics::Graphics(Network *net, qint16 clientId, QObject *parent):
    AbstrProto(MOD_GRAPHICS, net, clientId, parent), clientWidht_(1), clientHeight_(1)
{

}

void Graphics::onDataReceived()
{
	if (!(network_->receivedData().from == clientId_ &&
			network_->receivedData().mode == protoMode_))
		return;

    QByteArray arr = network_->receivedData().data;

    QImage img;

    switch((qint8)arr[0]) {
    case GMOD_IMGDIFF:
        break;
    case GMOD_IMGFULL:
        img.loadFromData(arr.mid(1));
        emit imageReady(img);

        break;
    case GMOD_INFO:
        clientWidht_ = fromBytes<qint16>(arr.mid(2,2));
        clientHeight_ = fromBytes<qint16>(arr.mid(4,2));

        arr.clear();
        arr.append(GMOD_INFO);
        arr.append(GMOD_PROTOCOL_VERSION);
        arr.append((quint8)50);
        network_->sendLevelTwo(clientId_, protoMode_, arr);

        emit ready(clientWidht_, clientHeight_);

        qDebug() << "    GMOD_INFO";

        break;
    default:
        break;
    }
}

void Graphics::onReady(QByteArray &arr)
{
	network_->sendLevelTwo(clientId_, protoMode_, arr);
}


void Graphics::onMove(qint16 x, qint16 y)
{
    QByteArray arr;
    arr.append(GMOD_MMOV);
    arr.append(toBytesMacro(x));
    arr.append(toBytesMacro(y));

    network_->sendLevelTwo(clientId_, protoMode_, arr);
}

void Graphics::onClick(qint16 x, qint16 y, GMCLICK click)
{
    QByteArray arr;
    arr.append(GMOD_MCLICK);
    arr.append(toBytes(x));
    arr.append(toBytes(y));
    arr.append(click);

    network_->sendLevelTwo(clientId_, protoMode_, arr);

    qDebug() << "    " << Q_FUNC_INFO << fromBytes<qint16>(arr.mid(1,2)) <<
                fromBytes<qint16>(arr.mid(3,2)) << (quint8)arr[5];
}

void Graphics::onKey(int key)
{
    qDebug() << Q_FUNC_INFO << key;

    qint8 k = key;

    QByteArray arr;
    arr.append(GMOD_KEYEV);
    arr.append(toBytesMacro(k));

    network_->sendLevelTwo(clientId_, protoMode_, arr);
}
