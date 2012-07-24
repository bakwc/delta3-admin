#include "abstrproto.h"
#include "network.h"

namespace delta3{

AbstrProto::AbstrProto(ProtocolMode mode, Network *net, qint16 clientId, QObject *parent) :
	QObject(parent), network_(net), clientId_(clientId), protoMode_(mode)
{
	network_->activateMode(clientId_, protoMode_);
	connect(network_, SIGNAL(dataIncome()), SLOT(onDataReceived()));
}

AbstrProto::~AbstrProto()
{
	disconnect(network_);
	network_->deactivateMode(clientId_, protoMode_);
}
}
