#include "fileform.h"
#include "ui_fileform.h"

FileForm::FileForm(delta3::File *file, QWidget *parent) :
    QWidget(parent),
	file_(file),
    ui(new Ui::FileForm)
{
     ui->setupUi(this);

     connect(file_,SIGNAL(dir(QVector<QStringList>)),
             this,SLOT(onDirListReceived(QVector<QStringList>)));

     connect(this,SIGNAL(requestDir(QString&)),
             file_,SLOT(requestDir(QString&)));

     //connect(file_, SIGNAL(ready(QString&)), SLOT(onDataReceived(QString&)));
     //connect(this, SIGNAL(ready(QString&)), file_, SLOT(onReady(QString&)));

	 setAttribute(Qt::WA_DeleteOnClose);
}


FileForm::~FileForm()
{
	delete ui;
}


void FileForm::onDirListReceived(const QVector<QStringList> &dir)
{
    qDebug() << Q_FUNC_INFO;
    ui->textEdit->clear();
    for (auto i=dir.begin();i!=dir.end();i++)
    {
        QStringList l=*i;
        ui->textEdit->insertPlainText(l[0]+"\n");
    }
}

void FileForm::on_pushButton_clicked()
{
    QString dir=ui->lineEdit->text();
    emit requestDir(dir);
}
