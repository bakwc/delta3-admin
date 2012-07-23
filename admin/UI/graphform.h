#pragma once

#include <QWidget>
#include "network.h"
#include "defines.h"
#include <QGraphicsScene>
namespace Ui {
class GraphForm;
}

class GraphForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit GraphForm(
			delta3::Network *network,
            qint16 clientId,
            QWidget* parent = 0);
    ~GraphForm();
    
private:
    bool eventFilter(QObject* _o, QEvent* _e);
    // Хранит сжатую картинку в байтах.
    QByteArray bytePicIn;
    // Содержит захваченый принтскрин экрана
    QPixmap picIn;
    // На нее добавляется картинка перед отрисовкой.
    QGraphicsScene scene;
    // Используется для посылок сообщений.
	delta3::Network *network_;
    // Айди клиента
    qint16 clientId_;
    // Сама формочка
    Ui::GraphForm *ui;
private slots:
    // Обрабатывает входящие данные.
    void onDataReceived();
};

