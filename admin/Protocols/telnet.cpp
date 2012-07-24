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
			network_->receivedData().mode == protoMode_))
		return;
	qDebug() << "TelnetForm::onDataReceived()";

	QString message = QString::fromUtf8(network_->receivedData().data);

	emit ready(message);
}

void Telnet::onReady(QString &data)
{
	network_->sendLevelTwo(clientId_, protoMode_, data.toUtf8());
}
