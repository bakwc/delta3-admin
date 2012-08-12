#pragma once

#include <QWidget>
#include <QListWidgetItem>
#include "network.h"
#include "Protocols/file.h"

namespace Ui {
class FileForm;
}

class FileForm : public QWidget
{
    Q_OBJECT
    
public:
	explicit FileForm(delta3::File *file, QWidget* parent = 0);
    ~FileForm();
    
signals:
    void requestDir(QString &d);
    void requestFile(QString &f);

private slots:
    void onDirListReceived(const QVector<QStringList> &dir);
    void on_pushButton_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
	delta3::File	*file_;
	Ui::FileForm	*ui;
    QString _cd;
};
