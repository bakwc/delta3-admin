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
}

TelnetForm::~TelnetForm()
{
    network_->deactivateMode(clientId_,MOD_TELNET);
    delete ui;
}

void TelnetForm::on_lineEdit_returnPressed()
{
    //TODO: send cmd to server
}
