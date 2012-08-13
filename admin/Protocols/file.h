#pragma once

#include "abstrproto.h"
#include <QVector>
#include <QStringList>

namespace delta3 {

class DELTA3_EXPORT File : public AbstrProto
{
	Q_OBJECT

    static const quint8 VERSION = 1;
public:
    explicit File(Network *net = NULL,
				  qint16 clientId = 0, QObject *parent = 0);

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

protected slots:
	void onDataReceived();

public slots:
    void onCommand(delta3::File::FileMode cmd, QString source, QString dest);
    void requestDir(QString &dir);
    void requestFile(QString &file);

private:
    QVector<QStringList> parseDirCmd(QByteArray& arr);
};

}
