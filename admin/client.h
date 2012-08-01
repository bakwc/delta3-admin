#pragma once
#include <QObject>
#include <QString>
#include <QDebug>
#include <QHostAddress>

#if defined(DELTA3_ADMIN_LIBRARY)
#   define DELTA3_EXPORT Q_DECL_EXPORT
#else
#   define DELTA3_EXPORT Q_DECL_IMPORT
#endif

namespace delta3 {

class DELTA3_EXPORT Client: public QObject
{
    Q_OBJECT
public:
    Client(QObject *parent);
    QString getHash() const;
    qint32  getId() const;
    QString getOs() const;
    QString getDevice() const;
    QString getCaption() const;
    QString getIp() const;

    void setHash(const QByteArray& hash);
    void setId(qint16 id);
    void setOs(const QString& os);
    void setDevice(const QString& device);
    void setCaption(const QString& caption);
    void setIp(qint32 ip);
private:
    QString idHash_;
    qint32 id_;
    QString os_;
    QString device_;
    QString caption_;
    QHostAddress ip_;
};

}
