#pragma once

#include <QWidget>
#include <QListWidgetItem>
#include "network.h"
#include "Protocols/file.h"
#include <QMenu>

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
    void requestDir();
    void requestFile(QString &f);
    void setCurrentDir(const QString &dir);
    void setDirUp();
    void openDir(const QString &dir);
    void command(delta3::File::FileMode m, QString source, QString dest);


private slots:
    void onDirListReceived(const QVector<QStringList> &dir);
    void on_pushButton_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_customContextMenuRequested(const QPoint &pos);
    void onDirChanged(QString &cd);

    void rename();

private:
	delta3::File	*file_;
	Ui::FileForm	*ui;
    QMenu           menu_;
};
