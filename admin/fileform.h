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
            Network *_network=0,
            qint16 _clientId=0,
            QWidget* parent = 0);
    ~FileForm();
    
private:
    Network *network_;
    qint16 clientId_;
    Ui::FileForm *ui;

    QString _directoryName;
    QStringList* _dirsAndFiles;

    void parseData(const QByteArray* _incomingData);
    void showFileTree();

private slots:
    void onDataReceived();
};
