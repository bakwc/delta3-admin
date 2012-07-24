#include <QApplication>
#include "UI/mainwindow.h"
#include "network.h"
#include "Protocols/telnet.h"
#include "UI/telnetform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	delta3::Network network;//(QHostAddress("193.169.33.254"));

    delta3::MainWindow w(&network);
    w.show();
    
    return a.exec();
}
