#pragma once

#include <QWidget>

namespace Ui {
class TelnetForm;
}

class TelnetForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit TelnetForm(QWidget *parent = 0);
    ~TelnetForm();
    
private:
    Ui::TelnetForm *ui;
};

