#include <Arduino.h>


#define PISTON_PIN D1
#define PISTON_SENSOR_PIN D5
#define TRIGGER_PIN D7


void setup()
{
    Serial.begin(9600);

    pinMode(PISTON_PIN, OUTPUT);

    pinMode(PISTON_SENSOR_PIN, INPUT);
    pinMode(TRIGGER_PIN, INPUT);

    Serial.println("init done");
}


void piston_back()
{
    analogWrite(PISTON_PIN, 200);

    // wait for piston to come back
    while (digitalRead(PISTON_SENSOR_PIN)) {delay(2);}

    // turn off piston
    digitalWrite(PISTON_PIN, 0);
}


void fire_n(int count)
{
    // reset piston
    piston_back();

    // turn on motor
    digitalWrite(PISTON_PIN, 1);

    // fire for count times
    for (int i = 0; i < count; i++)
    {
        while (digitalRead(PISTON_SENSOR_PIN)) {delay(10);}  // wait for piston to leave

        if (i == count - 1) {break;}  // on the last rotation, leave the piston out
        else {while (!digitalRead(PISTON_SENSOR_PIN)) {delay(10);}}  // wait for piston to return
    }

    // turn motor off again
    digitalWrite(PISTON_PIN, 0);
}


void loop()
{
    bool switch_state = !digitalRead(PISTON_SENSOR_PIN);
    bool trigger = !digitalRead(TRIGGER_PIN);

    if (trigger)
    {   // shoot
        Serial.println("shooting");
        fire_n(4);
        delay(500);
        piston_back();
    }
    else
    {   // still
        digitalWrite(PISTON_PIN, 0);

        if (!switch_state)
        {   // piston not back
            piston_back();
        }

    }
}
