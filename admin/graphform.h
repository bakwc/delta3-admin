#pragma once

#include <QWidget>
#include "network.h"

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
    Network *network_;
    qint16 clientId_;
    Ui::GraphForm *ui;
};

