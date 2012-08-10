#pragma once

#include <QWidget>
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

private slots:
    void onDirListReceived(const QVector<QStringList> &dir);

    void on_pushButton_clicked();

private:
	delta3::File	*file_;
	Ui::FileForm	*ui;
};
