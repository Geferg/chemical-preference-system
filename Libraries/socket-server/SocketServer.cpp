#include <pigpio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>

#include "SocketServer.h"

namespace Libraries {

    void SocketServer::sigchldHandler(int s) {
        int saved_errno = errno;
        while(waitpid(-1, nullptr, WNOHANG) > 0);
        errno = saved_errno;
    }

    void *SocketServer::getInAddr(struct sockaddr *sa) {
        if (sa->sa_family == AF_INET) {
            return &(((struct sockaddr_in*)sa)->sin_addr);
        }

        return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }
}