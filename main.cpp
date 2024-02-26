#include <cmath>
#include <iostream>
#include <chrono>
#include <cmath>

#include "Libraries/socket-server/SocketServer.h"
#include "Libraries/hardware-control/HardwareControl.h"

using namespace Libraries;

void cycle() {
    HardwareControl::setValveMode(left, buffer);
    HardwareControl::setValveMode(right, buffer);
    HardwareControl::setValveMode(bottom, trash);

    HardwareControl::delay(4000);

    HardwareControl::setValveMode(left, circuit);
    HardwareControl::setValveMode(right, circuit);
    HardwareControl::setValveMode(bottom, circuit);

    HardwareControl::delay(4000);

    HardwareControl::setValveMode(left, product);
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


    if (!HardwareControl::isInitialized() || !HardwareControl::isReady()) {
        return -1;
    }

    //cycle();

    float ml = 27.78;
    int cycles = (int)(ml * 720);

    std::cout << "cycles " << cycles << "\n";
    HardwareControl::runMotor(up, 2000, cycles);
    HardwareControl::delay(3000);
    HardwareControl::runMotor(down, 2000, cycles);

    return 0;
}
