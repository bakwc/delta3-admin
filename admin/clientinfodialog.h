#pragma once

#include <QDialog>
#include <QString>
#include "client.h"
#include "network.h"

namespace Ui {
class ClientInfoDialog;
}

class ClientInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ClientInfoDialog(qint16 clientId, Network *net, QWidget *parent = 0);
    ~ClientInfoDialog();
    QString getCaption();
    
private:
    Network *network_;
    Ui::ClientInfoDialog *ui;
};
