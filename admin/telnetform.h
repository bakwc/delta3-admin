#pragma once

#include <QDialog>
#include <QTextCursor>
#include <QColor>
#include <QPalette>
#include <QKeyEvent>
#include <QEvent>
#include <QObject>
#include "network.h"
#include "defines.h"

namespace Ui {
class TelnetForm;
}

class TelnetForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit TelnetForm(
            Network *network,
            qint32 clientId,
            QWidget* parent = 0);
    ~TelnetForm();
    
private slots:
    void onDataReceived();

private:
    bool eventFilter(QObject* _o, QEvent* _e);

private:
    void textScrollDown();
private:
    Network *network_;
    qint32 clientId_;
    Ui::TelnetForm *ui;
    QString currentCmd_;
    QString history_;
};

