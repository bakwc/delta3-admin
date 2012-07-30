#include "graphics.h"
#include "../network.h"

using namespace delta3;

Graphics::Graphics(Network *net, qint16 clientId, QObject *parent):
	AbstrProto(MOD_GRAPHICS, net, clientId, parent)
{

}

void Graphics::onDataReceived()
{
	if (!(network_->receivedData().from == clientId_ &&
			network_->receivedData().mode == protoMode_))
		return;

	QImage img;
	img.loadFromData(network_->receivedData().data);

	emit ready(img);
}

void Graphics::onReady(QByteArray &arr)
{
	network_->sendLevelTwo(clientId_, protoMode_, arr);
}


void Graphics::onMove(qint16 x, qint16 y)
{
    qDebug() << Q_FUNC_INFO << x << y;

    QByteArray arr;
    arr.append(GMOD_MMOV);
    arr.append(toBytesMacro(x));
    arr.append(toBytesMacro(y));

    network_->sendLevelTwo(clientId_, protoMode_, arr);
}

void Graphics::onClick(qint16 x, qint16 y, GMCLICK click)
{
    qDebug() << Q_FUNC_INFO << x << y << click;

    QByteArray arr;
    arr.append(GMOD_MCLICK);
    arr.append(toBytesMacro(x));
    arr.append(toBytesMacro(y));
    arr.append(click);

    network_->sendLevelTwo(clientId_, protoMode_, arr);
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
