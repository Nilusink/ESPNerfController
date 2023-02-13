#include "weaponhandler.hpp"


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
    m_t_pin = motor_trigger_pin;
    p_m_pin = piston_motor_pin;
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
    Serial.println("resetting piston");
    // motor on
    analogWrite(p_m_pin, 180);

    // wait for piston to return
    while (digitalRead(p_pin)) {delay(2);}

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
        while (digitalRead(p_pin)) {delay(10);}  // wait for piston to leave

        if (i == count - 1) {break;}  // on the last rotation, leave the piston out
        else {while (!digitalRead(p_pin)) {delay(10);}}  // wait for piston to return
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
    bool piston_state = digitalRead(p_pin);

//    Serial.print("per: "); Serial.print(peripherals_save); Serial.print("\ttriggers: "); Serial.print(motor_trigger && trigger); Serial.print("\tpiston: "); Serial.println(piston_state);

    // check if firing
    if (peripherals_save && motor_trigger && trigger)
    {
        firing = true;
        digitalWrite(p_m_pin, true);
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
        Serial.print("off: "); Serial.println(piston_state);
        // check if piston is back
        if (piston_state)
        {
            digitalWrite(p_m_pin, false);
            delay(500);

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


Handler wpn::handler(
    JAMMER_PIN,
    MAG_PIN,
    MOTOR_TRIGGER_PIN,
    TRIGGER_PIN,
    PISTON_PIN,
    PISTONR_MOTOR_PIN
);
