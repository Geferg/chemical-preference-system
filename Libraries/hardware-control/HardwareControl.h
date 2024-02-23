#ifndef CHEMICAL_PREFERENCE_SYSTEM_HARDWARECONTROL_H
#define CHEMICAL_PREFERENCE_SYSTEM_HARDWARECONTROL_H

#include "enums.h"
#include "ValveHandler.h"
#include "MotorHandler.h"

namespace Libraries {

    class HardwareControl {
    public:
        static int initialize();

        // |  Mode   | V1  | V2  | V3  | V4  | V5  | V6  |
        // |---------|-----|-----|-----|-----|-----|-----|
        // | Buffer  |  0  |  0  |  0  |  0  | n/a | n/a |
        // | Product |  0  |  1  |  1  |  0  | n/a | n/a |
        // | Circuit |  1  |  x  |  x  |  1  |  0  |  0  |
        // | Trash   | n/a | n/a | n/a | n/a |  1  |  1  |
        static int setValveMode(ValveCluster valves, ValveMode mode);

        static int runMotor(MotorDirection direction, int step_period_millis, int run_period_millis);

        static bool isReady();
        static bool isInitialized();
        static void delay(int millis);

    private:
        static ValveHandler valveHandler;
        static MotorHandler motorHandler;

        static const unsigned int visible_light_pin = 10;
        static const unsigned int ir_light_pin = 9;

        static const unsigned int motor_dir_pin = 11;
        static const unsigned int motor_step_pin = 22;

        static const unsigned int valve_1_gpio_pin = 26;
        static const unsigned int valve_2_gpio_pin = 19;
        static const unsigned int valve_3_gpio_pin = 6;
        static const unsigned int valve_4_gpio_pin = 5;
        static const unsigned int valve_5_gpio_pin = 27;
        static const unsigned int valve_6_gpio_pin = 17;

        constexpr static const unsigned int valve_gpio_pins[6] = {
                valve_1_gpio_pin,
                valve_2_gpio_pin,
                valve_3_gpio_pin,
                valve_4_gpio_pin,
                valve_5_gpio_pin,
                valve_6_gpio_pin
        };

        static bool gpio_initialized;
        static bool gpio_ready;
    };

} // Libraries

#endif //CHEMICAL_PREFERENCE_SYSTEM_HARDWARECONTROL_H
