
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WiFiControl.h"
#include "ChigoIRControl.h"
#include "WebServerControl.h"


const char *ssid = "Drive The Classic";
const char *password = "L4nci4Fulvi4.-";

ESP8266WebServer server(80);
WiFiControl wifi(ssid, password);
ChigoIRControl chigoIR(4); // D2 pin
WebServerControl web(server, chigoIR, wifi);

void setup()
{
  Serial.begin(9600);
  chigoIR.begin();
  web.begin();
  Serial.println("Web server started");
}

void loop()
{
  web.handleClient();
}
