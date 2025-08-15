#ifndef WIFI_CONTROL_H
#define WIFI_CONTROL_H

#include <ESP8266WiFi.h>


#include <EEPROM.h>
#include <ESP8266WebServer.h>

class WiFiControl {
public:
    WiFiControl();
    void connect();
    void startConfigPortal(ESP8266WebServer& server);
    bool hasCredentials();
    void saveCredentials(const String& ssid, const String& password);
    void clearCredentials();
    void loadCredentials();
    String getSSID();
    String getPassword();
private:
    String ssid;
    String password;
    void setupAP();
};

#endif // WIFI_CONTROL_H
