#pragma once
#include <ESP8266WebServer.h>
#include "ChigoIRControl.h"
#include "WiFiControl.h"

class WebServerControl {
public:
    WebServerControl(ESP8266WebServer& server, ChigoIRControl& chigoIR, WiFiControl& wifi);
    void begin();
    void handleClient();

private:
    ESP8266WebServer& server;
    ChigoIRControl& chigoIR;
    WiFiControl& wifi;

    void handleRoot();
    void handleStatus();
    void handleOn();
    void handleOff();
    void handleSet();
    void handleSetMode();
    void handleSetAirflow();
    void handleSetFan();
};
