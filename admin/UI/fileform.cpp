#include "fileform.h"
#include "ui_fileform.h"

namespace delta3{
FileForm::FileForm(delta3::File *file, QWidget *parent) :
    QWidget(parent),
	file_(file),
    ui(new Ui::FileForm)
{
     ui->setupUi(this);
}


FileForm::~FileForm()
{
	delete ui;
}


void FileForm::onDataReceived(QString &d)
{
}
}
