#include "SocketServer.h"

#include <iostream>
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

namespace Libraries {
    SocketServer::SocketServer(const char *port) {
        port_ = port;
        debug = false;
    }

    int SocketServer::initialize() {
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // use my IP

        if((rv = getaddrinfo(nullptr,
                             port_,
                             &hints,
                             &serv_info)) != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
            return 1;
        }

        if(debug) {
            std::cout << "socket initialization complete\n";
        }

        return 0;
    }

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