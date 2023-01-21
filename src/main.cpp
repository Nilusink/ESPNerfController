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
#define jammer_pin D7
#define mag_pin D6
#define motor_trigger_pin D5
#define trigger_pin D4
#define piston_pin D3

#define piston_motor_pin D0


wpn::Handler handler(
  jammer_pin,
  mag_pin,
  motor_trigger_pin,
  trigger_pin,
  piston_pin,
  piston_motor_pin
);


IPAddress apIP(10, 10, 10, 1);


void handle_post(AsyncWebServerRequest *request) {
  Serial.println("ACTION!");

  bool success = false;

  int params = request->params();
  for (int i = 0; i < params; i++) {
    AsyncWebParameter* p = request->getParam(i);

    String param_name = p->name();
    String param_value = p->value();


    Serial.printf("POST[%s]: %s\n", param_name.c_str(), param_value.c_str());

    // match parameters
    if (param_name.equals("mode"))
    {
      handler.set_fire_mode(param_value.toInt());
      success = true;
    }
    else if (param_name.equals("salvo"))
    {
      handler.set_salvo_count(param_value.toInt());
      success = true;
    }
  }

  request->send_P(200,  "application/json", success ? "{\"success\": true}" : "{\"success\": false}");
}


void setup()
{
  // initialize serial connection
  Serial.begin(9600);
  Serial.println("beginning");

  // create wifi hotspot
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID, PWD);

  Serial.println("wifi  up");

  // request stuff
  server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    Serial.println("getting");
    // send status
    char buff[255];
//    handler.get_as_json(buff);

    Serial.println(buff);

    request->send_P(200, "application/json", buff);
  });

  // post requests
  server.on("/set/", HTTP_POST, handle_post);

  // start server
  server.begin();

  Serial.println("init done");
}


void loop()
{
  handler.update_states();
  handler.update_functionality();
  delay(10);
}
