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
            Network *network,
            qint16 clientId,
            QWidget* parent = 0);
    ~GraphForm();
    





private:
    void mouseReleaseEvent(QMouseEvent *me);
    void mouseDoubleClickEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *pKeyEvent);
    void mousePressEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);
    // Хранит сжатую картинку в байтах.
    QByteArray bytePicIn;
    // Содержит захваченый принтскрин экрана
    QPixmap picIn;
    // На нее добавляется картинка перед отрисовкой.
    // Используется для посылок сообщений.
    Network *network_;
    // Айди клиента
    qint16 clientId_;
    // Сама формочка
    Ui::GraphForm *ui;
private slots:
    // Обрабатывает входящие данные.
    void onDataReceived();
};

