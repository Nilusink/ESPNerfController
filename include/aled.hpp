/**
 * @file aled.hpp
 * @author Nilusink
 * @brief a few useful functions for the built-in addressable leds
 * @version 1.0
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once
#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 25
#define CLOCK_PIN 13


namespace ALED
{
    // Define the array of leds
    extern CRGB leds[NUM_LEDS];

    /**
     * @brief setup the leds
     * 
     * @param brightness led brightness
     */
    void setup(uint8_t brightness);

    /**
     * @brief fade all led brightness
     * 
     */
    void fadeall();

    /**
     * @brief ripple into a new color
     * 
     * @param color the new color
     * @param max_brightness max ripple brightness
     * @param d delay
     */
    void ripple(CHSV color, uint8_t max_brightness, double d, bool invert = false);

    /**
     * @brief blink all leds in the current color
     * 
     * @param brightness blinking brightness
     * @param d delay
     * @param n times
     */
    void blink(CHSV color1, CHSV color2, double d, uint n);
}
