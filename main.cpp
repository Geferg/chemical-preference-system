#include <iostream>

#include "Libraries/socket-server/SocketServer.h"

using namespace Libraries;

int main() {

    auto server = SocketServer("3490");

    server.debug = true;
    server.start();

    return 0;
}
