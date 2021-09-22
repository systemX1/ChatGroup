#include "workthread.h"

void WorkThread::run()
{
    const int EPOLL_SIZE = 1;
    int epfd = epoll_create(EPOLL_SIZE);
    char buf[util::BUF_SIZE];
    int ret;

    util::addEpollFd(epfd, clntfd, true);
    static struct epoll_event events[EPOLL_SIZE];

    while(true) {
        int epoll_event_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
        if(epoll_event_count < 0) {
            qDebug() << "epoll_wait err";   quit();
        }
        qDebug() << "epoll_events_count = " << epoll_event_count;
        for (int i = 0; i < epoll_event_count; ++i) {
            if(events[i].data.fd == clntfd) {
                if((ret = recv(clntfd, buf, util::BUF_SIZE, 0) ) == 0) {
                    qDebug() << "Server closed connection: " << clntfd;
                    ::close(clntfd);
                    quit();
                } else {
                    emit sendReciMsg(QString(buf).section(' ', 1, -1));
                }
                memset(buf, 0, strlen(buf));
            }
        }
    }
}
