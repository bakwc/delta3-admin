#pragma once

#include <QMainWindow>
#include <QListWidgetItem>
#include <QTextCodec>
#include <QPoint>
#include <QMenu>
#include "network.h"
#include "telnetform.h"
#include "graphform.h"
#include "fileform.h"
#include "clientinfodialog.h"

namespace Ui {
class MainWindow;
}

namespace delta3{
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(Network *net = NULL,
						QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void setNetwork(Network *net);

private slots:
    void on_actionConnect_activated();
    void onRedraw();

    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_customContextMenuRequested(const QPoint &pos);

	void runTelnet();
	void runGraph();
//    void runFile();
	void runOptions();

private:
    Ui::MainWindow *ui;
    Network *network_;
    QMenu *modeMenu_;
};
}
