/**
 * @file weaponhandler.hpp
 * @author Nilusink
 * @brief most of the interesting sutff
 * @version 0.8
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once
#include <Arduino.h>


// jammer (36)
// MTrigger (34)
// Trigger (23)
// GripSwitch (2)
// Piston (14)
// mag (35)


#define MOTOR_TRIGGER_PIN 34
#define PISTONR_MOTOR_PIN 25
#define TRIGGER_PIN 23
#define JAMMER_PIN 36
#define PISTON_PIN 14
#define MOTOR_PIN 26
#define GRIP_PIN 2
#define MAG_PIN 35



/**
 * @brief convert a boolean into its string variant ("true", "false")
 * 
 * @param b input bool
 * @return const char* 
 */
const char* charBoolean(bool b);


namespace wpn
{
    /**
     * @brief handles most of the switches
     * 
     */
    class Handler
    {
        private:
            // settings
            int salvo_sleep = 500;

            // pins
            uint8_t j_pin, m_pin, m_t_pin, t_pin, p_pin, p_m_pin, r_m_pin;

            // switch states
            bool motor_trigger = false;
            bool bio = false;
            bool trigger = false;
            bool jammer = false;
            bool mag = false;

            // config
            int salvo_count = 3;
            int fire_mode = 0;  // 0 - full auto; 1 - salvo (configurable); 2 - single;

            // internal variables
            bool firing = false;

            // private functions
            /**
             * @brief put the firing piston back
             * 
             */
            void piston_back();

            /**
             * @brief fire for `count` times
             * 
             * @param count how often to fire
             */
            void fire_n(int count);

        public:
            Handler(
                uint8_t jammer_pin,
                uint8_t mag_pin,
                uint8_t motor_trigger_pin,
                uint8_t trigger_pin,
                uint8_t piston_pin,
                uint8_t pinton_motor_pin,
                uint8_t motor_pin
                );

            // utility functions
            /**
             * @brief update all of the button readings
             * 
             * @param biometrics current biometric status
             */
            void update_states(bool biometrics);
            
            /**
             * @brief update motors
             * 
             */
            void update_functionality();

            // getters
            bool get_motor_trigger();

            bool get_biometrics();

            int get_salvo_count();

            int get_fire_mode();

            bool get_trigger();

            bool get_jammer();

            bool get_mag();

            /**
             * @brief get all of the values formatted as stringified json
             * 
             * @param buffer 
             */
            void get_as_json(char* buffer);

            // setters  (true on success, false on fail)
            /**
             * @brief Set the fire mode
             * 
             * @param mode 0...full auto; 1...salvo (configurable); 2...single;
             * @return bool - success
             */
            bool set_fire_mode(int mode);

            /**
             * @brief configure the salvo count
             * 
             * @param count how many darts to shoot (only for fire_mode 1)
             * @return bool - success
             */
            bool set_salvo_count(int count);
    };

    extern wpn::Handler handler;
}
