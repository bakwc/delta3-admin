#include "fileform.h"
#include "ui_fileform.h"
#include <QIcon>
#include <QInputDialog>

FileForm::FileForm(delta3::File *file, QWidget *parent) :
    QWidget(parent),
	file_(file),
    ui(new Ui::FileForm)
{
     ui->setupUi(this);

     connect(file_,SIGNAL(dir(QVector<QStringList>)),
             this,SLOT(onDirListReceived(QVector<QStringList>)));

     connect(this,SIGNAL(requestDir()),
             file_,SLOT(requestDir()));

     connect(this,SIGNAL(requestFile(QString&)),
            file_,SLOT(requestFile(QString&)));

     connect(this, SIGNAL(command(delta3::File::FileMode,QString,QString)),
             file_, SLOT(onCommand(delta3::File::FileMode,QString,QString)));

     connect(this, SIGNAL(setDirUp()), file_, SLOT(setDirUp()));

     connect(this, SIGNAL(setCurrentDir(const QString&)),
             file_, SLOT(setCurrentDir(const QString&)));

     connect(this, SIGNAL(openDir(const QString&)),
            file_, SLOT(openDir(const QString&)));

     connect(file_, SIGNAL(dirChanged(QString&)),this, SLOT(onDirChanged(QString&)));

     //connect(file_, SIGNAL(ready(QString&)), SLOT(onDataReceived(QString&)));
     //connect(this, SIGNAL(ready(QString&)), file_, SLOT(onReady(QString&)));

	 setAttribute(Qt::WA_DeleteOnClose);

     this->setWindowTitle(tr("File Browser - ")+file_->getClientCaption());


     ui->lineEdit->setText("/");
     emit requestDir();

     QAction* act = new QAction("Rename", this);
     connect(act, SIGNAL(triggered()), SLOT(rename()));
     menu_.addAction(act);
}


FileForm::~FileForm()
{
    //delete ui;
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
            item->setWhatsThis("folder");
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
            item->setWhatsThis("file");
            ui->listWidget->addItem(item);
        }
    }
}


void FileForm::on_pushButton_clicked()
{
    QString absDir=ui->lineEdit->text();
    emit setCurrentDir(absDir);
    emit requestDir();
}


void FileForm::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if (item->whatsThis()=="folder")
    {
        if (item->text()==".")
            emit setCurrentDir("/");
        else if (item->text()=="..")
        {
            emit setDirUp();
            /*
            if (_cd.count("/")>1)
            {
                _cd.chop(1);
                auto n=_cd.lastIndexOf("/");
                qDebug() << n;
                _cd=_cd.left(n+1);
            }*/
        }
        else
            emit openDir(item->text());
            //_cd+=item->text()+"/";

        //ui->lineEdit->setText(_cd);
        emit requestDir();
    } if (item->whatsThis()=="file")
    {
        QString fname=item->text();
        qDebug() << "request sended" << fname;
        emit requestFile(fname);
    }
}


void FileForm::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    if (ui->listWidget->selectedItems().isEmpty())
        return;

    menu_.move(QCursor::pos());
    menu_.show();
}


void FileForm::rename()
{
    QString newName = QInputDialog::getText(0, "Rename", "New name:");

    if (!newName.isEmpty()) {
        emit command(delta3::File::FMOD_RENAME, ui->listWidget->currentItem()->text(), newName);
        ui->listWidget->currentItem()->setText(newName);
    }
}

void FileForm::onDirChanged(QString &cd)
{
    ui->lineEdit->setText(cd);
}
