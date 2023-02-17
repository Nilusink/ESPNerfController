/**
 * @file main.cpp
 * @author Nilusink
 * @brief combines everything
 * @version 0.8
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>

#include "weaponhandler/weaponhandler.hpp"
#include "fingerprint/fingerprint.hpp"
#include "wserver/wserver.hpp"
#include "aled/aled.hpp"
#include "oled/oled.hpp"
#include "gyro/gyro.hpp"


// colors for the adressable RGB leds
CHSV n_color(100, 255, 100);
CHSV nb_color(100, 255, 255);
CHSV l_color(160, 255, 150);
CHSV g_color(0, 255, 150);

bool state = false;


void setup()
{
    Serial.begin(115200);

    // setup all of the systems
    bool fs = Finger::setup();
    bool gy = Gyro::setup();

    ALED::setup(40);
    OLED::setup();

    if (!(fs && gy))
    {
        Serial.println("error initializing systems");
        for (;;) { delay(1); }
    }

    WServer::setup();

    // slowly turn red
    Finger::finger.LEDcontrol(5, 255, 1, 1);

    // set red
    ALED::ripple(n_color, 255, 10);
}


void loop()
{
    // update weapon handler
    wpn::handler.update_states(state);
    wpn::handler.update_functionality();

    double angle = Gyro::get_angle();

    uint8_t mode;
    switch(wpn::handler.get_fire_mode())
    {
        case 0:
        {
            mode = 0;
            break;
        }
        case 1:
        {
            mode = wpn::handler.get_salvo_count();
            break;
        }
        case 2:
        {
            mode = 1;
            break;
        }
        default:
        {
            mode = 255;
        }
    }

    OLED::update_display(mode, angle, 12);

    int id = Finger::getFingerprintID();

    if (id > 0)
    {
        Finger::finger.LEDcontrol(1, 100, 2, 1);
        ALED::ripple(g_color, 255, 7);
        delay(255);
        ALED::ripple(l_color, 255, 7, true);
        state = true;
    }
    else if (id == -3)
    {
        if (state)
        {
            Finger::finger.LEDcontrol(5, 20, 1);
            delay(10);
            ALED::ripple(n_color, 255, 5);
        }

        // blink red 3 times
        Finger::finger.LEDcontrol(1, 50, 1, 1);

        // leds blink red 3 times
        ALED::blink(nb_color, n_color, 150, 3);
        state = false;
        Finger::finger.LEDcontrol(5, 20, 1);
    }
}


/*
    # TODO:
        * Front motor
        * OLED "locked" when biometrics are locked
        * Some sort of indication when peripherals are disconnected (mag or jammer)
*/
