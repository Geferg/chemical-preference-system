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
    SocketServer::SocketServer(const char *port, const int backlog) : backlog_(backlog) {
        port_ = port;
        debug = false;
    }

    int SocketServer::start() {
        // Load up address structs
        loadAddress();
        tryBind();
        freeaddrinfo(serv_info_);
        startListen();
        reap();
        acceptClients();

        return 0;
    }

    int SocketServer::stop() {
        stopListen();

        return 0;
    }

    int SocketServer::loadAddress() {
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

            break;
        }

        if (p_ == nullptr)  {
            fprintf(stderr, "server: failed to bind\n");
            exit(1);
        }

        if (debug) {
            std::cout << "Server is bound.\n";
        }

        return 0;
    }

    int SocketServer::startListen() {
        if (listen(socket_file_descriptor_, backlog_) == -1) {
            perror("listen");
            exit(1);
        }

        std::cout << "Waiting for connections.\n";
        return 0;
    }

    int SocketServer::stopListen() {



        return 0;
    }

    int SocketServer::reap() {
        sa_.sa_handler = sigchldHandler;
        sigemptyset(&sa_.sa_mask);
        sa_.sa_flags = SA_RESTART;

        if (sigaction(SIGCHLD, &sa_, nullptr) == -1) {
            perror("sigaction");
            exit(1);
        }

        if (debug) {
            std::cout << "Dead processes reaped.\n";
        }

        return 0;
    }

    int SocketServer::acceptClients() {
        int new_fd;

        while(true) {  // main accept() loop
            sin_size_ = sizeof their_addr_;
            new_fd = accept(socket_file_descriptor_, (struct sockaddr *)&their_addr_, &sin_size_);
            if (new_fd == -1) {
                perror("accept");
                continue;
            }

            inet_ntop(their_addr_.ss_family,
                      getInAddr((struct sockaddr *)&their_addr_),
                      s_, sizeof s_);

            if (debug) {
                std::cout << "Got connection from " << s_ << "\n";
            }

            if (!fork()) { // this is the child process
                close(socket_file_descriptor_); // child doesn't need the listener

                if (send(new_fd, "Hello, world!", 13, 0) == -1) {
                    perror("send");
                }

                close(new_fd);
                exit(0);
            }

            close(new_fd);  // parent doesn't need this
        }
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