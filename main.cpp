#include <iostream>

#include "Libraries/socket-server/SocketServer.h"

using namespace Libraries;

int main() {
    SocketServer server {
        .port = 3490
    };


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
