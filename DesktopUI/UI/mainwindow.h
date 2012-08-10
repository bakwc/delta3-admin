#pragma once

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTextCodec>
#include <QPoint>
#include <QMenu>
#include <QSystemTrayIcon>
#include "network.h"
#include "telnetform.h"
#include "graphform.h"
#include "fileform.h"
#include "clientinfodialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(delta3::Network *net = NULL,
                        QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setNetwork(delta3::Network *net);

private slots:
    void on_actionConnect_activated();
    void onRedraw();

    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void runTelnet();
    void runGraph();
    void runFile();
    void runProxy();
	void runOptions();
    void ShowHide();

private:
    bool isClientExist(QListWidget *wdg, qint32 id);
    void smartClear(QListWidget* wdg, delta3::Clients clients);
    bool isIdExist(const QListWidgetItem *item, delta3::Clients &clients);
    void createTrayIcon();
    void timerEvent(QTimerEvent *);

private:
    Ui::MainWindow  *ui;
	delta3::Network *network_;
    QMenu           *modeMenu_;
    QSystemTrayIcon *trayIcon;
};
