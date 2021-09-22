#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include "mainwindow.h"
#include "util.h"

class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread(int fd) : clntfd(fd) {}
protected:
    void run();
signals:
    void sendReciMsg(QString msg);
private:
    int clntfd;
};

#endif // WORKTHREAD_H
