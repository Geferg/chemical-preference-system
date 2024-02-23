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

        for (unsigned int gpioPin : valve_gpio_pins) {
            gpioSetMode(gpioPin, PI_OUTPUT);
            gpioWrite(gpioPin, PI_LOW);
        }

        gpioDelay(500000);

        for (unsigned  int gpioPin : valve_gpio_pins) {
            gpioWrite(gpioPin, PI_HIGH);
            gpioDelay(100000);
            gpioWrite(gpioPin, PI_LOW);
        }

        return 0;
    }

    int HardwareControl::setValveMode(ValveCluster valves, ValveMode mode) {
        if (!gpio_initialized) {
            return -1;
        }

        int ret = valveHandler.set(valves, mode);

        return ret;
    }

    void HardwareControl::delay(int millis) {
        gpioDelay(millis * 1000);
    }
}