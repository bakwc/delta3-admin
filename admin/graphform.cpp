#include "graphform.h"
#include "ui_graphform.h"

GraphForm::GraphForm(
        Network *network, qint16 clientId, QWidget *parent) :
    QWidget(parent),
    network_(network),
    clientId_(clientId),
    ui(new Ui::GraphForm)
{
    ui->setupUi(this);
}

GraphForm::~GraphForm()
{
    delete ui;
}
