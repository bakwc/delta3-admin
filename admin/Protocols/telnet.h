#pragma once

#include "abstrproto.h"
#include <QString>

namespace delta3 {

class DELTA3_EXPORT Telnet : public AbstrProto
{
    Q_OBJECT
public:
    explicit Telnet(Network *net = NULL,
                    qint16 clientId = 0,
                    QObject *parent = 0);

    enum TelnetMode {
        TMOD_REQ    = 1,
        TMOD_RESP   = 2,
        TMOD_CMD    = 3
    };

    enum TMODCMD {
        TMODCMD_BREAK   = 1,
        TMODCMD_UP      = 11,
        TMODCMD_DOWN    = 12
    };

signals:
    void ready(QString &data);

protected slots:
    void onDataReceived();

public slots:
    void sendCommand(QString &data);
    void sendCommand(TMODCMD cmd);
};

}
