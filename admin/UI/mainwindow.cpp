#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	network_ = new delta3::Network(this);
    connect(network_,SIGNAL(listUpdated()),
            this,SLOT(onRedraw()));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    QAction *act;
    modeMenu_ = new QMenu(this);

    act = new QAction(tr("Telnet mode"),this);
    connect(act,SIGNAL(triggered()),this,SLOT(runTelnet()));
    modeMenu_->addAction(act);

    act = new QAction(tr("File mode"),this);
    connect(act,SIGNAL(triggered()),this,SLOT(runFile()));
    modeMenu_->addAction(act);

    act = new QAction(tr("Graphics mode"),this);
    connect(act,SIGNAL(triggered()),this,SLOT(runGraph()));
    modeMenu_->addAction(act);

    modeMenu_->addSeparator();

    act = new QAction(tr("Options"),this);
    connect(act,SIGNAL(triggered()),this,SLOT(runOptions()));
    modeMenu_->addAction(act);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_activated()
{
    network_->connectToServer();
}

void MainWindow::onRedraw()
{
    qDebug() << "onRedraw()";
    QListWidget *list=ui->listWidget;
    QListWidgetItem *item;
    list->clear();
	for(auto i = network_->getClients().begin();
			 i != network_->getClients().end(); i++)
    {
        item = new QListWidgetItem(i.value()->getOs() );
        item->setWhatsThis(QString("%1")
                        .arg( i.value()->getId() ));
        list->addItem(item);
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug() << "Double Click!";
    runTelnet();
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    qDebug() << "Context Menu!";
    if (ui->listWidget->selectedItems().size()==0)
        return;
   // modeMenu_->raise();
    modeMenu_->move(QCursor::pos());
    modeMenu_->show();
}

void MainWindow::runTelnet()
{
    if (ui->listWidget->selectedItems().size()==0)
        return;
    QListWidgetItem *item=ui->listWidget->selectedItems()[0];

	static TelnetForm* telnet = nullptr;

	if(telnet)
		delete telnet;

	telnet = new TelnetForm( network_, item->whatsThis().toInt());
    telnet->show();
}

void MainWindow::runGraph()
{
    if (ui->listWidget->selectedItems().size()==0)
        return;
    QListWidgetItem *item=ui->listWidget->selectedItems()[0];

	static GraphForm *graph = nullptr;

	if(graph)
		delete graph;

	graph = new GraphForm( network_, item->whatsThis().toInt());
    graph->show();
}

void MainWindow::runFile()
{
    if (ui->listWidget->selectedItems().size()==0)
        return;
    QListWidgetItem *item=ui->listWidget->selectedItems()[0];
    FileForm *file = new FileForm(
                network_,
                item->whatsThis().toInt());
            // REVIEW: potential memory leak?
    file->show();
}


void MainWindow::runOptions()
{
    if (ui->listWidget->selectedItems().size()==0)
        return;

    QListWidgetItem *item=ui->listWidget->selectedItems()[0];

    qint16 clientId=item->whatsThis().toInt();

    ClientInfoDialog dialog(clientId,network_);
    if (dialog.exec()!=ClientInfoDialog::Rejected)
    {
        network_->setClientCaption(clientId,dialog.getCaption());
    }

    /*
    FileForm *file = new FileForm(
                network_,
                item->whatsThis().toInt());
            // REVIEW: potential memory leak?
    file->show();
    */
}
