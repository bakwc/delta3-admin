#pragma once

#include <QWidget>
#include "network.h"
#include <QGraphicsScene>
namespace Ui {
class GraphForm;
}

class GraphForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit GraphForm(
            Network *network,
            qint16 clientId,
            QWidget* parent = 0);
    ~GraphForm();
    
private:
    QByteArray bytePicIn;
    QPixmap picIn;
    QGraphicsScene scene;
    Network *network_;
    qint16 clientId_;
    Ui::GraphForm *ui;
private slots:
    void onDataReceived();
};

