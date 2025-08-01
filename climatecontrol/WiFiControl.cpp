
#include "WiFiControl.h"
#include <Arduino.h>

WiFiControl::WiFiControl(const char *ssid, const char *password) : ssid(ssid), password(password) {}

void WiFiControl::connect() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Csatlakozás Wi-Fi-hez");
    int tries = 0;
    while (WiFi.status() != WL_CONNECTED && tries < 30) {
        delay(500);
        Serial.print(".");
        tries++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nCsatlakozva: " + WiFi.localIP().toString());
    } else {
        Serial.println("\nWiFi kapcsolat sikertelen.");
    }
}
