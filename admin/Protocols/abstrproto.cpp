#include "abstrproto.h"
#include "../network.h"

using namespace delta3;

AbstrProto::AbstrProto(ProtocolMode mode, Network *net, qint16 clientId, QObject *parent) :
	QObject(parent), network_(net), clientId_(clientId), protoMode_(mode)
{
    connect(network_, SIGNAL(dataIncome()), SLOT(onDataReceived()));
	network_->activateMode(clientId_, protoMode_);

	qDebug("Protocol %i activate", protoMode_);

}

AbstrProto::~AbstrProto()
{
	network_->deactivateMode(clientId_, protoMode_);
    disconnect(network_);

	qDebug("Protocol %i deactivate", protoMode_);
}

QString AbstrProto::getClientCaption()
{
    return network_->getClientCapt(clientId_);
}
