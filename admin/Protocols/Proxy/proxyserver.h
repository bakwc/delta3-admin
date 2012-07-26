#pragma once

#include <QTcpServer>

class ProxyThread;

class ProxyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ProxyServer(QObject *parent = 0);

protected:
    void incomingConnection(int handle);

signals:
    void send(const QString &data);
    void proxyAnswer(const QByteArray &data);

private slots:
    void read(const QString &message);
    void slotProxyAnswer(const QByteArray &data);

private:
    ProxyThread *thread_;
};
