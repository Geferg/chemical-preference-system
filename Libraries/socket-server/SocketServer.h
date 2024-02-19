#ifndef CHEMICAL_PREFERENCE_SYSTEM_SOCKETSERVER_H
#define CHEMICAL_PREFERENCE_SYSTEM_SOCKETSERVER_H

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
    class SocketServer {
    public:
        bool debug;

        explicit SocketServer(const char *port, const int backlog);

        int start();
        int stop();
    private:

        const char *port_;
        const int backlog_;
        int socket_file_descriptor_;
        struct addrinfo hints_;
        struct addrinfo *serv_info_;
        struct addrinfo *p_;
        struct sockaddr_storage their_addr_; // connector's_ address information
        socklen_t sin_size_;
        struct sigaction sa_;

        char s_[INET6_ADDRSTRLEN];
        int rv_;

        int loadAddress();
        int tryBind();
        int startListen();
        int stopListen();
        int reap();
        int acceptClients();

        // Saves and restores errno in case Waitpid() overwrites it
        static void sigchldHandler(int s);

        // Get sockaddr, IPv4 or IPv6
        static void *getInAddr(struct sockaddr *sa);

    };

}

#endif
