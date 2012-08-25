#pragma once

#include "abstrproto.h"
#include <QVector>
#include <QStringList>
#include <QFile>

namespace delta3 {

class DELTA3_EXPORT File : public AbstrProto
{
	Q_OBJECT

    static const quint8 VERSION = 1;
public:
    explicit File(Network *net = NULL,
				  qint16 clientId = 0, QObject *parent = 0);
    ~File();

    enum FileMode
    {
        FMOD_INFO       = 1,
        FMOD_CD         = 2, // cmd
        FMOD_DIR        = 3,
        FMOD_DOWNINFO   = 4,
        FMOD_DOWNLOAD   = 5,
        FMOD_RENAME     = 6, // cmd
        FMOD_DEL        = 7, // cmd
        FMOD_COPYTO     = 8, // cmd
        FMOD_MOVETO     = 9, // cmd
        FMOD_DOWNREQ    = 10,
        FMOD_READY      = 101
    };
	
signals:
    void dir(const QVector<QStringList> &dir);
    void dirChanged(QString &dir);
    void fileReceived(const QString &dir);

protected slots:
	void onDataReceived();

public slots:
    void onCommand(delta3::File::FileMode cmd, QString source, QString dest);
    void requestDir();
    void requestFile(QString &remoteFile, QString &localFile);
    void setCurrentDir(const QString &dir);
    void setDirUp();
    void openDir(const QString &dir);

private:
    QVector<QStringList> parseDirCmd(QByteArray& arr);

    quint32 _fileSize;
    quint32 _receivedSize;
    quint8 _fileId;
    QString *_cd;
    QString *_fileName, *_localFileName;
    QFile *_f;
};

}
