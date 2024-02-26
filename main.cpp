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

    HardwareControl::runMotorByVolume(up, 10, 1);
    HardwareControl::delay(3000);
    HardwareControl::runMotorByVolume(down, 10, 1);

    //HardwareControl::runMotorByDistance(up, 10, 1);
    //HardwareControl::delay(3000);
    //HardwareControl::runMotorByDistance(down, 10, 1);

    //cycle();

    //float volume_ml = 2;
    //float flow_ml_s = 0.06;

    // 1 ml change => 9/50 cm change, 1 cm change => 4000 cycles
    // 1 ml change => 720 cycles

    /*
    int cycles = (int)(volume_ml * 720);

    int run_period_micros = (int)(1000000 * volume_ml/flow_ml_s);
    int step_period_micros = run_period_micros/cycles;

    //std::cout << "cycles " << cycles << "\n";
    //std::cout << "step period " << step_period_micros << "us\n";
    //std::cout << "run period " << run_period_micros / 1000 << "ms\n";

    auto start = std::chrono::high_resolution_clock::now();
    HardwareControl::runMotorByTime(up, run_period_micros, step_period_micros);
    auto stop = std::chrono::high_resolution_clock::now();

    HardwareControl::delay(3000);
    HardwareControl::runMotorByTime(down, run_period_micros, step_period_micros);

    auto fullExecutionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "runtime: " << fullExecutionTime.count()/1000 << "ms\n";

     */
    return 0;
}
