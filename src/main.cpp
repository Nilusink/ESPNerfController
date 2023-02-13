#include <Arduino.h>
#include "fingerprint.hpp"
#include "weaponhandler.hpp"
#include "aled.hpp"


CHSV n_color(100, 255, 100);
CHSV nb_color(100, 255, 255);
CHSV l_color(160, 255, 100);
CHSV g_color(0, 255, 100);

bool state = false;


void setup()
{
    Serial.begin(9600);
    Finger::setup();
    ALED::setup(40);

    // slowly turn red
    Finger::finger.LEDcontrol(5, 255, 1, 1);

    // set red
    ALED::ripple(n_color, 255, 10);
}


void loop()
{  
    // update weapon handler
    wpn::handler.update_states();
    wpn::handler.update_functionality();

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
        Finger::finger.LEDcontrol(1, 20, 1);

        // leds blink red 3 times
        ALED::blink(nb_color, n_color, 150, 3);
        state = false;
        Finger::finger.LEDcontrol(5, 20, 1);
    }
}
