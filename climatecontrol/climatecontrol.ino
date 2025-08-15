#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>  // Új include
#include "WiFiControl.h"
#include "ChigoIRControl.h"
#include "WebServerControl.h"

// Pin definíciók
#define RESET_BUTTON_PIN 5  // D1 pin (GPIO5) - reset gomb

ESP8266WebServer server(80);
WiFiControl wifi;
ChigoIRControl chigoIR(4); // D2 pin
WebServerControl web(server, chigoIR, wifi);

// Reset gomb változók
unsigned long buttonPressTime = 0;
bool buttonPressed = false;
const unsigned long RESET_HOLD_TIME = 3000; // 3 másodperc tartás a resethez

void setup()
{
  Serial.begin(9600);
  Serial.println("=== Chigo Climate Control indítása ===");
  
  // Reset gomb beállítása
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
  Serial.println("Reset gomb konfiguráció: D1 pin (3 mp tartás a WiFi reset-hez)");
  
  chigoIR.begin();
  
  // Debug információk
  Serial.print("SSID: '");
  Serial.print(wifi.getSSID());
  Serial.println("'");
  Serial.print("Password length: ");
  Serial.println(wifi.getPassword().length());
  Serial.print("Has credentials: ");
  Serial.println(wifi.hasCredentials() ? "YES" : "NO");
  
  // Opció: WiFi adatok törlése soros port használatával
  Serial.println("Ha törölni szeretnéd a WiFi beállításokat, küldd: 'CLEAR_WIFI'");
  Serial.println("Vagy tartsd nyomva a reset gombot 3 másodpercig");
  
  if (!wifi.hasCredentials()) {
    Serial.println("Nincs mentett WiFi konfiguráció, konfigurációs portál indítása...");
    wifi.startConfigPortal(server);
    Serial.println("WiFi konfigurációs portál indítva.");
    Serial.println("Csatlakozz a 'ChigoSetup' hálózathoz és látogasd meg a 192.168.4.1 címet");
  } else {
    Serial.println("Mentett WiFi konfiguráció található, csatlakozás...");
    wifi.connect();
    
    // mDNS indítása WiFi csatlakozás után
    if (MDNS.begin("chigocontrol")) {
      Serial.println("mDNS responder started");
      Serial.println("Eszköz elérhető: http://chigocontrol.local");
      MDNS.addService("http", "tcp", 80);
    }
    
    web.begin();
    Serial.println("Web server started");
  }
}

void loop()
{
  server.handleClient();
  MDNS.update();  // mDNS frissítése
  
  // Reset gomb figyelése
  handleResetButton();
  
  // Soros port parancsok figyelése
  if (Serial.available()) {
    String command = Serial.readString();
    command.trim();
    if (command == "CLEAR_WIFI") {
      Serial.println("WiFi beállítások törlése...");
      wifi.clearCredentials();
      Serial.println("Újraindítás...");
      delay(1000);
      ESP.restart();
    }
  }
}

void handleResetButton() {
  bool currentButtonState = digitalRead(RESET_BUTTON_PIN) == LOW; // LOW = lenyomva (pull-up miatt)
  
  if (currentButtonState && !buttonPressed) {
    // Gomb lenyomva
    buttonPressed = true;
    buttonPressTime = millis();
    Serial.println("Reset gomb lenyomva...");
  } else if (!currentButtonState && buttonPressed) {
    // Gomb felengedve
    buttonPressed = false;
    unsigned long pressDuration = millis() - buttonPressTime;
    
    if (pressDuration >= RESET_HOLD_TIME) {
      Serial.println("WiFi reset aktiválva!");
      wifi.clearCredentials();
      Serial.println("WiFi beállítások törölve. Újraindítás...");
      delay(1000);
      ESP.restart();
    } else {
      Serial.print("Reset gomb felengedve (");
      Serial.print(pressDuration);
      Serial.println(" ms) - túl rövid a resethez");
    }
  } else if (currentButtonState && buttonPressed) {
    // Gomb folyamatosan nyomva
    unsigned long currentPressDuration = millis() - buttonPressTime;
    
    // Visszajelzés minden másodpercben
    if (currentPressDuration >= 1000 && currentPressDuration < RESET_HOLD_TIME) {
      static unsigned long lastFeedback = 0;
      if (millis() - lastFeedback >= 1000) {
        Serial.print("Reset gomb nyomva: ");
        Serial.print(currentPressDuration / 1000);
        Serial.print("/");
        Serial.print(RESET_HOLD_TIME / 1000);
        Serial.println(" mp");
        lastFeedback = millis();
      }
    }
  }
}
