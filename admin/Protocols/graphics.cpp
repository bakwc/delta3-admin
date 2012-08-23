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
            network_->receivedData().mode == mode_))
		return;

    QByteArray arr = network_->receivedData().data;

    switch((quint8)arr[0]) {
    case GMOD_IMG: {
        quint16 imgStrctCount = fromBytes<quint16>(arr.mid(1, 2));
        ImgStructList imageList;

        quint32 ind = 3;
        for (quint16 x, y, s; imgStrctCount > 0; --imgStrctCount) {
            x = fromBytes<quint16>(arr.mid(ind, 2)); ind += 2;
            y = fromBytes<quint16>(arr.mid(ind, 2)); ind += 2;
            s = fromBytes<quint16>(arr.mid(ind, 2)); ind += 2;

            QImage img;
            img.loadFromData(arr.mid(ind, s)); ind += s;

            imageList.push_back(ImgStruct(x, y, img));

//            qDebug() << Q_FUNC_INFO << s << x << y;
        }

        emit images(imageList);

        break; }
    case GMOD_IMGDIFF:
        break;
    case GMOD_IMGFULL: {
        QImage img;
        img.loadFromData(arr.mid(1));
        emit imageReady(img);

        break; }
    case GMOD_INFO: {
        clientWidht_ = fromBytes<quint16>(arr.mid(2,2));
        clientHeight_ = fromBytes<quint16>(arr.mid(4,2));

        QByteArray send;
        send.append(GMOD_INFO);
        send.append(GMOD_PROTOCOL_VERSION);
        send.append((quint8)30);
        sendData(send);

        emit ready(clientWidht_, clientHeight_, 2);
        break; }
    default:
        break;
    }
}

void Graphics::onReady(QByteArray &arr)
{
    network_->sendLevelTwo(clientId_, mode_, arr);
}


void Graphics::onMove(qint16 x, qint16 y)
{
    QByteArray arr;
    arr.append(GMOD_MMOV);
    arr.append(toBytesMacro(x));
    arr.append(toBytesMacro(y));

    sendData(arr);
}

void Graphics::onClick(qint16 x, qint16 y, GMCLICK click)
{
    QByteArray arr;
    arr.append(GMOD_MCLICK);
    arr.append(toBytes(x));
    arr.append(toBytes(y));
    arr.append(click);

    sendData(arr);
}

void Graphics::onKey(int key)
{
    qDebug() << Q_FUNC_INFO << key;

    qint8 k = key;

    QByteArray arr;
    arr.append((quint8)GMOD_KEYEV);
    arr.append(toBytesMacro(k));

    sendData(arr);
}
