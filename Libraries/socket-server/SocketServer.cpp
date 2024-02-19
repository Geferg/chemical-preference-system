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
        memset(&hints_, 0, sizeof hints_);
        hints_.ai_family = AF_UNSPEC;
        hints_.ai_socktype = SOCK_STREAM;
        hints_.ai_flags = AI_PASSIVE; // use my IP

        if((rv_ = getaddrinfo(nullptr,
                              port_,
                              &hints_,
                              &serv_info_)) != 0) {
            fprintf(stderr, "getaddrinfo: %s_\n", gai_strerror(rv_));
            return 1;
        }

        if(debug) {
            std::cout << "Socket initialization complete.\n";
        }

        return 0;
    }


    int SocketServer::tryBind() {
        int yes = 1;

        for(p_ = serv_info_; p_ != nullptr; p_ = p_->ai_next) {
            if ((socket_file_descriptor_ = socket(p_->ai_family, p_->ai_socktype,
                                 p_->ai_protocol)) == -1) {
                perror("server: socket");
                continue;
            }

            if (debug) {
                std::cout << "Got socket descriptor.\n";
            }

            if (setsockopt(socket_file_descriptor_, SOL_SOCKET, SO_REUSEADDR, &yes,
                           sizeof(int)) == -1) {
                perror("setsockopt");
                exit(1);
            }

            if (debug) {
               std::cout << "Socket options set.\n";
            }

            if (bind(socket_file_descriptor_, p_->ai_addr, p_->ai_addrlen) == -1) {
                close(socket_file_descriptor_);
                perror("server: bind");
                continue;
            }

            std::cout << "Server is bound.\n";
            return 0;
        }

        return 1;
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