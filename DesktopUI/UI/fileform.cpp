#include "fileform.h"
#include "ui_fileform.h"
#include <QIcon>

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
    ui->listWidget->clear();
    QIcon folderIcon(":/Folder.png");
    QIcon fileIcon(":/File.png");

    for (auto i=dir.begin();i!=dir.end();i++)   // Directory display
    {
        QStringList l=*i;
        QListWidgetItem *item = new QListWidgetItem(l[0]);
        if (l[1]=="dir")
        {
            item->setIcon(folderIcon);
            ui->listWidget->addItem(item);
        }
    }

    for (auto i=dir.begin();i!=dir.end();i++)  // Files display
    {
        QStringList l=*i;
        QListWidgetItem *item = new QListWidgetItem(l[0]);
        if (l[1]=="file")
        {
            item->setIcon(fileIcon);
            ui->listWidget->addItem(item);
        }
    }
}

void FileForm::on_pushButton_clicked()
{
    QString dir=ui->lineEdit->text();
    emit requestDir(dir);
}
