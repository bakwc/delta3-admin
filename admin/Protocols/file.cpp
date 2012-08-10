#include "file.h"
#include "../network.h"

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
    QByteArray send;

    switch ((quint8)arr[0]) {
    case FMOD_INFO:
        // (quint)arr[1] // version

        send.clear();
        send.append(FMOD_INFO);
        send.append(VERSION);
        network_->sendLevelTwo(clientId_, mode_, send);

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
    QByteArray arr, s, d;

    arr.append(cmd);

    s.append(source.toUtf8());
    arr.append(toBytes<quint16>(s.size()));
    arr.append(s);

    if(cmd != FMOD_DEL) {
        d.append(dest.toUtf8());
        arr.append(toBytes<quint16>(d.size()));
        arr.append(d);
    }

    network_->sendLevelTwo(clientId_, mode_, arr);
}


QVector<QStringList> File::parseDirCmd(QByteArray &arr)
{
    qDebug() << Q_FUNC_INFO << "array size " << arr.size();

    QVector<QStringList> vec;
    quint32 i = fromBytes<quint32>(arr.mid(1, 4)), ind = 5, size = 0;

    for (; i; --i) {
        QStringList list;

        // read the size of string and move to the beginning of this string
        size = fromBytes<quint16>(arr.mid(ind, 2));
        ind += 2;
        list << QString::fromUtf8( arr.mid(ind, size) );
        vec.push_back(list);
        ind += size;
    }

    return vec;
}

void File::requestDir(QString &dir)
{
    qDebug() << Q_FUNC_INFO;
    QByteArray arr;

    arr.append(FMOD_CD);
    arr.append(dir.toUtf8());
    //arr.append('\0'); // ??

    network_->sendLevelTwo(clientId_, mode_, arr);
}
