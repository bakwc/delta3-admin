#include "file.h"

using namespace delta3;

File::File(Network *net, qint16 clientId, QObject *parent) :
	AbstrProto(MOD_FILE, net, clientId, parent)
{
}

void File::onDataReceived()
{
}

void File::onReady(QString &d)
{
}
