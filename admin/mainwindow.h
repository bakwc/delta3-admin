#pragma once

#include <QMainWindow>
#include "network.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionConnect_activated();

private:
    Ui::MainWindow *ui;
    Network *network_;
};
