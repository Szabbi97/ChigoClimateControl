#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const char *ssid = "WIFI_SSID";
const char *password = "WIFI_PASSWORD";

ESP8266WebServer server(80);
const uint16_t kIrLedPin = 4; // D2 pin
IRsend irsend(kIrLedPin);

uint16_t rawData_on[99] = {6608, 7584, 642, 3368, 644, 3364, 646, 3368, 644, 1398, 616, 3366, 644, 3366, 646, 3366, 644, 3358, 644, 1396, 618, 1396, 616, 1398, 618, 3366, 644, 1398, 616, 1398, 618, 1396, 618, 1512, 616, 1396, 618, 3366, 644, 3366, 646, 1396, 618, 1396, 616, 3366, 646, 1396, 642, 1364, 616, 3366, 644, 1396, 618, 1394, 620, 3366, 644, 3368, 644, 1370, 644, 3366, 644, 3368, 644, 1370, 644, 3366, 644, 1370, 644, 3366, 644, 1370, 646, 3364, 646, 1368, 646, 1342, 644, 3368, 646, 1368, 646, 3366, 668, 1344, 646, 3364, 670, 1344, 644, 3366, 644, 3314, 644};
uint16_t rawData_off[99] = {6610, 7582, 644, 3364, 646, 3366, 644, 3368, 644, 1398, 616, 3366, 646, 3366, 644, 3366, 646, 3356, 644, 1398, 616, 1398, 616, 1398, 616, 3366, 644, 1398, 616, 1398, 618, 1398, 616, 1512, 616, 1398, 616, 3366, 644, 3366, 646, 3366, 644, 1398, 616, 3368, 644, 1398, 616, 1388, 618, 3366, 644, 1398, 616, 1398, 616, 1396, 616, 3366, 644, 1398, 616, 3366, 644, 3366, 646, 1394, 620, 3366, 644, 1370, 644, 3366, 644, 1370, 644, 3366, 646, 1368, 644, 1342, 644, 3366, 644, 1370, 644, 3366, 644, 1370, 644, 3366, 644, 1370, 644, 3366, 646, 3314, 646};
uint16_t rawData_18[99] = {6608, 7582, 644, 3366, 646, 3366, 644, 3366, 646, 1398, 616, 3364, 646, 3366, 644, 3366, 646, 3358, 644, 1398, 616, 1396, 618, 1396, 616, 3366, 646, 1396, 616, 1398, 616, 1398, 618, 1510, 616, 1398, 616, 3366, 644, 3366, 646, 1396, 616, 1396, 616, 1398, 616, 3366, 646, 3356, 644, 3366, 644, 1372, 642, 1370, 644, 3366, 644, 3366, 646, 3366, 646, 1368, 644, 1368, 646, 1370, 644, 3366, 646, 1368, 644, 3366, 644, 1370, 644, 3368, 644, 1370, 644, 1344, 646, 3364, 644, 1370, 644, 3366, 646, 1368, 646, 3364, 670, 1344, 646, 3364, 646, 3312, 644};
uint16_t rawData_19[99] = {6608, 7580, 644, 3366, 646, 3368, 644, 3366, 644, 1400, 616, 3366, 644, 3366, 644, 3366, 644, 3358, 644, 1398, 616, 1398, 616, 1398, 616, 3366, 644, 1396, 618, 1398, 616, 1396, 618, 1512, 616, 1398, 616, 3366, 644, 3366, 644, 1398, 616, 3366, 644, 1396, 618, 3364, 646, 3358, 644, 3366, 644, 1396, 616, 1396, 618, 3368, 644, 1396, 642, 3342, 644, 1370, 642, 1370, 644, 1370, 644, 3364, 646, 1368, 644, 3366, 646, 1368, 670, 3340, 644, 1370, 644, 1344, 644, 3366, 644, 1368, 644, 3368, 644, 1368, 646, 3366, 646, 1368, 646, 3366, 644, 3312, 646};
uint16_t rawData_20[99] = {6610, 7582, 644, 3366, 644, 3368, 644, 3366, 644, 1398, 614, 3368, 644, 3366, 646, 3364, 646, 3356, 646, 1398, 614, 1400, 614, 1398, 616, 3366, 646, 1398, 616, 1400, 614, 1398, 616, 1512, 616, 1398, 614, 3366, 644, 3368, 642, 1400, 616, 3364, 646, 3368, 644, 1398, 616, 3356, 646, 3368, 644, 1398, 616, 1398, 614, 3366, 646, 1398, 616, 1398, 616, 3368, 642, 1398, 616, 1398, 616, 3366, 644, 1398, 616, 3366, 646, 1398, 616, 3366, 646, 1398, 614, 1372, 616, 3366, 646, 1396, 618, 3364, 646, 1396, 618, 3366, 644, 1398, 616, 3366, 646, 3312, 644};
uint16_t rawData_21[99] = {6610, 7580, 644, 3366, 644, 3366, 644, 3366, 646, 1398, 616, 3366, 646, 3366, 644, 3366, 646, 3358, 644, 1396, 618, 1396, 616, 1398, 616, 3366, 644, 1398, 616, 1398, 618, 1396, 618, 1512, 618, 1396, 616, 3366, 644, 3368, 642, 1398, 616, 3368, 642, 3366, 644, 1396, 618, 3356, 646, 3366, 646, 1370, 644, 1372, 642, 3366, 644, 1372, 642, 1370, 642, 3366, 644, 1372, 644, 1370, 644, 3366, 642, 1372, 644, 3366, 644, 1370, 644, 3368, 644, 1370, 644, 1342, 644, 3368, 644, 1368, 644, 3366, 646, 1368, 646, 3366, 646, 1368, 646, 3364, 646, 3316, 642};
uint16_t rawData_22[99] = {6608, 7580, 646, 3366, 644, 3366, 646, 3364, 646, 1398, 616, 3364, 646, 3366, 644, 3366, 646, 3356, 644, 1398, 616, 1396, 616, 1398, 616, 3368, 642, 1398, 618, 1396, 616, 1396, 618, 1512, 616, 1398, 616, 3366, 644, 3368, 644, 1396, 616, 1398, 616, 3366, 644, 1398, 616, 3358, 644, 3366, 646, 1396, 618, 1396, 642, 3342, 644, 3366, 646, 1396, 618, 3366, 644, 1372, 642, 1370, 644, 3366, 646, 1368, 644, 3366, 644, 1370, 644, 3366, 644, 1370, 644, 1344, 644, 3366, 644, 1370, 644, 3366, 646, 1368, 646, 3364, 646, 1370, 644, 3366, 668, 3288, 646};
uint16_t rawData_23[99] = {6606, 7582, 644, 3366, 644, 3366, 646, 3366, 644, 1398, 616, 3366, 646, 3366, 644, 3366, 644, 3358, 644, 1398, 616, 1398, 618, 1396, 618, 3366, 646, 1396, 616, 1396, 618, 1396, 618, 1510, 618, 1396, 618, 3366, 644, 3366, 644, 1396, 618, 3366, 644, 1398, 616, 1396, 642, 3334, 644, 3366, 646, 1394, 618, 1396, 644, 3340, 644, 1396, 618, 3366, 644, 3366, 644, 1370, 644, 1370, 644, 3366, 644, 1370, 644, 3366, 646, 1368, 644, 3368, 644, 1368, 644, 1344, 644, 3366, 646, 1368, 644, 3366, 644, 1370, 644, 3364, 646, 1368, 670, 3340, 646, 3312, 644};
uint16_t rawData_24[99] = {6608, 7580, 646, 3366, 644, 3366, 644, 3366, 646, 1396, 618, 3366, 644, 3364, 646, 3366, 644, 3356, 670, 1372, 642, 1370, 618, 1396, 616, 3368, 648, 1392, 618, 1396, 618, 1396, 618, 1510, 618, 1396, 618, 3366, 644, 3366, 646, 1372, 640, 1372, 640, 1396, 620, 1394, 618, 3356, 646, 3368, 642, 1370, 644, 1370, 644, 3366, 644, 3366, 644, 3366, 644, 3368, 644, 1368, 644, 1370, 644, 3366, 646, 1366, 646, 3366, 646, 1368, 644, 3366, 644, 1370, 644, 1342, 644, 3366, 644, 1368, 644, 3366, 644, 1370, 644, 3366, 644, 1370, 644, 3368, 642, 3316, 642};
uint16_t rawData_25[99] = {6608, 7582, 644, 3368, 644, 3366, 646, 3364, 646, 1398, 616, 3366, 646, 3366, 644, 3368, 644, 3358, 644, 1398, 618, 1396, 616, 1398, 616, 3366, 644, 1398, 616, 1398, 616, 1398, 616, 1512, 616, 1398, 616, 3366, 644, 3366, 646, 1396, 616, 3366, 646, 3366, 644, 3366, 644, 1388, 616, 3366, 644, 1398, 616, 1398, 616, 3366, 644, 1396, 616, 1398, 616, 1398, 616, 3366, 644, 1398, 618, 3366, 644, 1396, 618, 3366, 644, 1396, 618, 3366, 644, 1396, 618, 1370, 618, 3364, 646, 1396, 618, 3366, 644, 1370, 644, 3368, 644, 1370, 644, 3366, 646, 3312, 644};
uint16_t rawData_26[99] = {6610, 7584, 642, 3366, 644, 3366, 644, 3366, 646, 1396, 616, 3368, 642, 3368, 642, 3366, 646, 3356, 644, 1398, 616, 1398, 616, 1396, 616, 3368, 644, 1396, 616, 1396, 618, 1396, 616, 1512, 616, 1396, 616, 3366, 646, 3364, 646, 1396, 644, 1370, 618, 3364, 646, 3366, 644, 1388, 618, 3366, 644, 1396, 618, 1396, 618, 3366, 646, 3366, 644, 1396, 618, 1370, 642, 3368, 668, 1346, 644, 3366, 646, 1370, 644, 3366, 644, 1370, 644, 3366, 644, 1370, 644, 1342, 644, 3366, 644, 1370, 644, 3366, 644, 1370, 644, 3366, 646, 1368, 646, 3364, 646, 3312, 646};
uint16_t rawData_27[99] = {6608, 7580, 644, 3366, 644, 3368, 644, 3366, 646, 1398, 616, 3366, 644, 3366, 644, 3364, 646, 3358, 644, 1398, 616, 1398, 616, 1398, 616, 3368, 644, 1398, 616, 1398, 616, 1396, 618, 1512, 616, 1398, 616, 3368, 644, 3366, 644, 1398, 616, 3366, 646, 1396, 618, 3366, 644, 1390, 618, 3364, 646, 1398, 616, 1396, 618, 3366, 644, 1396, 616, 3366, 644, 1396, 618, 3366, 644, 1396, 618, 3366, 644, 1396, 618, 3368, 644, 1396, 618, 3368, 644, 1394, 620, 1346, 640, 3366, 646, 1370, 642, 3366, 646, 1370, 644, 3366, 670, 1346, 642, 3366, 644, 3314, 642};
uint16_t rawData_28[99] = {6608, 7580, 646, 3366, 646, 3366, 644, 3368, 644, 1396, 616, 3366, 644, 3366, 646, 3366, 644, 3358, 646, 1396, 618, 1396, 618, 1396, 618, 3366, 644, 1396, 618, 1396, 618, 1396, 618, 1510, 618, 1396, 618, 3366, 644, 3366, 644, 1396, 618, 1396, 618, 1396, 618, 3366, 646, 1386, 618, 3366, 644, 1396, 642, 1348, 642, 3366, 644, 3366, 646, 3366, 644, 1368, 646, 3366, 644, 1370, 644, 3368, 644, 1368, 646, 3364, 644, 1370, 646, 3366, 646, 1368, 646, 1342, 646, 3366, 668, 1344, 646, 3364, 670, 1344, 670, 3340, 644, 1370, 668, 3342, 644, 3314, 644};
uint16_t rawData_29[99] = {6610, 7580, 646, 3366, 644, 3366, 646, 3366, 644, 1398, 616, 3366, 644, 3366, 644, 3368, 644, 3356, 646, 1398, 616, 1396, 616, 1396, 616, 3366, 646, 1396, 618, 1396, 616, 1396, 616, 1512, 616, 1396, 616, 3368, 642, 3366, 644, 1396, 616, 3366, 644, 3366, 646, 1396, 618, 1388, 618, 3366, 644, 1396, 618, 1396, 618, 3366, 644, 1396, 618, 1396, 618, 3368, 644, 3366, 644, 1396, 620, 3364, 644, 1396, 618, 3368, 644, 1370, 644, 3366, 644, 1370, 642, 1344, 644, 3368, 644, 1368, 644, 3366, 644, 1370, 644, 3366, 644, 1368, 646, 3366, 670, 3288, 644};
uint16_t rawData_30[99] = {6610, 7582, 644, 3366, 644, 3366, 644, 3366, 644, 1398, 616, 3366, 644, 3366, 644, 3368, 644, 3356, 646, 1396, 616, 1398, 616, 1398, 616, 3366, 644, 1398, 616, 1398, 616, 1396, 618, 1510, 618, 1398, 616, 3368, 644, 3366, 644, 1396, 618, 1396, 616, 3366, 644, 1396, 618, 1388, 616, 3366, 644, 1396, 618, 1396, 618, 3366, 644, 3366, 644, 1396, 618, 3364, 646, 3366, 670, 1370, 618, 3366, 644, 1396, 618, 3366, 644, 1370, 644, 3366, 644, 1370, 646, 1342, 644, 3366, 644, 1368, 644, 3366, 646, 1370, 644, 3366, 644, 1368, 644, 3366, 644, 3314, 644};

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
  irsend.sendRaw(rawData_on, 99, 38);
  server.send(200, "text/html; charset=UTF-8", "Bekapcsolva");
}

