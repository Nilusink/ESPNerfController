#pragma once
#include <Arduino.h>


const char* charBoolean(bool b);

namespace wpn
{
    class Handler
    {
        private:
            // settings
            int salvo_sleep = 200;

            // pins
            uint8_t j_pin, m_pin, m_t_pin, t_pin, p_pin, p_m_pin, r_m_pin;

            // switch states
            bool motor_trigger = false;
            bool biometrics = false;
            bool trigger = false;
            bool jammer = false;
            bool mag = false;

            // config
            int salvo_count = 3;
            int fire_mode = 0;  // 0 - full auto; 1 - salvo (configurable); 2 - single;

            // internal variables
            bool firing = false;

            // private functions
            void piston_back();

            void fire_n(int count);

        public:
            Handler(
                uint8_t jammer_pin,
                uint8_t mag_pin,
                uint8_t motor_trigger_pin,
                uint8_t trigger_pin,
                uint8_t piston_pin,
                uint8_t pinton_motor_pin
                );

            // utility functions
            void update_states();
            
            void update_functionality();

            // getters
            bool get_motor_trigger();

            bool get_biometrics();

            int get_salvo_count();

            int get_fire_mode();

            bool get_trigger();

            bool get_jammer();

            bool get_mag();

            void get_as_json(char* buffer);

            // setters  (true on success, false on fail)
            bool set_fire_mode(int mode);

            bool set_salvo_count(int count);
    };
}
