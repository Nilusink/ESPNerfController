/**
 * @file fingerprint.hpp
 * @author Nilusink
 * @brief Defines interface to the built-in fingerprint reader
 * @version 0.8
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <Adafruit_Fingerprint.h>


#define WAKEUP_PIN 13
#define INDUCTION_PIN 15


namespace Finger
{
    // use Serial2 as the interface
    extern Adafruit_Fingerprint finger;

    /**
     * @brief initialize the fingerprint sensor
     * 
     * @return true 
     * @return false 
     */
    bool setup();

    /**
     * @brief check for reading and if correct, rurn the id of the matched fingerprint
     * 
     * @return int -3...incorrect fingerprint; -2...image error; -1...no finger; 0+...finger of id n detected
     */
    int getFingerprintID();
}