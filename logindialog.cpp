#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->UserNameLineEdit->setFocus();
    QObject::connect(ui->LoginPushButton, &QPushButton::clicked,
                     this, &LoginDialog::loginPushButtonClicked);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::loginPushButtonClicked()
{
    userInfo = new util::UserInfo(ui->UserNameLineEdit->text(), ui->PwdLineEdit->text());
    showChatDialogWindow();
}

void LoginDialog::showChatDialogWindow()
{
    chatGroupWindow = new MainWindow(nullptr, userInfo);
    chatGroupWindow->setWindowTitle(ui->UserNameLineEdit->text());
    chatGroupWindow->show();
    this->close();
}
















