/**
 * @file gyro.hpp
 * @author Nilusink
 * @brief useful functions for the gyrometic sensor
 * @version 0.8
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


namespace Gyro
{
    extern Adafruit_MPU6050 mpu;

    /**
     * @brief initialize the sensor
     * 
     */
    bool setup();

    /**
     * @brief get the pitch angle
     * 
     * @return double
     */
    double get_angle();
}

