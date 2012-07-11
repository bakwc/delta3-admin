#include "telnetform.h"
#include "ui_telnetform.h"

TelnetForm::TelnetForm(
        Network *network, qint32 clientId, QWidget *parent) :
    QWidget(parent),
    network_(network),
    clientId_(clientId),
    ui(new Ui::TelnetForm)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("telnet - ")+network_->getClientName(clientId_));
    network_->activateMode(clientId_,MOD_TELNET);
    this->setFixedSize(this->size());
    connect(network_,SIGNAL(dataIncome()),
            this,SLOT(onDataReceived()));
}

TelnetForm::~TelnetForm()
{
    network_->deactivateMode(clientId_,MOD_TELNET);
    delete ui;
}

void TelnetForm::on_lineEdit_returnPressed()
{
    network_->sendLevelTwo(clientId_,MOD_TELNET,
                           ui->lineEdit->text().toLocal8Bit());
    ui->lineEdit->clear();
}

void TelnetForm::onDataReceived()
{
    if (!(network_->receivedData().from==clientId_ &&
            network_->receivedData().mode==MOD_TELNET))
        return;
    qDebug() << "onDataReceived:" << network_->receivedData().data;

    ui->textEdit->append(network_->receivedData().data);
}
