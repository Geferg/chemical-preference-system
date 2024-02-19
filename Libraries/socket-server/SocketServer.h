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

        explicit SocketServer(const char *port);

        int initialize();
    private:

        const char *port_;
        int socket_file_descriptor;
        struct addrinfo hints;
        struct addrinfo *serv_info;
        struct addrinfo *p;
        struct sockaddr_storage their_addr{}; // connector's address information
        socklen_t sin_size;
        struct sigaction sa;
        int yes=1;
        char s[INET6_ADDRSTRLEN];
        int rv;

        // Saves and restores errno in case Waitpid() overwrites it
        static void sigchldHandler(int s);

        // Get sockaddr, IPv4 or IPv6
        static void *getInAddr(struct sockaddr *sa);

    };

}

#endif
