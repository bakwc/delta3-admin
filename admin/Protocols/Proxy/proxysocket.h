#pragma once

#include <QTcpSocket>

class ProxySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ProxySocket(int socketDescriptor = -1,
                         QObject *parent = 0);

signals:

public slots:

protected:
    void readyRead();
};
