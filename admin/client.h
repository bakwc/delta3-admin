#pragma once
#include <QObject>
#include <QString>
#include <QDebug>

class Client: public QObject
{
    Q_OBJECT
public:
    Client(QObject *parent);
    QString getHash() const;
    qint32 getId() const;
    QString getOs() const;
    void setHash(const QByteArray& hash);
    void setId(qint16 id);
    void setOs(const QString& os);
    void setDevice(const QString& device);
    void setCaption(const QString& caption);
private:
    QString idHash_;
    qint32 id_;
    QString os_;
    QString device_;
    QString caption_;
};
