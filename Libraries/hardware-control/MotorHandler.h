#ifndef CHEMICAL_PREFERENCE_SYSTEM_MOTORHANDLER_H
#define CHEMICAL_PREFERENCE_SYSTEM_MOTORHANDLER_H

#include "enums.h"

namespace Libraries {

    class MotorHandler {
    public:
        bool compensate;

        explicit MotorHandler(const unsigned int dir_pin, const unsigned int step_pin) {
            dir_gpio_pin = dir_pin;
            step_gpio_pin = step_pin;
            compensate = true;
            total_error = 0;
            last_error = 0;
            cycle_count = 0;
        }

        int prepareGpio();
        int run(MotorDirection direction, int step_period_millis);
        int stop();
        int runFor(MotorDirection direction, int step_period_millis, int run_period_millis);

    private:
        unsigned int dir_gpio_pin;
        unsigned int step_gpio_pin;

        long total_error;
        long last_error;
        int cycle_count;

        long getCompensationMicros(long error_micros);
        void clearCompensation();
    };

}

#endif
