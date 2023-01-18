#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>


#define SSID "Nerfinator"
#define PWD "nERFiNATOR8080"


AsyncWebServer server(80);


bool getBiometricsState()
{
  return true;
}

bool getJammerState()
{
  return true;
}

bool getMagState()
{
  return true;
}


const char* charBoolean(bool b)
{
  return b ? "true" : "false";
}


void setup()
{
  Serial.begin(9600);

  WiFi.softAP(SSID, PWD);
  IPAddress IP = WiFi.softAPIP();

  Serial.print("AP IP: "); Serial.println(IP);
  Serial.print("Local IP: "); Serial.println(WiFi.localIP());

  // request stuff
  server.on("/state", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    // get status
    bool bio, jammer, mag;
    bio = getBiometricsState();
    jammer = getJammerState();
    mag = getMagState();

    // "convert" to json
    char buff[100];
    sprintf(buff, "{\"mag\": %s, \"jammer\": %s, \"biometrics\": %s", charBoolean(mag), charBoolean(jammer), charBoolean(bio));

    // send response
    request->send_P(200, "application/json", buff);
  });

  // start server
  server.begin();
}


void loop()
{
  // do weapon stuff
}
