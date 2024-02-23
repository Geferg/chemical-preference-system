#include <pigpio.h>
#include <iostream>

#include "HardwareControl.h"
#include "ValveHandler.h"
#include "MotorHandler.h"
#include "enums.h"

namespace Libraries {

    ValveHandler HardwareControl::valveHandler = ValveHandler(valve_gpio_pins);
    MotorHandler HardwareControl::motorHandler = MotorHandler(motor_dir_pin, motor_step_pin);

    bool HardwareControl::gpio_initialized = false;
    bool HardwareControl::gpio_ready = false;

    int HardwareControl::initialize() {
        //TODO improve returns for different jank
        if (gpioInitialise() == -1) {
            return -1;
        }

        gpio_initialized = true;

        if (valveHandler.prepareGpio() != 0) {
            return -1;
        }

        if (motorHandler.prepareGpio() != 0) {
            return -1;
        }

        motorHandler.compensate = false;

        gpio_ready = true;

        return 0;
    }

    int HardwareControl::setValveMode(ValveCluster valves, ValveMode mode) {
        if (!gpio_initialized) {
            return -1;
        }

        return valveHandler.set(valves, mode);
    }

    int HardwareControl::runMotor(MotorDirection direction, int step_period_millis, int run_period_millis) {
        if (!gpio_initialized) {
            return -1;
        }

        return motorHandler.runFor(direction, step_period_millis, run_period_millis);
    }

    bool HardwareControl::isInitialized() {
        return gpio_initialized;
    }

    bool HardwareControl::isReady() {
        return gpio_ready;
    }

    void HardwareControl::delay(int millis) {
        gpioDelay(millis * 1000);
    }
}