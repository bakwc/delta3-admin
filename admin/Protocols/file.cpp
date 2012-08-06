#include "file.h"
#include "network.h"

using namespace delta3;

File::File(Network *net, qint16 clientId, QObject *parent) :
	AbstrProto(MOD_FILE, net, clientId, parent)
{
}

void File::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == mode_))
        return;

    QByteArray arr = network_->receivedData().data;

    switch ((quint8)arr[0]) {
    case FMOD_INFO:
        // (quint)arr[1] // version

        arr.clear();
        arr.append(FMOD_INFO);
        arr.append(VERSION);
        network_->sendLevelTwo(clientId_, mode_, arr);

        break;
    case FMOD_CD:

        break;
    case FMOD_DIR:

        break;
    case FMOD_DOWNINFO:

        break;
    case FMOD_DOWNLOAD:

        break;
    case FMOD_RENAME:

        break;
    case FMOD_DEL:

        break;
    case FMOD_COPYTO:

        break;
    case FMOD_MOVETO:

        break;
    case FMOD_READY:

        break;
    default:
        break;
    }
}

void File::onReady(QString &d)
{
}
