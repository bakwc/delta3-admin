#include <QDebug>
#include "proxyform.h"
#include "ui_proxyform.h"

ProxyForm::ProxyForm(delta3::Proxy *proxy, QWidget *parent) :
    QWidget(parent), _proxy(proxy),
    ui(new Ui::ProxyForm)
{
    ui->setupUi(this);
}

ProxyForm::~ProxyForm()
{
    delete ui;
}
