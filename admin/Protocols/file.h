#pragma once

#include "abstrproto.h"

namespace delta3 {

class DELTA3_EXPORT File : public AbstrProto
{
	Q_OBJECT

    static const quint8 VERSION = 1;
public:
    explicit File(Network *net = NULL,
				  qint16 clientId = 0, QObject *parent = 0);
	
signals:
    void ready(QStringList &d);

protected slots:
	void onDataReceived();

public slots:
	void onReady(QString &d);

public:
    enum FileMode
    {
        FMOD_INFO       = 1,
        FMOD_CD         = 2,
        FMOD_DIR        = 3,
        FMOD_DOWNINFO   = 4,
        FMOD_DOWNLOAD   = 5,
        FMOD_RENAME     = 6,
        FMOD_DEL        = 7,
        FMOD_COPYTO     = 8,
        FMOD_MOVETO     = 9,
        FMOD_READY      = 101
    };
};

}
