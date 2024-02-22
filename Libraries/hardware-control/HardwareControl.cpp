#include <pigpio.h>
#include <iostream>

#include "HardwareControl.h"
#include "enums.h"

namespace Libraries {

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

    //TODO move to valve logic handler along with motor handler
    int HardwareControl::setValveMode(ValveCluster valves, ValveMode mode) {
        /*
        if (!gpio_initialized) {
            return -1;
        }
        */

        //valveHandler.set(valves, mode);


        switch (mode) {
            case buffer:
                switch (valves) {
                    case left:
                        gpioWrite(valve_1_gpio_pin, PI_LOW);
                        gpioWrite(valve_2_gpio_pin, PI_LOW);
                        break;

                    case right:
                        gpioWrite(valve_4_gpio_pin, PI_LOW);
                        gpioWrite(valve_3_gpio_pin, PI_LOW);
                        break;

                    case bottom:
                        return -1;
                }
                break;

            case product:
                switch (valves) {
                    case left:
                        gpioWrite(valve_1_gpio_pin, PI_LOW);
                        gpioWrite(valve_2_gpio_pin, PI_HIGH);
                        break;

                    case right:
                        gpioWrite(valve_4_gpio_pin, PI_LOW);
                        gpioWrite(valve_3_gpio_pin, PI_HIGH);
                        break;

                    case bottom:
                        return -1;
                }
                break;

            case circuit:
                switch (valves) {
                    case left:
                        gpioWrite(valve_1_gpio_pin, PI_HIGH);
                        break;

                    case right:
                        gpioWrite(valve_4_gpio_pin, PI_HIGH);
                        break;

                    case bottom:
                        gpioWrite(valve_5_gpio_pin, PI_LOW);
                        gpioWrite(valve_6_gpio_pin, PI_LOW);
                        break;
                }
                break;

            case trash:
                switch (valves) {
                    case bottom:
                        gpioWrite(valve_5_gpio_pin, PI_HIGH);
                        gpioWrite(valve_6_gpio_pin, PI_HIGH);
                        break;

                    case left:
                    case right:
                        return -1;
                }


                break;
        }



        return 0;
    }

    void HardwareControl::delay(int millis) {
        gpioDelay(millis * 1000);
    }
}