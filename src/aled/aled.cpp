/**
 * @file aled.hpp
 * @author Nilusink
 * @version 1.0
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <Arduino.h>
#include "aled.hpp"

CRGB ALED::leds1[NUM_LEDS];
CRGB ALED::leds2[NUM_LEDS];


void ALED::setup(uint8_t brightness)
{
    FastLED.addLeds<WS2812, DATA_PIN1, RGB>(leds1, NUM_LEDS);
    FastLED.addLeds<WS2812, DATA_PIN2, RGB>(leds2, NUM_LEDS);
    FastLED.setBrightness(brightness);
}

void ALED::fadeall()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds1[i].nscale8(250);
        leds2[i].nscale8(250);
    }
}

void ALED::ripple(CHSV color, uint8_t max_brightness, double d, bool invert)
{
    CHSV now_col(color.hue, color.s, max_brightness);

    int i0, i1;
    for (int i = 0; i < NUM_LEDS+1; i++)
    {
        // set current led to max_brightness of color
        i0 = i;
        if (invert)
        {
            i0 = NUM_LEDS - i;
        }
        leds1[i0] = now_col;
        leds2[i0] = now_col;

        // set last leds to perm color
        if (i > 0)
        {
            i0--;
            leds1[i0] = color;
            leds2[i0] = color;
        }

        FastLED.show();

        delay(d);
    }
}

void ALED::blink(CHSV color1, CHSV color2, double d, uint n)
{
    for (int x = 0; x < n; x++)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds1[i] = color1;
            leds2[i] = color1;
        }

        FastLED.show();
        delay(d);

        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds1[i] = color2;
            leds2[i] = color2;
        }
        FastLED.show();
        delay(d);
    }
}
