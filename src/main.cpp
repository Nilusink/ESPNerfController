#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "weaponhandler.h"


// configuration
#define SSID "Nerfinator"
#define PWD "nERFiNATOR8080"

AsyncWebServer server(80);


// weapon handler setup
wpn::Handler handler(12, 11);


IPAddress apIP(10, 10, 10, 1);


void setup()
{
  // initialize serial connection
  Serial.begin(9600);

  // create wifi hotspot
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID, PWD);

  // request stuff
  server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    // send status
    char buff[100];
    handler.get_as_json(buff);

    request->send_P(200, "application/json", buff);
  });

  // start server
  server.begin();
}


void loop()
{
  // do weapon stuff
}
