# SPIFFS Weblap Integráció

Ez a dokumentum leírja, hogyan integráljuk a fejlett UI weblapot az Arduino ESP8266 projektbe SPIFFS használatával.

## Előfeltételek

1. **Arduino IDE** telepítve
2. **ESP8266 board package** telepítve az Arduino IDE-ben
3. **ESP8266FS plugin** telepítve (SPIFFS adatok feltöltéséhez)

## ESP8266FS Plugin Telepítése

1. Töltsd le az ESP8266FS plugint: https://github.com/esp8266/arduino-esp8266fs-plugin
2. Csomagold ki és helyezd el az Arduino IDE tools mappájában:
   - Windows: `C:\Users\{username}\Documents\Arduino\tools\ESP8266FS\tool\esp8266fs.jar`
3. Indítsd újra az Arduino IDE-t

## Használat

### 1. Kód feltöltése

1. Nyisd meg a `climatecontrol/climatecontrol.ino` fájlt az Arduino IDE-ben
2. Állítsd be a WiFi hálózat nevét és jelszavát:
   ```cpp
   const char *ssid = "YOUR_SSID";     // Helyettesítsd a saját WiFi neveddel
   const char *password = "YOUR_PASSWORD"; // Helyettesítsd a saját WiFi jelszavaddal
   ```
3. Válaszd ki a megfelelő ESP8266 board típust és portot
4. Töltsd fel a kódot az ESP8266-ra

### 2. SPIFFS Adatok Feltöltése

1. Az Arduino IDE-ben menj a **Tools > ESP8266 Sketch Data Upload** menüpontra
2. Várd meg, amíg a feltöltés befejeződik
3. Ez feltölti a `data/` mappában található összes fájlt az ESP8266 SPIFFS fájlrendszerére

### 3. Eszköz Tesztelése

1. Nyisd meg a Serial Monitor-t (9600 baud)
2. Az ESP8266 újraindítása után látni fogod a kapcsolódási információkat
3. Jegyezd fel az ESP8266 IP címét
4. Nyisd meg a böngészőben: `http://[ESP8266_IP_CIME]`

## Funkciók

A weblap a következő funkciókat biztosítja:

- **Modern UI**: Reszponzív design, sötét/világos téma
- **Többnyelvű támogatás**: Magyar és angol
- **Időjárás animációk**: Vizuális effektek
- **Klímavezérlés**:
  - Be/kikapcsolás
  - Hőmérséklet beállítása (18-30°C)
  - Üzemmód váltás (fűtés, párátlanítás, ventilátor, hűtés)
  - Légáramlás beállítása
  - Ventilátor sebesség beállítása

## API Végpontok

A weblap a következő API végpontokat használja:

- `GET /status` - Eszköz állapot lekérdezése
- `GET /on` - Klíma bekapcsolása
- `GET /off` - Klíma kikapcsolása
- `GET /set?temp=XX` - Hőmérséklet beállítása
- `GET /setmode?mode=X` - Üzemmód beállítása (1=fűtés, 2=párátlanítás, 3=ventilátor, 4=hűtés)
- `GET /setairflow?airflow=X` - Légáramlás beállítása (0=kikapcsolva, 1=fix, 2=mozgó)
- `GET /setfan?fan=X` - Ventilátor sebesség (0=auto, 1=alacsony, 2=közepes, 3=magas)

## Hibaelhárítás

### SPIFFS Mount Failed
Ha a "SPIFFS mount failed" hibaüzenetet látod:
1. Ellenőrizd, hogy az ESP8266FS plugin megfelelően telepítve van
2. Próbáld meg újra feltölteni a SPIFFS adatokat
3. Ellenőrizd, hogy van-e elegendő memória az ESP8266-on

### Fájlok nem töltődnek be
1. Ellenőrizd a Serial Monitor üzeneteket
2. Győződj meg róla, hogy a fájlok a `data/` mappában vannak
3. Próbáld meg újra feltölteni a SPIFFS adatokat

### WiFi kapcsolódási problémák
1. Ellenőrizd a WiFi hálózat nevét és jelszavát
2. Győződj meg róla, hogy az ESP8266 a WiFi hatótávolságában van
3. Próbáld meg újraindítani az ESP8266-ot

## Fejlesztés

Ha módosítod a weblap fájljait:
1. Mentsd el a változtatásokat a `ui/` mappában
2. Másold át a fájlokat a `data/` mappába
3. Töltsd fel újra a SPIFFS adatokat az "ESP8266 Sketch Data Upload" funkcióval
