#ifndef UTIL_H
#define UTIL_H

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <QString>
#include <QDateTime>
#include <qdebug.h>

namespace util {

enum MsgType {
    ChatMsg, Online, Offline, TFile, RefFile
};

struct UserInfo
{
    UserInfo() {}
    UserInfo(QString u, QString t) : userName(u), token(t) {}
    QString userName;
    QString token;
};

static const char* SERV_HOST = "127.0.0.1";
static const char* SERV_PORT = "2002";
static const int BUF_SIZE = 4096;

int openClientFd(const char *hostname, const char *port);
void addEpollFd(int epollFd, int fd, bool isEnableET);
int setNonBlock(int sockfd);
QString getCurrTime();
void closeWrapper(int fd);

}   // namespace util

#endif // UTIL_H
