#ifndef CLIENTINFODIALOG_H
#define CLIENTINFODIALOG_H

#include <QDialog>
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
    
private:
    Ui::ClientInfoDialog *ui;
    Network *network_;
};

#endif // CLIENTINFODIALOG_H
