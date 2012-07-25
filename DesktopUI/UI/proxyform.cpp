#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include "proxyform.h"
#include "ui_proxyform.h"

ProxyForm::ProxyForm(delta3::Proxy *proxy, QWidget *parent) :
    QWidget(parent), _proxy(proxy),
    ui(new Ui::ProxyForm)
{
    ui->setupUi(this);

    _proxyServer = new QTcpServer;
    _proxyServer->listen(QHostAddress::Any, 8080);
    connect(_proxy, SIGNAL(ready(QString&)), SLOT(onDataReceived(QString&)));
    connect(this, SIGNAL(ready(QString&)), _proxy, SLOT(onReady(QString&)));
    connect(_proxyServer, SIGNAL(newConnection()), SLOT(slotNewConnection()));

}

ProxyForm::~ProxyForm()
{
    delete ui;
}

void ProxyForm::onDataReceived(QString &str)
{
    //TODO: inSocket->write(QByteArray(str));
    qDebug() << str;
}

void ProxyForm::slotNewConnection()
{
    qDebug() << "ProxyForm::slotNewConnection";
}
