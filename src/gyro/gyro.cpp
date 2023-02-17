#include "gyro.hpp"


Adafruit_MPU6050 Gyro::mpu;


bool Gyro::setup()
{
    // start the sensor
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        return false;
    }
    return true;
}


double Gyro::get_angle()
{
    /*
        x: down
        z: forward
    */

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // invert the angle (+up, -down) and multiply by 10, because sensor weird
    return a.acceleration.roll * -10;
}
