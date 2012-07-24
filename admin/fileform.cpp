#include "fileform.h"
#include "ui_fileform.h"
#include <QStandardItemModel>
#include <QStandardItem>

FileForm::FileForm(Network *_network, qint16 _clientId, QWidget *parent) :
    QWidget(parent),
    network_(_network),
    clientId_(_clientId),
    ui(new Ui::FileForm),
    _dirsAndFiles(new QStringList())
{
     ui->setupUi(this);
     connect(network_, SIGNAL(dataIncome()),
                 this, SLOT(onDataReceived()));
}


FileForm::~FileForm()
{
    delete ui;
    delete _dirsAndFiles;
}


void FileForm::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == MOD_FILE))
        return;

    parseData(&network_->receivedData().data);
}

void FileForm::parseData(const QByteArray *_incomingData)
{
    QString dataString(*_incomingData);
    QStringList parsedData = dataString.split(":");

    if (parsedData[0]=="file")
    {
        //Sending and geting file logic should be here.
    }
    else
        if(parsedData[0]=="dir")
        {
            _directoryName=parsedData[1];

            for(int i=2;i<parsedData.size()-1;i++)
                _dirsAndFiles->push_back(parsedData.at(i));
        }
        else
            return;



}

void FileForm::showFileTree()
{
    QStandardItemModel myModel(_dirsAndFiles->size(),1,this);
    for(int i=0;i<_dirsAndFiles->size()-1;++i)
    {
        QStandardItem *item=new QStandardItem(_dirsAndFiles->at(i));
        myModel.appendRow(item);
        delete item;
    }
    ui->listView->setModel(&myModel);
}
