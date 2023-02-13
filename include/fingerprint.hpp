/**
 * @file fingerprint.hpp
 * @author Nilusink
 * @brief Defines interface to the built-in fingerprint reader
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <Adafruit_Fingerprint.h>


namespace Finger
{
    // use Serial2 as the interface
    extern Adafruit_Fingerprint finger;

    bool setup();

    int getFingerprintID();

}