/**
 * @file oled.hpp
 * @author Nilusink
 * @brief utility functions for the oled
 * @version 0.8
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <U8g2lib.h>


#define DART_SPEED 15  // m/s
#define G 9.81  // m/s²


namespace OLED
{
    extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

    /**
     * @brief setup the display
     * 
     */
    void setup();

    /**
     * @brief calculate the distance the dart will fly
     * 
     * @param angle weapon angle in deg
     * @return double distance in m
     */
    double calculate_distance(double angle);

    /**
     * @brief update the builtin oled
     * 
     * @param salvo how many darts per salvo (0 - auto)
     * @param angle weapon angle in deg
     * @param shots_left mag darts left
     */
    void update_display(uint8_t salvo, double angle, uint8_t shots_left);
};
