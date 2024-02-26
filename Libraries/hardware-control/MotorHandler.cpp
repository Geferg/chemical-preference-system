#include <pigpio.h>
#include <chrono>
#include <iostream>
#include <cmath>

#include "MotorHandler.h"
#include "enums.h"

namespace Libraries {
    int MotorHandler::prepareGpio() {
        int ret = gpioSetMode(dir_gpio_pin, PI_OUTPUT);
        if (ret != 0) {
            return ret;
        }

        ret = gpioSetMode(step_gpio_pin, PI_OUTPUT);
        if (ret != 0) {
            return ret;
        }

        ret = gpioSetMode(sleep_gpio_pin, PI_OUTPUT);
        if (ret != 0) {
            return ret;
        }

        gpioWrite(sleep_gpio_pin, PI_LOW);

        return 0;
    }

    int MotorHandler::run(MotorDirection direction, int step_period_millis) {
        if (direction == up) {

        }

        return 0;
    }

    int MotorHandler::stop() {

        return 0;
    }

    int MotorHandler::runFor(MotorDirection direction, unsigned int step_period_micros, unsigned int run_period_micros) {

        //TODO implement half steps?

        gpioWrite(sleep_gpio_pin, PI_HIGH);

        gpioDelay(2000);

        gpioWrite(step_gpio_pin, PI_LOW);
        if (direction == up) {
            gpioWrite(dir_gpio_pin, PI_LOW);
        }
        else {
            gpioWrite(dir_gpio_pin, PI_HIGH);
        }

        auto start = std::chrono::high_resolution_clock::now();

        long cycle_time;
        long cycle_error = 0;

        for(unsigned int i = 0; i < run_period_micros; i += step_period_micros) {
            long compensate_micros = getCompensationMicros(cycle_error);

            auto cycle_start = std::chrono::high_resolution_clock::now();

            if (step_period_micros - compensate_micros < 0) {
                compensate_micros = step_period_micros - 4;
            }

            gpioWrite(step_gpio_pin, PI_HIGH);
            gpioDelay((step_period_micros - compensate_micros)/2);
            gpioWrite(step_gpio_pin, PI_LOW);
            gpioDelay((step_period_micros - compensate_micros)/2);

            auto cycle_stop = std::chrono::high_resolution_clock::now();

            cycle_time = std::chrono::duration_cast<std::chrono::microseconds>(cycle_stop - cycle_start).count();
            cycle_error = cycle_time - step_period_micros;
        }

        // UNCOMMENT FOR TUNING COMPENSATOR PID
        //auto stop = std::chrono::high_resolution_clock::now();
        //auto runtime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        //long error = runtime.count() - run_period_millis * 1000;
        //float error_ratio = (float)error/((float)run_period_millis * 1000);
        //float error_per_cycle = (float)error/(float)cycle_count;
        //std::cout << "Absolute error: " << error << "μs\n";
        //std::cout << "Percentage error: " << std::floor(error_ratio * 10000) / 100 <<"%\n";
        //std::cout << "Cycles: " << cycle_count << "\n";
        //std::cout << "Error per cycle: " << error_per_cycle << "μs\n";

        gpioWrite(dir_gpio_pin, PI_LOW);
        gpioWrite(sleep_gpio_pin, PI_LOW);
        clearCompensation();

        return 0;
    }

    long MotorHandler::getCompensationMicros(long error_micros) {
        // PI-Controller
        // replacing `error_micros` with `(total_error/cycle_count)` could smooth result
        total_error += error_micros;
        cycle_count++;

        long comp = error_micros/5 + total_error/10;

        return comp;
    }

    void MotorHandler::clearCompensation() {
        last_error = 0;
        total_error = 0;
        cycle_count = 0;
    }

    void MotorHandler::sleepMotor() {

    }

    void MotorHandler::wakeMotor() {

    }
}