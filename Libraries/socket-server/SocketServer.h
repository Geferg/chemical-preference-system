#ifndef CHEMICAL_PREFERENCE_SYSTEM_SOCKETSERVER_H
#define CHEMICAL_PREFERENCE_SYSTEM_SOCKETSERVER_H

namespace Libraries {
    class SocketServer {
    public:
        int port;

    private:

        // Saves and restores errno in case Waitpid() overwrites it
        static void sigchldHandler(int s);

        // Get sockaddr, IPv4 or IPv6
        static void *getInAddr(struct sockaddr *sa);

    };

}

#endif
