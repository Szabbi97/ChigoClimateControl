
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WiFiControl.h"
#include "ChigoIRControl.h"
#include "WebServerControl.h"



ESP8266WebServer server(80);
WiFiControl wifi;
ChigoIRControl chigoIR(4); // D2 pin
WebServerControl web(server, chigoIR, wifi);

void setup()
{
  Serial.begin(9600);
  Serial.println("=== Chigo Climate Control indítása ===");
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
  
  if (!wifi.hasCredentials()) {
    Serial.println("Nincs mentett WiFi konfiguráció, konfigurációs portál indítása...");
    wifi.startConfigPortal(server);
    Serial.println("WiFi konfigurációs portál indítva.");
    Serial.println("Csatlakozz a 'ChigoSetup' hálózathoz és látogasd meg a 192.168.4.1 címet");
  } else {
    Serial.println("Mentett WiFi konfiguráció található, csatlakozás...");
    wifi.connect();
    web.begin();
    Serial.println("Web server started");
  }
}

void loop()
{
  server.handleClient();
  
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
