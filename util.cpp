#include "util.h"

int util::openClientFd(const char *hostname, const char *port)
{
    int clntfd, errcode;
    struct addrinfo hints, *list, *p;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV | AI_ADDRCONFIG;
    if ( (errcode = getaddrinfo(hostname, port, &hints, &list)) != 0) {
        fprintf(stderr, "getaddrinfo failed (%s:%s): %s\n", hostname, port, gai_strerror(errcode));
        return -2;
    }

    for (p = list; p; p = p->ai_next) {
        if ((clntfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)  // try next if failed
            continue;
        if (connect(clntfd, p->ai_addr, p->ai_addrlen) != -1)                     // succ
            break;
        if (close(clntfd) < 0) {                                                  // failed to open and close
            fprintf(stderr, "open_clientfd: close failed: %s\n", strerror(errno));
            return -1;
        }
    }
    qDebug() << "clntfd" << clntfd << endl;
    freeaddrinfo(list);
    if (!p)
        return -1;
    else
        return clntfd;
}

void util::addEpollFd(int epollFd, int fd, bool isEnableET)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if (isEnableET) {
        ev.events = EPOLLIN | EPOLLET;
    }
    epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &ev);
    setNonBlock(fd);
    qDebug() << fd << "added to epoll";
}

int util::setNonBlock(int sockfd) {
    fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK);
    return 0;
}

QString util::getCurrTime()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

void util::closeWrapper(int fd)
{
    close(fd);
}
