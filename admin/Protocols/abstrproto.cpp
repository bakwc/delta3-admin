#include "abstrproto.h"
#include "../network.h"

using namespace delta3;


AbstrProto::AbstrProto(ProtocolMode mode, Network *net, qint16 clientId, QObject *parent) :
	QObject(parent), network_(net), clientId_(clientId), mode_(mode)
{
    connect(network_, SIGNAL(dataIncome()), SLOT(onDataReceived()));
	network_->activateMode(clientId_, mode_);

	qDebug("Protocol %i activate", mode_);
}


AbstrProto::~AbstrProto()
{
	network_->deactivateMode(clientId_, mode_);
    disconnect(network_);

	qDebug("Protocol %i deactivate", mode_);
}


QString AbstrProto::getClientCaption()
{
    return network_->getClientCapt(clientId_);
}

void AbstrProto::sendData(const QByteArray &arr)
{
    network_->sendLevelTwo(clientId_, mode_, arr);
}
