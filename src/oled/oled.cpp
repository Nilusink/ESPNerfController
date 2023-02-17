#include "oled.hpp"
#include <cmath>


U8G2_SH1106_128X64_NONAME_F_HW_I2C OLED::u8g2(U8G2_R0);


void OLED::setup()
{
    u8g2.begin();
    u8g2.setFont(u8g2_font_ncenB08_tr);
}


double OLED::calculate_distance(double angle)
{
    double rad_ang = angle * (M_PI / 180);  // convert to radian

    double y_part = sin(rad_ang) * DART_SPEED;  // y part of the vleocity
    double x_part = cos(rad_ang) * DART_SPEED;

    double y_max = pow(y_part, 2) / (2 * G);  // maximum height
    double t = 2 * sqrt((2 * y_max ) / G); // flight time

    double x_dist = x_part * t;  // x distance

    return x_dist;
}


void OLED::update_display(uint8_t salvo, double angle, uint8_t shots_left)
{
    double distance = calculate_distance(angle);  // calculate distance from given angle
    u8g2.firstPage();

    // angle
    char buff[64];
    sprintf(buff, "%.0f deg", angle);

    u8g2.drawStr(0, 10, buff);

    // distance
    sprintf(buff, "%.1f m", distance);
    u8g2.drawStr(0, 64, buff);

    // salvo
    if (salvo == 0)
    {
        sprintf(buff, "auto");
    }
    else
    {
        sprintf(buff, "salv %i", salvo);
    }
    u8g2.drawStr(100, 10, buff);

    // shots left
    sprintf(buff, "mag: %i", shots_left);
    u8g2.drawStr(90, 64, buff);

    u8g2.nextPage();
}


