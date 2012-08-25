#include "file.h"
#include "../network.h"
#include "../utils.h"

using namespace delta3;

File::File(Network *net, qint16 clientId, QObject *parent) :
	AbstrProto(MOD_FILE, net, clientId, parent)
{
    _fileName = new QString;
    _localFileName = new QString;
    _cd = new QString("/");
    _f = new QFile;
}

File::~File()
{
    delete _fileName;
    delete _localFileName;
    delete _f;
    delete _cd;
}

void File::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == mode_))
        return;

    QByteArray arr = network_->receivedData().data;

    switch ((quint8)arr[0]) {
    case FMOD_INFO: {
        // (quint)arr[1] // version

        QByteArray send;
        send.append(FMOD_INFO);
        send.append(VERSION);
        sendData(send);

        break;
    }
    case FMOD_DIR:
        emit dir(parseDirCmd(arr));

        break;
    case FMOD_DOWNINFO:
    {
        auto fileNameSize = fromBytes<quint16>(arr.mid(1,2));
        *_fileName = QString::fromUtf8(arr.mid(3,fileNameSize));
        _fileId = arr[3+fileNameSize];
        _fileSize = fromBytes<quint32>(arr.mid(4+fileNameSize,4));
        qDebug() << 4+fileNameSize << arr.size();
        qDebug() << "FMOD_DOWNINFO:" << *_fileName << _fileSize;

        _f->setFileName(*_localFileName);
        if (!_f->open(QIODevice::WriteOnly))
        {
            return;
        }

        _receivedSize=0;

        QByteArray send;
        send.append(FMOD_READY);
        send.append(_fileId);
        send.append('\101');
        sendData(send);

        break;
    }
    case FMOD_DOWNLOAD:
    {
        //qDebug() << "Some data income!";
        auto dataSize=fromBytes<quint16>(arr.mid(2,2));
        QByteArray content=arr.mid(4,dataSize);
        _receivedSize+=dataSize;

        _f->write(content);
        if (_receivedSize>=_fileSize)
        {
            qDebug() << "File received: " << *_fileName;
            emit fileReceived(*_fileName);
            _f->close();
        } else
        {
            QByteArray send;
            send.append(FMOD_READY);
            send.append(_fileId);
            send.append('\101');
            sendData(send);
        }

    }
        break;
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

    sendData(arr);
}


QVector<QStringList> File::parseDirCmd(QByteArray &arr)
{
    QVector<QStringList> vec;
    quint32 i = fromBytes<quint32>(arr.mid(1, 4)), ind = 5, size = 0;

    for (; i; --i) {
        QStringList list;
        // read the size of string and move to the beginning of this string
        size = fromBytes<quint16>(arr.mid(ind, 2));
        ind += 2;
        // Fill list
        list << QString::fromUtf8( arr.mid(ind, size) );
        ind += size;
        list.push_back(arr[ind]=='\0' ? "file" : "dir");
        ind++;

        vec.push_back(list);
    }

    return vec;
}

void File::requestDir()
{
    QByteArray arr;
    arr.append(FMOD_CD);
    arr.append((*_cd).toUtf8());
    sendData(arr);
}

void File::requestFile(QString &remoteFile, QString &localFile)
{
    qDebug() << "admin request file" << *_cd+remoteFile;
    *_localFileName = localFile;
    QByteArray arr,fname=(*_cd+remoteFile).toUtf8();
    arr.append(FMOD_DOWNREQ);
    arr.append(toBytes((quint16)fname.size()));
    arr.append(fname);
    sendData(arr);
}

void File::setCurrentDir(const QString &dir)
{
    *_cd=dir;
}

void File::setDirUp()
{
    if ((*_cd).count("/")>1)
    {
        (*_cd).chop(1);
        auto n=(*_cd).lastIndexOf("/");
        qDebug() << n;
        (*_cd)=(*_cd).left(n+1);
        emit dirChanged(*_cd);
    }
}

void File::openDir(const QString &dir)
{
    *_cd+=dir+"/";
    emit dirChanged(*_cd);
}
