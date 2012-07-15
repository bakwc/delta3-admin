#pragma once

#include <QWidget>
#include "network.h"

namespace Ui {
class FileForm;
}

class FileForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit FileForm(
            Network *network,
            qint16 clientId,
            QWidget* parent = 0);
    ~FileForm();
    
private:
    Network *network_;
    qint16 clientId_;
    Ui::FileForm *ui;
};
