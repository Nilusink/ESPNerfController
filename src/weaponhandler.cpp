#include "weaponhandler.h"

const char *charBoolean(bool b)
{
    return b ? "true" : "false";
}


// Handler implementation
using namespace wpn;
Handler::Handler(
    uint8_t jammer_pin,
    uint8_t mag_pin,
    uint8_t motor_trigger_pin,
    uint8_t trigger_pin,
    uint8_t piston_pin,
    uint8_t piston_motor_pin
    )
{
    // save pin numbers
    p_m_pin = piston_motor_pin;
    m_t_pin = motor_trigger_pin;
    t_pin = trigger_pin;
    p_pin = piston_pin;
    j_pin = jammer_pin;
    m_pin = mag_pin;

    // setup pins
    pinMode(p_m_pin, OUTPUT);
    pinMode(m_t_pin, INPUT_PULLUP);
    pinMode(p_pin, INPUT_PULLUP);
    pinMode(t_pin, INPUT_PULLUP);
    pinMode(j_pin, INPUT_PULLUP);
    pinMode(m_pin, INPUT_PULLUP);
}

// private functions
void Handler::piston_back()
{
    // motor on
    digitalWrite(p_m_pin, 1);

    // wait for piston to return
    while (!digitalRead(p_pin));

    // turn motor off
    digitalWrite(p_m_pin, 0);
}

void Handler::fire_n(int count)
{
    // reset piston
    piston_back();

    // turn on motor
    digitalWrite(p_m_pin, 1);

    // fire for count times
    for (int i = 0; i < count; i++)
    {
        while (digitalRead(p_pin));  // wait for piston to leave
        while (!digitalRead(p_pin)); // wait for piston to return
    }

    // turn motor off again
    digitalWrite(p_m_pin, 0);
}

// utility functions
void Handler::update_states()
{
    motor_trigger = !digitalRead(m_t_pin);

    trigger = !digitalRead(t_pin);
    jammer = !digitalRead(j_pin);
    mag = !digitalRead(m_pin);
}

void Handler::update_functionality()
{
    bool peripherals_save = jammer && mag;

    // check if firing
    if (peripherals_save && motor_trigger && trigger)
    {
        firing = true;
        switch (fire_mode)
        {
            case 0:  // full auto
            {
                // turn motor on
                digitalWrite(p_m_pin, 1);
                break;
            }
            case 1:
            {
                fire_n(salvo_count);  // fire salvo
                delay(salvo_sleep);
                break;
            }
            case 2:
            {
                fire_n(1); // fire once
                delay(salvo_sleep);
                break;
            }
            default:
            {
                // turn motor off
                digitalWrite(p_m_pin, false);
                firing = false;
            }
        }
    }
    else
    {
        // check if piston is back
        if (!digitalRead(p_pin))
        {
            // if not, put it to its default position
            piston_back();
        }
        // turn motor off
        digitalWrite(p_m_pin, false);
        firing = false;
    }
}

// getters
bool Handler::get_motor_trigger()
{
    return motor_trigger;
}

bool Handler::get_biometrics()
{
    return biometrics;
}

int Handler::get_salvo_count()
{
    return salvo_count;
}

int Handler::get_fire_mode()
{
    return fire_mode;
}

bool Handler::get_trigger()
{
    return trigger;
}

bool Handler::get_jammer()
{
    return jammer;
}

bool Handler::get_mag()
{
    return mag;
}

void Handler::get_as_json(char *buffer)
{
    sprintf(
        buffer,
        "{\"mag\": %s, \"jammer\": %s, \"biometrics\": %s, \"motor_trigger\": %s, \"trigger\": %s, \"fire_mode\": %d, \"salvo_count\": %d}",
        charBoolean(mag),
        charBoolean(jammer),
        charBoolean(biometrics),
        charBoolean(motor_trigger),
        charBoolean(trigger),
        fire_mode,
        salvo_count
        );
}


// setters
bool Handler::set_fire_mode(int mode)
{
    // make sure to get the latest state
    update_states();

    if (!biometrics)  // not authorized
    {
        return false;
    }

    // set mode
    fire_mode = mode;

    // success
    return true;
}

bool Handler::set_salvo_count(int count)
{
    // make sure to get the latest state
    update_states();

    if (!biometrics)  // not authorized
    {
        return false;
    }

    // set count
    salvo_count = count;

    // success
    return true;
}
