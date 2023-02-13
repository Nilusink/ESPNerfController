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

CRGB ALED::leds[NUM_LEDS];

void ALED::setup(uint8_t brightness)
{
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(brightness);
}

void ALED::fadeall()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].nscale8(250);
    }
}

void ALED::ripple(CHSV color, uint8_t max_brightness, double d, bool invert)
{
    uint8_t led_half = NUM_LEDS / 2 + 1;

    CHSV now_col(color.hue, color.s, max_brightness);

    int i0, i1;
    for (int i = 0; i < led_half; i++)
    {
        i0 = i;
        if (invert)
        {
            i0 = led_half - i;
        }

        // from beginning and end
        i1 = NUM_LEDS - 1 - i0;

        leds[i0] = now_col;
        leds[i1] = now_col;

        // set last leds to perm color
        if (i > 0)
        {
            i0--;
            i1 = NUM_LEDS - 1 - i0;

            leds[i0] = color;
            leds[i1] = color;
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
            leds[i] = color1;
        }

        FastLED.show();
        delay(d);

        for (int i = 0; i < NUM_LEDS; i++)
        {
            leds[i] = color2;
        }
        FastLED.show();
        delay(d);
    }
}

//     for (int i = 0; i < NUM_LEDS; i++)
//     {
//         // Set the i'th led to red
//         leds[i] = CHSV(hue++, 255, 255);
//         // Show the leds
//         FastLED.show();
//         // now that we've shown the leds, reset the i'th led to black
//         // leds[i] = CRGB::Black;
//         fadeall();
//         // Wait a little bit before we loop around and do it again
//         delay(10);
//     }
