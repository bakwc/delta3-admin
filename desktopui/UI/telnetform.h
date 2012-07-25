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
#include "Protocols/telnet.h"

namespace Ui {
class TelnetForm;
}

class TelnetForm : public QWidget
{
    Q_OBJECT
    
public:
	explicit TelnetForm(delta3::Telnet* tel, QWidget* parent = 0);
    ~TelnetForm();

signals:
	void ready(QString &str);

private slots:
	void onDataReceived(QString &str);

private:
    bool eventFilter(QObject* _o, QEvent* _e);
    void textScrollDown();

private:
	delta3::Telnet	*tel_;
	Ui::TelnetForm	*ui;
	QString			currentCmd_;
	QString			history_;
};

