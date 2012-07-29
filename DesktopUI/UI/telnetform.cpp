#include "telnetform.h"
#include "ui_telnetform.h"

TelnetForm::TelnetForm(delta3::Telnet *tel, QWidget *parent) :
	QWidget(parent), tel_(tel), ui(new Ui::TelnetForm)
{
    ui->setupUi(this);

	connect(tel_, SIGNAL(ready(QString&)), SLOT(onDataReceived(QString&)));
	connect(this, SIGNAL(ready(QString&)), tel_, SLOT(onReady(QString&)));

    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    ui->textEdit->setPalette(p);

    ui->textEdit->installEventFilter(this);

	setAttribute(Qt::WA_DeleteOnClose);

    this->setWindowTitle("telnet - "+tel_->getClientCaption());

    auto fmt = ui->textEdit->currentCharFormat();
    fmt.setFontFixedPitch(true);
    fmt.setFontStyleHint(QFont::Monospace);
    fmt.setFontFamily("monospace");
    ui->textEdit->setCurrentCharFormat(fmt);
}

TelnetForm::~TelnetForm()
{
    delete ui;
}

void TelnetForm::onDataReceived(QString &str)
{

	history_ += str;

	if (history_.length() > delta3::TELNET_HISTORY_LENGTH)
		history_=history_.right(delta3::TELNET_HISTORY_LENGTH);

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
//			network_->sendLevelTwo(clientId_, delta3::MOD_TELNET,
//                                   currentCmd_.toUtf8());

			emit ready(currentCmd_);

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
