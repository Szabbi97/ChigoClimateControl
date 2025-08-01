
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WiFiControl.h"
#include "ChigoIRControl.h"
#include "WebServerControl.h"


const char *ssid = "YOUR_WIFI_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

ESP8266WebServer server(80);
WiFiControl wifi(ssid, password);
ChigoIRControl chigoIR(4); // D2 pin
WebServerControl web(server, chigoIR, wifi);

void setup()
{
  Serial.begin(9600);
  chigoIR.begin();
  web.begin();
  Serial.println("Webszerver elindítva");
}

void loop()
{
  web.handleClient();
}
