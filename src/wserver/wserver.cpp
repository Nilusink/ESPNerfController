#include "wserver.hpp"
#include "weaponhandler/weaponhandler.hpp"


// Hotspot configuration
AsyncWebServer WServer::server(80);
IPAddress WServer::apIP(10, 10, 10, 1);


void WServer::setup()
{
    // create wifi hotspot
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(SSID, WPWD);

    // add routes
    server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        // send status
        char buff[255];
        wpn::handler.get_as_json(buff);

        request->send_P(200, "application/json", buff);
    });

    server.begin();
}