void handleOff()
{
  irsend.sendRaw(rawData_off, 99, 38);
  server.send(200, "text/html; charset=UTF-8", "Kikapcsolva");
}

void handleSet()
{
  if (server.hasArg("temp"))
  {
    int temp = server.arg("temp").toInt();
    switch (temp)
    {
    case 18:
      irsend.sendRaw(rawData_18, 99, 38);
      break;
    case 19:
      irsend.sendRaw(rawData_19, 99, 38);
      break;
    case 20:
      irsend.sendRaw(rawData_20, 99, 38);
      break;
    case 21:
      irsend.sendRaw(rawData_21, 99, 38);
      break;
    case 22:
      irsend.sendRaw(rawData_22, 99, 38);
      break;
    case 23:
      irsend.sendRaw(rawData_23, 99, 38);
      break;
    case 24:
      irsend.sendRaw(rawData_24, 99, 38);
      break;
    case 25:
      irsend.sendRaw(rawData_25, 99, 38);
      break;
    case 26:
      irsend.sendRaw(rawData_26, 99, 38);
      break;
    case 27:
      irsend.sendRaw(rawData_27, 99, 38);
      break;
    case 28:
      irsend.sendRaw(rawData_28, 99, 38);
      break;
    case 29:
      irsend.sendRaw(rawData_29, 99, 38);
      break;
    case 30:
      irsend.sendRaw(rawData_30, 99, 38);
      break;
    default:
      server.send(400, "text/html; charset=UTF-8", "Érvénytelen hőmérséklet");
      return;
    }
    server.send(200, "text/html; charset=UTF-8", "Beállítva: " + String(temp) + " °C");
  }
  else
  {
    server.send(400, "text/html; charset=UTF-8", "Hiányzó paraméter");
  }
}

void setup()
{
  Serial.begin(9600);
  irsend.begin();

  WiFi.begin(ssid, password);
  Serial.print("Csatlakozás Wi-Fi-hez");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nCsatlakozva: " + WiFi.localIP().toString());

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
