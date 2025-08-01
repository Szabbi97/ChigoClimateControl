

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WiFiControl.h"
#include "ChigoIRControl.h"


const char *ssid = "WIFI_SSID";
const char *password = "WIFI_PASSWORD";


ESP8266WebServer server(80);

WiFiControl wifi(ssid, password);
ChigoIRControl chigoIR(4); // D2 pin

void handleRoot()
{
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="hu">
<head>
  <meta charset="UTF-8">
  <title>Klíma vezérlés</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  
  <style>
    body { 
      font-family: sans-serif; 
      padding: 20px; 
      background: linear-gradient(to bottom, #87CEEB 0%, #98D8E8 50%, #B8E6F2 100%);
      min-height: 100vh;
      position: relative;
      overflow-x: hidden;
    }
    
    /* Felhő animációk */
    .clouds {
      position: fixed;
      top: 0;
      left: 0;
      width: 100%;
      height: 100%;
      pointer-events: none;
      z-index: 0;
    }
    
    .cloud {
      position: absolute;
      background: rgba(255, 255, 255, 0.8);
      border-radius: 50px;
      opacity: 0;
      transition: opacity 2s ease-in-out;
    }
    
    .cloud:before,
    .cloud:after {
      content: '';
      position: absolute;
      background: rgba(255, 255, 255, 0.8);
      border-radius: 50px;
    }
    
    .cloud.visible {
      opacity: 0.7;
    }
    
    @keyframes floatAcross {
      0% { 
        left: -150px; 
        opacity: 0;
      }
      10% {
        opacity: 0.7;
      }
      90% {
        opacity: 0.7;
      }
      100% { 
        left: calc(100% + 150px); 
        opacity: 0;
      }
    }
    
    @keyframes floatFromPosition {
      0% { 
        opacity: 0.7;
      }
      90% {
        opacity: 0.7;
      }
      100% { 
        left: calc(100% + 150px); 
        opacity: 0;
      }
    }
    
    .container { max-width: 400px; margin: auto; background: rgba(255, 255, 255, 0.95); border-radius: 10px; box-shadow: 0 4px 16px rgba(0,0,0,0.1); padding: 24px; position: relative; z-index: 1; backdrop-filter: blur(5px); }
    h2 { text-align: center; }
    .controls { display: flex; flex-direction: column; gap: 12px; margin-bottom: 16px; }
    button, select, input[type="submit"] {
      margin: 0;
      padding: 14px;
      font-size: 18px;
      border-radius: 6px;
      border: 1px solid #bbb;
      background: #e9e9e9;
      transition: background 0.2s;
      cursor: pointer;
    }
    button:hover, input[type="submit"]:hover { background: #d0eaff; }
    label { font-weight: bold; margin-bottom: 4px; }
    #status {
      margin-top: 20px;
      font-weight: bold;
      padding: 10px;
      border-radius: 6px;
      background: #eef;
      min-height: 32px;
      text-align: center;
    }
    .power-buttons {
      display: flex;
      gap: 16px;
      justify-content: center;
      margin-bottom: 12px;
    }
    .power-on {
      background: #7cffb0;
      color: #155724;
      border: 1px solid #7cffb0;
      font-weight: bold;
      box-shadow: 0 2px 6px #b2f7c1;
      transition: background 0.2s, box-shadow 0.2s;
    }
    .power-on:hover {
      background: #4be38c;
      box-shadow: 0 4px 12px #b2f7c1;
    }
    .power-off {
      background: #ff7b7b;
      color: #721c24;
      border: 1px solid #ff7b7b;
      font-weight: bold;
      box-shadow: 0 2px 6px #f7b2b2;
      transition: background 0.2s, box-shadow 0.2s;
    }
    .power-off:hover {
      background: #ff5252;
      box-shadow: 0 4px 12px #f7b2b2;
    }
    .slider-container {
      display: flex;
      flex-direction: column;
      align-items: center;
      margin-bottom: 18px;
    }
    .slider-label {
      font-weight: bold;
      margin-bottom: 8px;
    }
    .temp-value {
      font-size: 1.2em;
      font-weight: bold;
      margin-bottom: 8px;
      color: #1976d2;
    }
    input[type="range"] {
      width: 100%;
      accent-color: #1976d2;
      margin-bottom: 8px;
      height: 4px;
      border-radius: 4px;
      background: #e0e0e0;
      position: relative;
      z-index: 2;
    }
    /* Hide default thumb for Chrome, Safari, Edge */
    input[type="range"]::-webkit-slider-thumb {
      -webkit-appearance: none;
      appearance: none;
      width: 36px;
      height: 36px;
      border-radius: 50%;
      background: #fff center/70% no-repeat;
      border: 2px solid #bbb;
      box-shadow: 0 2px 6px #b2d7ff;
      cursor: pointer;
      transition: border-color 0.2s, box-shadow 0.2s;
    }
    input[type="range"]:focus::-webkit-slider-thumb {
      border-color: #1976d2;
      box-shadow: 0 4px 12px #b2d7ff;
    }
    /* Hide default thumb for Firefox */
    input[type="range"]::-moz-range-thumb {
      width: 36px;
      height: 36px;
      border-radius: 50%;
      background: #fff center/70% no-repeat;
      border: 2px solid #bbb;
      box-shadow: 0 2px 6px #b2d7ff;
      cursor: pointer;
      transition: border-color 0.2s, box-shadow 0.2s;
    }
    input[type="range"]:focus::-moz-range-thumb {
      border-color: #1976d2;
      box-shadow: 0 4px 12px #b2d7ff;
    }
    /* Hide default thumb for IE */
    input[type="range"]::-ms-thumb {
      width: 36px;
      height: 36px;
      border-radius: 50%;
      background: #fff center/70% no-repeat;
      border: 2px solid #bbb;
      box-shadow: 0 2px 6px #b2d7ff;
      cursor: pointer;
      transition: border-color 0.2s, box-shadow 0.2s;
    }
    /* Remove outline for Firefox */
    input[type="range"]::-moz-focus-outer {
      border: 0;
    }
    @media (max-width: 500px) {
      .container { padding: 10px; }
      button, select, input[type="submit"] { font-size: 16px; padding: 10px; }
    }
  </style>
</head>
<body>
  <!-- Animált felhők háttér -->
  <div class="clouds" id="clouds-container">
  </div>
  
  <div class="container">
    <h2>Chigo klíma vezérlés</h2>
    <div class="controls">
      <form onsubmit="return false;">
        <div class="slider-container" style="position:relative;">
          <label for="temp" class="slider-label">Hőmérséklet:</label>
          <div id="temp-value" class="temp-value">24 °C</div>
          <input
            type="range"
            id="temp"
            name="temp"
            min="18"
            max="30"
            value="24"
            oninput="updateTempValue(this.value); autoSetTemperature(this.value);"
            style="position:relative; z-index:2;"
          >
        </div>
      </form>
      
      <div class="power-buttons">
        <button class="power-on" onclick="sendCommand('/on', 'Bekapcsolás')">Bekapcsolás</button>
        <button class="power-off" onclick="sendCommand('/off', 'Kikapcsolás')">Kikapcsolás</button>
      </div>
    </div>
    <div id="status">Állapot: nincs művelet</div>
  </div>
  <script>
    // Dinamikus felhő generátor
    function createCloud(initialPosition = null, isInitial = false) {
      const cloudsContainer = document.getElementById('clouds-container');
      const cloud = document.createElement('div');
      cloud.className = 'cloud';
      
      // Véletlenszerű felhő méret és pozíció
      const size = Math.random() * 60 + 40; // 40-100px szélesség
      const height = size * 0.5; // magasság a szélesség fele
      const topPosition = Math.random() * 70 + 5; // 5-75% magasság
      const duration = Math.random() * 20 + 25; // 25-45 másodperc
      
      cloud.style.width = size + 'px';
      cloud.style.height = height + 'px';
      cloud.style.top = topPosition + '%';
      
      // Ha kezdő pozíció van megadva (oldal betöltéskor)
      if (initialPosition !== null && isInitial) {
        // Kezdő felhők: már a helyükön vannak, rögtön láthatók
        cloud.style.left = initialPosition + 'px';
        cloud.style.opacity = '0.7';
        // Folytatják az úszást a jelenlegi pozíciójukból
        const remainingDistance = window.innerWidth + 150 - initialPosition;
        const remainingDuration = (remainingDistance / (window.innerWidth + 300)) * duration;
        cloud.style.animation = `floatFromPosition ${remainingDuration}s linear`;
      } else {
        // Új felhők: balról úsznak be
        cloud.style.animation = `floatAcross ${duration}s linear`;
      }
      
      // Véletlenszerű before és after elemek (felhő alakja)
      const beforeSize = size * 0.6;
      const afterSize = size * 0.7;
      
      // Egyedi style elem minden felhőhöz
      const style = document.createElement('style');
      const cloudId = 'cloud-' + Date.now() + '-' + Math.random().toString(36).substr(2, 9);
      cloud.id = cloudId;
      
      style.textContent = `
        #${cloudId}:before {
          width: ${beforeSize}px;
          height: ${beforeSize}px;
          top: ${-beforeSize/2}px;
          left: ${size * 0.15}px;
        }
        #${cloudId}:after {
          width: ${afterSize}px;
          height: ${height}px;
          top: ${-height * 0.3}px;
          right: ${size * 0.15}px;
        }
      `;
      
      document.head.appendChild(style);
      cloudsContainer.appendChild(cloud);
      
      // Felhő eltávolítása az animáció végén
      const cleanupDuration = isInitial && initialPosition !== null ? 
        ((window.innerWidth + 150 - initialPosition) / (window.innerWidth + 300)) * duration * 1000 :
        duration * 1000;
        
      setTimeout(() => {
        if (cloud.parentNode) {
          cloud.parentNode.removeChild(cloud);
        }
        if (style.parentNode) {
          style.parentNode.removeChild(style);
        }
      }, cleanupDuration);
    }
    
    // Kezdő felhők létrehozása az oldal betöltésekor
    function createInitialClouds() {
      const numClouds = Math.floor(Math.random() * 6) + 10; // 10-15 felhő
      for (let i = 0; i < numClouds; i++) {
        // Véletlenszerű kezdő pozíció a képernyő szélességén belül (0 és window.innerWidth között)
        const initialX = Math.random() * (window.innerWidth - 100); // 100px margó a jobb oldalon
        // Azonnal létrehozás, várakozás nélkül
        createCloud(initialX, true); // true = kezdő felhő
      }
    }
    
    // Felhők folyamatos generálása
    function startCloudGeneration() {
      createCloud();
      // Következő felhő 2-5 másodperc múlva (gyors generálás)
      const nextCloudDelay = Math.random() * 3000 + 2000;
      setTimeout(startCloudGeneration, nextCloudDelay);
    }
    
    // Indítás oldal betöltésekor
    document.addEventListener('DOMContentLoaded', function() {
      console.log('DOM loaded');
      // Kezdő felhők létrehozása azonnal
      createInitialClouds();
      // Folyamatos generálás indítása azonnal
      setTimeout(startCloudGeneration, 2000); // 2 másodperc múlva indul a folyamatos generálás
    });

    function setStatus(msg, loading = false) {
      const status = document.getElementById('status');
      status.innerText = msg;
      status.style.color = loading ? "#888" : "#222";
    }

    function sendCommand(path, msg) {
      setStatus(msg + " (folyamatban...)", true);
      fetch(path)
        .then(response => response.text())
        .then(text => setStatus(text))
        .catch(() => setStatus("Hiba történt!"));
    }

    function setTemperature(val) {
      setStatus("Hőmérséklet beállítása (" + val + "°C)...", true);
      fetch('/set?temp=' + val)
        .then(response => response.text())
        .then(text => setStatus(text))
        .catch(() => setStatus("Hiba történt!"));
    }

    function updateTempValue(val) {
      document.getElementById('temp-value').innerText = val + " °C";
    }

    // Automatikus hőmérséklet beállítás csúszka változásra
    let tempTimeout;
    function autoSetTemperature(val) {
      clearTimeout(tempTimeout);
      tempTimeout = setTimeout(() => setTemperature(val), 400);
    }

    // Frissítés oldalbetöltéskor is
    const slider = document.getElementById('temp');
    updateTempValue(slider.value);
  </script>
</body>
</html>
  )rawliteral";

  server.send(200, "text/html; charset=UTF-8", html);
}


void handleOn()
{
  chigoIR.powerOn();
  server.send(200, "text/html; charset=UTF-8", "Bekapcsolva");
}


void handleOff()
{
  chigoIR.powerOff();
  server.send(200, "text/html; charset=UTF-8", "Kikapcsolva");
}


void handleSet()
{
  if (server.hasArg("temp"))
  {
    int temp = server.arg("temp").toInt();
    if (chigoIR.setTemperature(temp)) {
      server.send(200, "text/html; charset=UTF-8", "Beállítva: " + String(temp) + " °C");
    } else {
      server.send(400, "text/html; charset=UTF-8", "Érvénytelen hőmérséklet");
    }
  }
  else
  {
    server.send(400, "text/html; charset=UTF-8", "Hiányzó paraméter");
  }
}



void setup()
{
  Serial.begin(9600);
  chigoIR.begin();
  wifi.connect();
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/set", handleSet);
  server.begin();
  Serial.println("Webszerver elindítva");
}

void loop()
{
  server.handleClient();
}
