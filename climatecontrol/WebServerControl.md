# WebServerControl modul

Ez a modul felelős az ESP8266 webkiszolgáló kezeléséért, a klímavezérlő és a WiFi modul integrációjáért.

## Fő felelősségek
- HTTP végpontok kezelése: /, /on, /off, /set
- Webes UI kiszolgálása
- Kliens kérések kezelése

## Használat

1. Hozd létre a szükséges példányokat a fő .ino-ban:

```cpp
#include "WebServerControl.h"

ESP8266WebServer server(80);
WiFiControl wifi(ssid, password);
ChigoIRControl chigoIR(4);
WebServerControl web(server, chigoIR, wifi);
```

2. A setup-ban hívd meg:
```cpp
web.begin();
```

3. A loop-ban hívd meg:
```cpp
web.handleClient();
```

## Fájlok
- WebServerControl.h
- WebServerControl.cpp

## SRP
Ez a modul kizárólag a webes működésért felel, így megfelel az SRP-nek.
