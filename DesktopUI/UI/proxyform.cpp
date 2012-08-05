#include "Protocols/proxy.h"
#include "proxyform.h"
#include "ui_proxyform.h"

ProxyForm::ProxyForm(delta3::Proxy *proxy, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProxyForm)
{
    ui->setupUi(this);

    _proxy = proxy;
    ui->spinBox->setRange(1, 65535);
    ui->spinBox->setValue(8080);
    ui->pushButton->setCheckable(true);
    ui->pushButton->setChecked(false);
    ui->pushButton->setText("start");

    ui->label->setText(trUtf8("Укажите в браузере прокси"));
    ui->label_2->setText("127.0.0.1:");
    ui->label_2->setAlignment(Qt::AlignRight);
}

ProxyForm::~ProxyForm()
{
    delete ui;
}

void ProxyForm::on_pushButton_clicked(bool checked)
{
    if(checked){
        _proxy->start(ui->spinBox->value());
        ui->pushButton->setText("stop");
        ui->pushButton->setChecked(true);
    } else {
        _proxy->stop();
        ui->pushButton->setChecked(false);
        ui->pushButton->setText("start");
    }
}
