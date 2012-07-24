#include "clientinfodialog.h"
#include "ui_clientinfodialog.h"

namespace delta3{
ClientInfoDialog::ClientInfoDialog(qint16 clientId, delta3::Network *net, QWidget *parent) :
    QDialog(parent),
    network_(net),
    ui(new Ui::ClientInfoDialog)
{
    ui->setupUi(this);
    ui->fieldOS->setText(network_->getClient(clientId)->getOs());
    ui->fieldHash->setText(network_->getClient(clientId)->getHash());
    ui->fieldDevice->setText(network_->getClient(clientId)->getDevice());
    ui->fieldCaption->setText(network_->getClient(clientId)->getCaption());
    ui->fieldIp->setText(network_->getClient(clientId)->getIp());
}

ClientInfoDialog::~ClientInfoDialog()
{
    delete ui;
}

QString ClientInfoDialog::getCaption()
{
    return ui->fieldCaption->text();
}
}
