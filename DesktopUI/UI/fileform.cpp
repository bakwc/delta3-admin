#include "fileform.h"
#include "ui_fileform.h"
#include <QIcon>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>

FileForm::FileForm(delta3::File *file, QWidget *parent) :
    QWidget(parent),
    _file(file),
    ui(new Ui::FileForm)
{
     ui->setupUi(this);

     _dialog = new QFileDialog(this);

     connect(_file,SIGNAL(dir(QVector<QStringList>)),
             this,SLOT(onDirListReceived(QVector<QStringList>)));

     connect(this,SIGNAL(requestDir()),
             _file,SLOT(requestDir()));

     connect(this,SIGNAL(requestFile(QString&,QString&)),
            _file,SLOT(requestFile(QString&,QString&)));

     connect(this, SIGNAL(command(delta3::File::FileMode,QString,QString)),
             _file, SLOT(onCommand(delta3::File::FileMode,QString,QString)));

     connect(this, SIGNAL(setDirUp()), _file, SLOT(setDirUp()));

     connect(this, SIGNAL(setCurrentDir(const QString&)),
             _file, SLOT(setCurrentDir(const QString&)));

     connect(this, SIGNAL(openDir(const QString&)),
            _file, SLOT(openDir(const QString&)));

     connect(_file, SIGNAL(dirChanged(QString&)),
             this, SLOT(onDirChanged(QString&)));

     connect(_file, SIGNAL(fileReceived(QString)),
             this, SLOT(onFileReceived()));

     //connect(file_, SIGNAL(ready(QString&)), SLOT(onDataReceived(QString&)));
     //connect(this, SIGNAL(ready(QString&)), file_, SLOT(onReady(QString&)));

	 setAttribute(Qt::WA_DeleteOnClose);

     this->setWindowTitle(tr("File Browser - ")+_file->getClientCaption());


     ui->lineEdit->setText("/");
     emit requestDir();

     QAction* act = new QAction("Rename", this);
     connect(act, SIGNAL(triggered()), SLOT(rename()));
     _menu.addAction(act);
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


void FileForm::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if (item->whatsThis()=="folder")
    {
        if (item->text()==".")
            emit setCurrentDir("/");
        else if (item->text()=="..")
        {
            emit setDirUp();
        }
        else
            emit openDir(item->text());
        emit requestDir();
    } if (item->whatsThis()=="file")
    {

        QString remoteFileName=item->text();
        QString localFileName=_dialog->getSaveFileName
                (this,tr("Save file as"),remoteFileName,tr("All Files (*)"));
        if (!localFileName.isEmpty())
        {
            qDebug() << "request sended" << remoteFileName;
            emit requestFile(remoteFileName, localFileName);
        }
    }
}


void FileForm::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    if (ui->listWidget->selectedItems().isEmpty())
        return;

    _menu.move(QCursor::pos());
    _menu.show();
}


void FileForm::rename()
{
    QString newName = QInputDialog::getText(0, "Rename", "New name:");

    if (!newName.isEmpty()) {
        emit command(delta3::File::FMOD_RENAME, ui->listWidget->currentItem()->text(), newName);
        ui->listWidget->currentItem()->setText(newName);
    }
}

void FileForm::onFileReceived()
{
    QMessageBox::information(0, tr("Finished"), tr("File received!"));
}

void FileForm::onDirChanged(QString &cd)
{
    ui->lineEdit->setText(cd);
}

void FileForm::on_buttonChangeDir_clicked()
{
    QString absDir=ui->lineEdit->text();
    emit setCurrentDir(absDir);
    emit requestDir();
}
