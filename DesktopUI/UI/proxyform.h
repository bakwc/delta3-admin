#pragma once
#include <QWidget>

namespace delta3{
class Proxy;
}

namespace Ui {
class ProxyForm;
}

class ProxyForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProxyForm(delta3::Proxy *proxy, QWidget *parent = 0);
    ~ProxyForm();

private slots:
    void on_pushButton_clicked(bool checked);

private:
    Ui::ProxyForm *ui;
    delta3::Proxy *_proxy;
};
