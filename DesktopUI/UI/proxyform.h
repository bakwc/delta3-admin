#pragma once

#include <QWidget>
#include "Protocols/proxy.h"

class QTcpSocket;
class QTcpServer;

namespace Ui {
class ProxyForm;
}

class ProxyForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProxyForm(delta3::Proxy *proxy, QWidget *parent = 0);
    ~ProxyForm();

private:
    delta3::Proxy *_proxy;
    Ui::ProxyForm *ui;
    QTcpSocket *_inSocket;
    QTcpServer *_proxyServer;

signals:
    void ready(QString &str);

private slots:
    void slotNewConnection();
    void onDataReceived(QString &str);
};
