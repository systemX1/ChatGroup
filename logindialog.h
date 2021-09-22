#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QFile>
#include <QObject>
#include "mainwindow.h"
#include "util.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    void loginPushButtonClicked();
    void showChatDialogWindow();
private:
    Ui::LoginDialog *ui;
    MainWindow *chatGroupWindow;
    util::UserInfo *userInfo = nullptr;
};

#endif // LOGINDIALOG_H
