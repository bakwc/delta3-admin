#pragma once

#include <QThread>

class QTcpSocket;

class ProxyThread : public QThread
{
    Q_OBJECT
public:
    explicit ProxyThread(int socketDescriptor = -1,
                         QObject *parent = 0);

protected:
    void run();

private:
    QTcpSocket *socket_;
    int socketDescriptor_;

private slots:
    void slotReadyRead();

signals:
    void read(const QString &message);
};

