#pragma once

#include <QString>
#include "abstrproto.h"

namespace delta3 {

class Proxy : public AbstrProto
{
    Q_OBJECT
public:
    explicit Proxy(Network *net = NULL,
                   qint16 clientId = 0,
                   QObject *parent = 0);

signals:
    void ready(QString &data);

protected slots:
    void onDataReceived();

public slots:
    void onReady(QString &data);
};

}
