#pragma once

#include <QWidget>
#include <QListWidgetItem>
#include "network.h"
#include "Protocols/file.h"
#include <QMenu>
#include <QFileDialog>

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
    void requestFile(QString &remoteFile, QString &localFile);
    void setCurrentDir(const QString &dir);
    void setDirUp();
    void openDir(const QString &dir);
    void command(delta3::File::FileMode m, QString source, QString dest);


private slots:
    void onDirListReceived(const QVector<QStringList> &dir);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_customContextMenuRequested(const QPoint &pos);
    void onDirChanged(QString &cd);
    void onFileReceived();

    void rename();

    void on_buttonChangeDir_clicked();

private:
    delta3::File	*_file;
	Ui::FileForm	*ui;
    QFileDialog *_dialog;
    QMenu           _menu;
};
