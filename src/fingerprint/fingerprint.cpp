#include "fingerprint.hpp"


Adafruit_Fingerprint Finger::finger = Adafruit_Fingerprint(&Serial2);



bool Finger::setup()
{
    Serial.println("Initializing fingerprint sensor...");

    // set the data rate for the sensor serial port
    finger.begin(57600);
    delay(5);

    if (finger.verifyPassword())
    {
        Serial.println("Found fingerprint sensor!");
    }
    else
    {
        Serial.println("Did not find fingerprint sensor :(");
        return false;
    }

    // check if the fingerprint sensor has available templates
    finger.getTemplateCount();

    if (finger.templateCount == 0)
    {
        Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
        return false;
    }
    else
    {
        Serial.println("Waiting for valid finger...");
        Serial.print("Sensor contains ");
        Serial.print(finger.templateCount);
        Serial.println(" templates");
    }

    // turn on induction for sensor
    pinMode(INDUCTION_PIN, OUTPUT);
    pinMode(WAKEUP_PIN, INPUT);

    digitalWrite(INDUCTION_PIN, HIGH);

    return true;
}


int Finger::getFingerprintID()
{
    uint8_t p = finger.getImage();

    // check if reading successful
    switch (p)
    {
    case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;

    case FINGERPRINT_NOFINGER:
        // Serial.println("No finger detected");
        return -1;

    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return -1;

    case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        return -1;

    default:
        Serial.println("Unknown error");
        return -1;
    }

    // convert fingerprint
    p = finger.image2Tz();
    switch (p)
    {
    case FINGERPRINT_OK:
        Serial.println("Image converted");
        break;

    case FINGERPRINT_IMAGEMESS:
        Serial.println("Image too messy");
        return -2;

    case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        return -2;

    case FINGERPRINT_FEATUREFAIL:
        Serial.println("Could not find fingerprint features");
        return -2;

    case FINGERPRINT_INVALIDIMAGE:
        Serial.println("Could not find fingerprint features");
        return -2;

    default:
        Serial.println("Unknown error");
        return -2;
    }

    // find match
    p = finger.fingerSearch();
    if (p == FINGERPRINT_OK)
    {
        Serial.println("Found a print match!");
    }
    else if (p == FINGERPRINT_PACKETRECIEVEERR)
    {
        Serial.println("Communication error");
        return -3;
    }
    else if (p == FINGERPRINT_NOTFOUND)
    {
        Serial.println("Did not find a match");
        return -3;
    }
    else
    {
        Serial.println("Unknown error");
        return -3;
    }

    // found a match!
    Serial.print("Found ID #");
    Serial.print(finger.fingerID);
    Serial.print(" with confidence of ");
    Serial.println(finger.confidence);

    return finger.fingerID;
}
