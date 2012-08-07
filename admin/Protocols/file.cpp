#include "file.h"
#include "network.h"
#include <QTextCodec>

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
//    case FMOD_CD:

//        break;
    case FMOD_DIR:
        emit dir(parseDirCmd(arr));

        break;
    case FMOD_DOWNINFO:

        break;
    case FMOD_DOWNLOAD:

        break;
//    case FMOD_RENAME:

//        break;
//    case FMOD_DEL:

//        break;
//    case FMOD_COPYTO:

//        break;
//    case FMOD_MOVETO:

//        break;
    case FMOD_READY:

        break;
    default:
        break;
    }
}

void File::onCommand(File::FileMode cmd, QString source, QString dest)
{
    QByteArray arr;

    arr.append(cmd);
    arr.append((quint8)source.size());
    arr.append( reinterpret_cast<const char*>(source.utf16()) );

    if(cmd != FMOD_DEL) {
        arr.append((quint8)dest.size());
        arr.append( reinterpret_cast<const char*>(dest.utf16()) );
    }

    network_->sendLevelTwo(clientId_, mode_, arr);
}


QVector<QStringList> File::parseDirCmd(QByteArray &arr)
{
    QVector<QStringList> vec;
    int i = arr[1], ind = 2, size = 0;

    for (; i; --i) {
        size = arr[ind++]; // read the size of string and move to the beginning of this string
        QStringList list;
        list << QString::fromUtf16(fromBytes<ushort*>(arr.mid(ind, size)), size);
        vec.push_back(list);
        ind += size;
    }

    return vec;
}
