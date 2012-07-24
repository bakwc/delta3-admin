#include "abstrproto.h"
#include "../network.h"

using namespace delta3;

AbstrProto::AbstrProto(ProtocolMode mode, Network *net, qint16 clientId, QObject *parent) :
	QObject(parent), network_(net), clientId_(clientId), protoMode_(mode)
{
	network_->activateMode(clientId_, protoMode_);
	connect(network_, SIGNAL(dataIncome()), SLOT(onDataReceived()));

	qDebug("Protocol %i activate", protoMode_);

}

AbstrProto::~AbstrProto()
{
	disconnect(network_);
	network_->deactivateMode(clientId_, protoMode_);

	qDebug("Protocol %i deactivate", protoMode_);
}
