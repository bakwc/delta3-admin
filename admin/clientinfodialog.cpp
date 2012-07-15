#include "clientinfodialog.h"
#include "ui_clientinfodialog.h"

ClientInfoDialog::ClientInfoDialog(qint16 clientId, Network *net, QWidget *parent) :
    QDialog(parent),
    network_(net),
    ui(new Ui::ClientInfoDialog)
{
    ui->setupUi(this);
    ui->fieldOS->setText(network_->getClient(clientId)->getOs());
    ui->fieldHash->setText(network_->getClient(clientId)->getHash());
    ui->fieldDevice->setText(network_->getClient(clientId)->getDevice());
    ui->fieldCaption->setText(network_->getClient(clientId)->getCaption());
}

ClientInfoDialog::~ClientInfoDialog()
{
    delete ui;
}
