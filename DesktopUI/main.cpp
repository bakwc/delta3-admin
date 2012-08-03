#include <QApplication>
#include "UI/mainwindow.h"
#include "network.h"
#include "Protocols/telnet.h"
#include "UI/telnetform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    delta3::Network network(QHostAddress("46.247.149.149"));

	MainWindow w(&network);
    w.show();

    a.setQuitOnLastWindowClosed(false);
    
    return a.exec();
}
