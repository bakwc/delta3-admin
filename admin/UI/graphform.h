#pragma once

#include <QWidget>
#include "network.h"
#include "defines.h"
#include "Protocols/graphics.h"

namespace Ui {
class GraphForm;
}

class GraphForm : public QWidget
{
    Q_OBJECT
    
public:
	explicit GraphForm(delta3::Graphics* graph, QWidget* parent = 0);
    ~GraphForm();

signals:
	void ready(QByteArray &arr);

private slots:
	void onDataReceived(QImage &img);

protected:
	void paintEvent(QPaintEvent *);
	bool eventFilter(QObject* _o, QEvent* _e);

private:
	delta3::Graphics	*graph_;
	QImage				image_; // mb it's a not very well idea ;|
	Ui::GraphForm		*ui;
};

