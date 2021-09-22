#include <QApplication>

#include "mainwindow.h"
#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog loginDig;
    loginDig.show();
    return a.exec();
}
