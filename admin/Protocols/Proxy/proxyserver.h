#pragma once

#include <QTcpServer>

class ProxySocket;

class ProxyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ProxyServer(QObject *parent = 0);

protected:
    void incomingConnection(int handle);

signals:

public slots:

private:
    ProxySocket *socket_;
};
