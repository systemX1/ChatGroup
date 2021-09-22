#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QCloseEvent>
#include <QThread>
#include <QString>

#include "util.h"
#include "workthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(QWidget *parent = nullptr, util::UserInfo *u = nullptr);
    ~MainWindow();

    void connToServ();
    void setSlotConnection();
    void setShortcut();

    int sendChatMsg(const QString& qchatMsg);
    int reciChatMsg(QString msg);
    void closeEvent(QCloseEvent *event);

    void sendPushButtonClicked();
    QString getChatTextEdit();
    void showMsg(util::MsgType msgType, const QString& qmsg);
private:
    Ui::MainWindow *ui;
    util::UserInfo *userInfo;
    int clntfd;
};
#endif // MAINWINDOW_H
