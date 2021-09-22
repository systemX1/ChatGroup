#ifndef FILETRANDIALOG_H
#define FILETRANDIALOG_H

#include <QDialog>

namespace Ui {
class FileTranDialog;
}

class FileTranDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileTranDialog(QWidget *parent = nullptr);
    ~FileTranDialog();

private:
    Ui::FileTranDialog *ui;
};

#endif // FILETRANDIALOG_H
