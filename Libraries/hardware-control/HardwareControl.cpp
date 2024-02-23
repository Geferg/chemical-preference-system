#include <pigpio.h>
#include <iostream>

#include "HardwareControl.h"
#include "enums.h"

namespace Libraries {

    ValveHandler HardwareControl::valveHandler = ValveHandler(valve_gpio_pins);
    bool HardwareControl::gpio_initialized = false;

    int HardwareControl::initialize() {
        if (gpioInitialise() == -1) {
            return -1;
        }

        gpio_initialized = true;
        valveHandler.prepareGpio();

        return 0;
    }

    int HardwareControl::setValveMode(ValveCluster valves, ValveMode mode) {
        if (!gpio_initialized) {
            return -1;
        }

        return valveHandler.set(valves, mode);
    }

    void HardwareControl::delay(int millis) {
        gpioDelay(millis * 1000);
    }
}