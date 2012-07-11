#include "telnetform.h"
#include "ui_telnetform.h"

TelnetForm::TelnetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TelnetForm)
{
    ui->setupUi(this);
}

TelnetForm::~TelnetForm()
{
    delete ui;
}

void TelnetForm::on_lineEdit_returnPressed()
{
    //TODO: send cmd to server
}
