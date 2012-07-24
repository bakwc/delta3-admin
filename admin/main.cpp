#include <QApplication>
#include "UI/mainwindow.h"
#include "network.h"
#include "Protocols/telnet.h"
#include "UI/telnetform.h"

void runTelnet(delta3::Network *n, qint16 c) {
	delta3::Telnet* net = new delta3::Telnet(n, c);
	TelnetForm* form = new TelnetForm(net);
	form->show();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	delta3::Network network;

	MainWindow w(&network);
	w.runTelnet_ = &runTelnet;
    w.show();
    

    return a.exec();
}
