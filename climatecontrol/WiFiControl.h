#ifndef WIFI_CONTROL_H
#define WIFI_CONTROL_H

#include <ESP8266WiFi.h>

class WiFiControl {
public:
    WiFiControl(const char *ssid, const char *password);
    void connect();
private:
    const char *ssid;
    const char *password;
};

#endif // WIFI_CONTROL_H
