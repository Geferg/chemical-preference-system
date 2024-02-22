#include "ValveHandler.h"
#include "pigpio.h"

namespace Libraries {

    int ValveHandler::prepareGpio() {

        for (unsigned int gpio : valve_gpio_pins) {
            int ret = gpioSetMode(gpio, PI_OUTPUT);
            if (ret != 0) {
                return ret;
            }

        }

        return 0;
    }

    int ValveHandler::set(ValveCluster valves, ValveMode mode) {
        switch (mode) {
            case buffer:
                switch (valves) {
                    case left:
                        gpioWrite(valve_gpio_pins[0], PI_LOW);
                        gpioWrite(valve_gpio_pins[1], PI_LOW);
                        break;

                    case right:
                        gpioWrite(valve_gpio_pins[3], PI_LOW);
                        gpioWrite(valve_gpio_pins[2], PI_LOW);
                        break;

                    case bottom:
                        return -1;
                }
                break;

            case product:
                switch (valves) {
                    case left:
                        gpioWrite(valve_gpio_pins[0], PI_LOW);
                        gpioWrite(valve_gpio_pins[1], PI_HIGH);
                        break;

                    case right:
                        gpioWrite(valve_gpio_pins[3], PI_LOW);
                        gpioWrite(valve_gpio_pins[2], PI_HIGH);
                        break;

                    case bottom:
                        return -1;
                }
                break;

            case circuit:
                switch (valves) {
                    case left:
                        gpioWrite(valve_gpio_pins[0], PI_HIGH);
                        break;

                    case right:
                        gpioWrite(valve_gpio_pins[3], PI_HIGH);
                        break;

                    case bottom:
                        gpioWrite(valve_gpio_pins[4], PI_LOW);
                        gpioWrite(valve_gpio_pins[5], PI_LOW);
                        break;
                }
                break;

            case trash:
                switch (valves) {
                    case bottom:
                        gpioWrite(valve_gpio_pins[4], PI_HIGH);
                        gpioWrite(valve_gpio_pins[5], PI_HIGH);
                        break;

                    case left:
                    case right:
                        return -1;
                }


                break;
        }

        return 0;
    }
}