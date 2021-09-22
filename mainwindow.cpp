#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setSlotConnection();
    connToServ();
}

MainWindow::MainWindow(QWidget *parent, util::UserInfo *u)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), userInfo(u)
{
    ui->setupUi(this);

    setSlotConnection();
    connToServ();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete userInfo;
}

void MainWindow::connToServ()
{
    this->clntfd = util::openClientFd(util::SERV_HOST, util::SERV_PORT);
    if(this->clntfd <= 0) {
        qDebug() << "openClientFd err" << clntfd << endl;
    }
    qDebug() << util::SERV_HOST << util::SERV_PORT << clntfd << endl;
    WorkThread* thread1 = new WorkThread(clntfd);
    thread1->start();
    QObject::connect(thread1, &WorkThread::sendReciMsg,
                     this, &MainWindow::reciChatMsg);
}

void MainWindow::setShortcut()
{



}

void MainWindow::setSlotConnection()
{
    setShortcut();
    QObject::connect(ui->SendPushButton, &QPushButton::clicked,
                     this, &MainWindow::sendPushButtonClicked);

}

int MainWindow::sendChatMsg(const QString& qchatMsg)
{
    QString qtemp = userInfo->userName + " " + qchatMsg;
    QByteArray qba = qtemp.toLocal8Bit();
    char *buf = qba.data();
    qDebug() << buf << clntfd;
    send(clntfd, buf, strlen(buf), 0);
    return 0;
}

int MainWindow::reciChatMsg(QString msg)
{
//    char buf[util::BUF_SIZE];
//    int ret = recv(clntfd, buf, util::BUF_SIZE, 0);
//    if (ret == 0) {
//        qDebug() << "Server closed connection: %d" << clntfd;
//        ::close(clntfd);
//        return -1;
//    }
    ui->ChatTextBrowser->setCurrentFont(QFont("微软雅黑", 12));
    ui->ChatTextBrowser->setTextColor(Qt::darkBlue);
    ui->ChatTextBrowser->append(userInfo->userName + "  " + util::getCurrTime());
    ui->ChatTextBrowser->setTextColor(Qt::darkGreen);
    ui->ChatTextBrowser->append(msg);
    return 0;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    send(clntfd, nullptr, 0, 0);
    event->accept();
}

void MainWindow::sendPushButtonClicked()
{
    const QString& qchatMsg = getChatTextEdit();
    sendChatMsg(qchatMsg);
    showMsg(util::ChatMsg, qchatMsg);
}

QString MainWindow::getChatTextEdit()
{
    QString qchatMsg = ui->ChatTextEdit->toPlainText();
    ui->ChatTextEdit->clear();
    ui->ChatTextEdit->setFocus();
    return qchatMsg;
}

void MainWindow::showMsg(util::MsgType msgType, const QString& qmsg)
{
    switch (msgType) {
    case util::ChatMsg:
        ui->ChatTextBrowser->setCurrentFont(QFont("微软雅黑", 12));
        ui->ChatTextBrowser->setTextColor(Qt::darkBlue);
        ui->ChatTextBrowser->append(userInfo->userName + "  " + util::getCurrTime());
        ui->ChatTextBrowser->setTextColor(Qt::darkGreen);
        ui->ChatTextBrowser->append(qmsg);
        break;
    default:
        break;
    }
}

