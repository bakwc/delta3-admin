#include "telnetform.h"
#include "ui_telnetform.h"

TelnetForm::TelnetForm(
        Network *network, qint16 clientId, QWidget *parent) :
    QWidget(parent),
    network_(network),
    clientId_(clientId),
    ui(new Ui::TelnetForm)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("telnet - ") + network_->getClientName(clientId_));
    network_->activateMode(clientId_, MOD_TELNET);
    this->setFixedSize(this->size());
    connect(network_,SIGNAL(dataIncome()),
            this,SLOT(onDataReceived()));

    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    ui->textEdit->setPalette(p);

    ui->textEdit->installEventFilter(this);
    //ui->textEdit->setTextColor(Qt::green);
    //ui->lineEdit->
}

TelnetForm::~TelnetForm()
{
    network_->deactivateMode(clientId_, MOD_TELNET);
    delete ui;
}

void TelnetForm::onDataReceived()
{
    if (!(network_->receivedData().from == clientId_ &&
            network_->receivedData().mode == MOD_TELNET))
        return;
    qDebug() << "TelnetForm::onDataReceived()";

    QString message = QString::fromUtf8(network_->receivedData().data);

    history_ += message;

    if (history_.length() > TELNET_HISTORY_LENGTH)
        history_=history_.right(TELNET_HISTORY_LENGTH);

   // ui->textEdit->append(message);
    ui->textEdit->setText(history_);
    textScrollDown();
}

bool TelnetForm::eventFilter(QObject* _o, QEvent* _e)
{
    if(_e->type() == QEvent::KeyPress)
    {
        QKeyEvent* eventKey = static_cast<QKeyEvent*>(_e);

        if(eventKey->key() == Qt::Key_Shift ||
           eventKey->key() == Qt::Key_Control ||
           eventKey->key() == Qt::Key_Alt)
            return true;

        if(eventKey->key() == Qt::Key_Return)
        {
            qDebug() << "pressed enter!";
            network_->sendLevelTwo(clientId_, MOD_TELNET,
                                   currentCmd_.toUtf8());
            currentCmd_.clear();

            return true;
        }

        if(eventKey->key() == Qt::Key_Backspace)
        {
            if (currentCmd_.isEmpty()) return true;
            currentCmd_=currentCmd_.left(currentCmd_.size()-1);
            ui->textEdit->setText(history_+currentCmd_);
            textScrollDown();
            return true;
        }

            qint32 key = eventKey->key();

            if ( ! (eventKey->modifiers() == Qt::ShiftModifier ))
                key=tolower(key);

            currentCmd_+=QChar(key);

            ui->textEdit->setText(history_+currentCmd_);
            textScrollDown();
            return true;

    }
    return QWidget::eventFilter(_o, _e);
}


void TelnetForm::textScrollDown()
{
    QTextCursor c =  ui->textEdit->textCursor();
    c.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(c);
}
