/**
 * @file wserver.hpp
 * @author Nilusink
 * @brief Webserver for the Andoid app
 * @version 0.8
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


// configurable
#define SSID "Nerfinator"
#define WPWD "---"


namespace WServer
{
    extern AsyncWebServer server;
    extern IPAddress apIP;

    /**
     * @brief initialize the server
     * 
     */
    void setup();
}