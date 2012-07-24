#include "graphics.h"
#include "network.h"

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

