

#include "WiFiControl.h"
#include <Arduino.h>

#define EEPROM_SIZE 96
#define SSID_ADDR 0
#define PASS_ADDR 32

WiFiControl::WiFiControl() {
    EEPROM.begin(EEPROM_SIZE);
    loadCredentials();
}

bool WiFiControl::hasCredentials() {
    return ssid.length() > 0 && password.length() > 0;
}

void WiFiControl::saveCredentials(const String& ssid_, const String& password_) {
    ssid = ssid_;
    password = password_;
    for (int i = 0; i < 32; i++) {
        EEPROM.write(SSID_ADDR + i, i < ssid.length() ? ssid[i] : 0);
        EEPROM.write(PASS_ADDR + i, i < password.length() ? password[i] : 0);
    }
    EEPROM.commit();
}

void WiFiControl::clearCredentials() {
    ssid = "";
    password = "";
    for (int i = 0; i < 32; i++) {
        EEPROM.write(SSID_ADDR + i, 0);
        EEPROM.write(PASS_ADDR + i, 0);
    }
    EEPROM.commit();
    Serial.println("WiFi hitelesítési adatok törölve.");
}

void WiFiControl::loadCredentials() {
    char ssidBuf[33], passBuf[33];
    for (int i = 0; i < 32; i++) {
        ssidBuf[i] = EEPROM.read(SSID_ADDR + i);
        passBuf[i] = EEPROM.read(PASS_ADDR + i);
    }
    ssidBuf[32] = 0;
    passBuf[32] = 0;
    ssid = String(ssidBuf);
    password = String(passBuf);
    ssid.trim();
    password.trim();
    
    // Ha az SSID vagy jelszó csak nem-nyomtatható karaktereket tartalmaz, töröljük
    if (ssid.length() > 0) {
        bool hasValidChars = false;
        for (int i = 0; i < ssid.length(); i++) {
            if (ssid[i] >= 32 && ssid[i] <= 126) {
                hasValidChars = true;
                break;
            }
        }
        if (!hasValidChars) ssid = "";
    }
    
    if (password.length() > 0) {
        bool hasValidChars = false;
        for (int i = 0; i < password.length(); i++) {
            if (password[i] >= 32 && password[i] <= 126) {
                hasValidChars = true;
                break;
            }
        }
        if (!hasValidChars) password = "";
    }
}

String WiFiControl::getSSID() { return ssid; }
String WiFiControl::getPassword() { return password; }

void WiFiControl::connect() {
    if (!hasCredentials()) return;
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("Connecting to Wi-Fi");
    int tries = 0;
    while (WiFi.status() != WL_CONNECTED && tries < 30) {
        delay(500);
        Serial.print(".");
        tries++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected: " + WiFi.localIP().toString());
    } else {
        Serial.println("\nWiFi connection failed.");
    }
}

void WiFiControl::setupAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP("ChigoSetup");
    Serial.println("Access Point started: ChigoSetup");
    Serial.println("IP: " + WiFi.softAPIP().toString());
}

void WiFiControl::startConfigPortal(ESP8266WebServer& server) {
    setupAP();
    server.on("/", [&]() {
        String html = "<html><body><h2>WiFi beállítás</h2>"
            "<form method='POST' action='/save'>"
            "SSID: <input name='ssid'><br>"
            "Jelszó: <input name='password' type='password'><br>"
            "<input type='submit' value='Mentés'>"
            "</form></body></html>";
        server.send(200, "text/html", html);
    });
    server.on("/save", [&]() {
        if (server.hasArg("ssid") && server.hasArg("password")) {
            saveCredentials(server.arg("ssid"), server.arg("password"));
            server.send(200, "text/html", "<html><body><h2>Mentve! Indítsd újra az eszközt!</h2></body></html>");
            delay(2000);
            ESP.restart();
        } else {
            server.send(400, "text/html", "<html><body>Hiányzó adatok!</body></html>");
        }
    });
    server.begin();
    Serial.println("Config portal started.");
}
