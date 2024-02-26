#include <pigpio.h>
#include <iostream>

#include "HardwareControl.h"
#include "ValveHandler.h"
#include "MotorHandler.h"
#include "enums.h"

namespace Libraries {

    ValveHandler HardwareControl::valveHandler = ValveHandler(valve_gpio_pins);
    MotorHandler HardwareControl::motorHandler = MotorHandler(motor_dir_pin, motor_step_pin, motor_sleep_pin);

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

    int HardwareControl::runMotorByTime(MotorDirection direction,
                                        unsigned int time_us,
                                        unsigned int period_us_per_step) {
        if (!gpio_initialized) {
            return -1;
        }

        std::cout << "period: " << period_us_per_step << "us\n";
        std::cout << "time: " << time_us << "us\n";

        return motorHandler.runFor(direction, period_us_per_step, time_us);
    }

    int HardwareControl::runMotorByDistance(MotorDirection direction,
                                            unsigned int distance_mm,
                                            unsigned int velocity_mm_per_s) {
        if (!gpio_initialized) {
            return -1;
        }

        // 400 cycles => 1 mm change, QED
        unsigned int period_us_per_step = 2500/velocity_mm_per_s;
        unsigned int time_us = period_us_per_step * 400 * distance_mm;

        return runMotorByTime(direction, time_us, period_us_per_step);
    }

    int HardwareControl::runMotorByVolume(MotorDirection direction,
                                          unsigned int volume_ml,
                                          unsigned int flow_ml_per_s) {
        if (!gpio_initialized) {
            return -1;
        }

        // 9/5 mm => 1 ml change
        //TODO fix
        unsigned int distance_mm = volume_ml * 9/5;
        unsigned int velocity_mm_per_s = distance_mm * flow_ml_per_s/volume_ml;

        return runMotorByDistance(direction, distance_mm, velocity_mm_per_s);
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