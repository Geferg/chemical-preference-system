#include <iostream>

#include "Libraries/socket-server/SocketServer.h"
#include "Libraries/hardware-control/HardwareControl.h"

using namespace Libraries;

void cycle() {
    HardwareControl::setValveMode(left, product);
    HardwareControl::setValveMode(right, buffer);
    HardwareControl::setValveMode(bottom, trash);

    HardwareControl::delay(4000);

    HardwareControl::setValveMode(left, circuit);
    HardwareControl::setValveMode(right, circuit);
    HardwareControl::setValveMode(bottom, circuit);

    HardwareControl::delay(4000);

    HardwareControl::setValveMode(left, buffer);
    HardwareControl::setValveMode(right, buffer);
    HardwareControl::setValveMode(bottom, trash);

    HardwareControl::delay(4000);

    HardwareControl::setValveMode(left, circuit);
    HardwareControl::setValveMode(right, circuit);
    HardwareControl::setValveMode(bottom, circuit);

    cycle();
}

int main() {

    //auto server = SocketServer("3490", 3);

    //server.debug = true;
    //server.start();

    HardwareControl::initialize();

    cycle();

    return 0;
}
