#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Protocols/graphics.h"
#include "Protocols/proxy.h"
#include "proxyform.h"
#include <QTimerEvent>

MainWindow::MainWindow(delta3::Network *net, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(net)
        setNetwork(net);

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

    act = new QAction(tr("Proxy mode"),this);
    connect(act,SIGNAL(triggered()),this,SLOT(runProxy()));
    modeMenu_->addAction(act);

    act = new QAction(tr("Graphics mode"),this);
    connect(act,SIGNAL(triggered()),this,SLOT(runGraph()));
    modeMenu_->addAction(act);

	modeMenu_->addSeparator();

	act = new QAction(tr("Options"),this);
	connect(act,SIGNAL(triggered()),this,SLOT(runOptions()));
	modeMenu_->addAction(act);

    createTrayIcon();

    startTimer(1000);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setNetwork(delta3::Network *net)
{
    if(network_)
        disconnect(this);

    network_ = net;

    connect(network_,SIGNAL(listUpdated()),
            this,SLOT(onRedraw()));

}


void MainWindow::on_actionConnect_activated()
{
    if(network_ == NULL)
        return;
    qDebug() << "connecting to server";
    network_->connectToServer();
}


void MainWindow::onRedraw()
{
    QListWidget *list=ui->listWidget;
    QListWidgetItem *item;

    const delta3::Clients &clients = network_->getClients();

    for (auto i = clients.begin(); i != clients.end(); i++)
        if ( !isClientExist(list, i.value()->getId()) ) {
            item = new QListWidgetItem(i.value()->getCaption());
            item->setWhatsThis( QString::number(i.value()->getId()) );
            list->addItem(item);
        }

    smartClear(list, clients);
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
	runTelnet();
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    if (ui->listWidget->selectedItems().size()==0)
        return;

    modeMenu_->move(QCursor::pos());
    modeMenu_->show();
}


void MainWindow::runTelnet()
{
    QListWidgetItem *item = NULL;

    if ((item = ui->listWidget->selectedItems()[0]) == NULL)
        return;

    delta3::Telnet *tel = new delta3::Telnet(network_, item->whatsThis().toInt());
    TelnetForm *form = new TelnetForm(tel);
	tel->setParent(form);
	form->show();
}


void MainWindow::runGraph()
{
    QListWidgetItem *item = NULL;

    if ((item = ui->listWidget->selectedItems()[0]) == NULL)
        return;

    delta3::Graphics *graph = new delta3::Graphics(network_,item->whatsThis().toInt());
    GraphForm *form = new GraphForm(graph);
	graph->setParent(form);
	form->show();
}

void MainWindow::runFile()
{
    QListWidgetItem *item = NULL;

    if ((item = ui->listWidget->selectedItems()[0]) == NULL)
        return;

    delta3::File *file = new delta3::File(network_,item->whatsThis().toInt());
    FileForm *form = new FileForm(file);
    file->setParent(form);
    form->show();
}


void MainWindow::runOptions()
{
    QListWidgetItem *item = NULL;

    if ((item = ui->listWidget->selectedItems()[0]) == NULL)
        return;

    ClientInfoDialog dialog(item->whatsThis().toInt(), network_);
    if (dialog.exec() != ClientInfoDialog::Rejected)
    {
		network_->setClientCaption(item->whatsThis().toInt(), dialog.getCaption());
        item->setText(dialog.getCaption());
    }
}


void MainWindow::ShowHide()
{
    if(isHidden())
        show();
    else
        hide();
}


bool MainWindow::isClientExist(QListWidget *wdg, qint32 id)
{
    for (int i = 0; i != wdg->count(); ++i)
        if(wdg->item(i)->whatsThis().toInt() == id)
            return true;

    return false;
}


void MainWindow::smartClear(QListWidget *wdg, delta3::Clients clients)
{
    for (int i = 0; i < wdg->count(); ++i)
        if ( !isIdExist(wdg->item(i), clients) )
            wdg->takeItem(i);
}


bool MainWindow::isIdExist(const QListWidgetItem *item, delta3::Clients &clients)
{
    for (auto it = clients.begin(); it != clients.end(); ++it)
        if ( item->whatsThis().toInt() == it.value()->getId() ) {
            clients.remove(it.key());
            return true;
        }

    return false;
}


void MainWindow::createTrayIcon()
{
    QAction *action;
    this->setWindowIcon(QIcon(":/icon.ico"));

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon(":/icon.ico"));
    trayIcon->show();

    QMenu *menu = new QMenu(this);

    action = new QAction("Show/Hide",this);
    connect(action, SIGNAL(triggered()), this, SLOT(ShowHide()));
    menu->addAction(action);

    menu->addSeparator();

    action = new QAction("About Delta3", this);
    connect(action, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    menu->addAction(action);

    menu->addSeparator();

    action = new QAction("Exit",this);
    connect(action, SIGNAL(triggered()), qApp, SLOT(quit()));
    menu->addAction(action);

    trayIcon->setContextMenu(menu);
}


void MainWindow::timerEvent(QTimerEvent *ev)
{
    onRedraw();

    ev->accept();
}


void MainWindow::runProxy()
{
    QListWidgetItem *item = NULL;

    if ((item = ui->listWidget->selectedItems()[0]) == NULL)
        return;
    delta3::Proxy *_proxy = new delta3::Proxy(network_, item->whatsThis().toInt());
    ProxyForm *_form = new ProxyForm(_proxy);
    _form->show();
}
