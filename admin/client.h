#pragma once
#include <QObject>
#include <QString>

class Client: public QObject
{
    Q_OBJECT
public:

private:
    QString clientIdHash;
    qint32 clientId;
};
