#pragma once

#include <QDialog>
#include <QString>
#include "client.h"
#include "network.h"

namespace Ui {
class ClientInfoDialog;
}
namespace delta3{
class ClientInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
	explicit ClientInfoDialog(qint16 clientId, delta3::Network *net, QWidget *parent = 0);
    ~ClientInfoDialog();
    QString getCaption();
    
private:
	delta3::Network *network_;
    Ui::ClientInfoDialog *ui;
};
}
