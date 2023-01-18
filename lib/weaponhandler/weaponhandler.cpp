#include "weaponhandler.h"

const char *charBoolean(bool b)
{
    return b ? "true" : "false";
}


// Handler implementation
using namespace wpn;
Handler::Handler(int jammerPin, int magPin)
{
    // save pin numbers
    jPin = jammerPin;
    mPin = magPin;

    // setup pins
    pinMode(jPin, INPUT_PULLUP);
    pinMode(mPin, INPUT_PULLUP);
}

// utility functions
void Handler::updateStates()
{
    jammer = !digitalRead(jPin);
    mag = !digitalRead(mPin);
}

// getters
bool Handler::get_biometrics()
{
    return biometrics;
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
    sprintf(buffer, "{\"mag\": %s, \"jammer\": %s, \"biometrics\": %s}", charBoolean(mag), charBoolean(jammer), charBoolean(biometrics));
}
