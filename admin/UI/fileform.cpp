#include "fileform.h"
#include "ui_fileform.h"

FileForm::FileForm(delta3::Network *network, qint16 clientId, QWidget *parent) :
    QWidget(parent),
    network_(network),
    clientId_(clientId),
    ui(new Ui::FileForm)
{
     ui->setupUi(this);
}


FileForm::~FileForm()
{
    delete ui;
}
