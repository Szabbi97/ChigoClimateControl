# Időjárás API Beállítás

## OpenWeatherMap API Kulcs

A weblap időjárás funkcióihoz OpenWeatherMap API kulcs szükséges.

### API Kulcs Beszerzése:

1. **Regisztráció**: Menj a https://openweathermap.org/api oldalra
2. **Ingyenes fiók**: Hozz létre egy ingyenes fiókot
3. **API kulcs**: A "API keys" menüpontban találod a kulcsodat

### API Kulcs Beállítása:

#### Ha beépített verziót használod:
1. Nyisd meg: `ui/scripts/weather.js`
2. Keress rá: `const apiKey = 'YOUR_API_KEY';`
3. Helyettesítsd `YOUR_API_KEY`-t a saját kulcsoddal
4. Futtasd: `tools/generate_web_resources.py`
5. Töltsd fel a sketch-et

#### Ha SPIFFS verziót használod:
1. Nyisd meg: `ui/scripts/weather.js` és `climatecontrol/data/scripts/weather.js`
2. Mindkét fájlban: `const apiKey = 'YOUR_API_KEY';`
3. Helyettesítsd `YOUR_API_KEY`-t a saját kulcsoddal
4. Töltsd fel a SPIFFS adatokat: Tools > ESP8266 Sketch Data Upload

### Példa:
```javascript
const apiKey = 'abc123def456ghi789jkl012mno345pq';
```

### Biztonsági Figyelmeztetés:
- ⚠️ **Ne commitáld a valódi API kulcsot Git repository-ba!**
- 🔒 **Használj environment változókat vagy külön config fájlt**
- 📝 **Az API kulcs free verzió: 1000 hívás/hó**

### Opcionális: API kulcs nélküli működés
Ha nem szeretnéd használni az időjárás funkciót:
- Az API kulcs `YOUR_API_KEY` marad
- A weblap minden más funkció működni fog
- Csak az időjárás effektek nem jelennek meg
