#include "telnet.h"
#include "network.h"
#include "defines.h"

using namespace delta3;

Telnet::Telnet(Network *net, qint16 clientId, QObject *parent) :
	AbstrProto(MOD_TELNET, net, clientId, parent)
{
}


void Telnet::onDataReceived()
{
	if (!(network_->receivedData().from == clientId_ &&
			network_->receivedData().mode == delta3::MOD_TELNET))
		return;
	qDebug() << "TelnetForm::onDataReceived()";

	QString message = QString::fromUtf8(network_->receivedData().data);

	emit ready(message);
}

void Telnet::onReady(QString &data)
{
	network_->sendLevelTwo(clientId_, protoMode_, data.toUtf8());
}
