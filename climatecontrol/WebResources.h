#pragma once
// Auto-generated file containing web resources
// Generated from ui/ directory

const char MAIN_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <title>Climate Control</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script type="module" src="scripts/main.js"></script>
  <link rel="stylesheet" href="styles/main.css">
</head>

<body>
  <!-- Thunder flash effect (must be behind container) -->
  <div id="thunder-flash"></div>
  <!-- Animated clouds background -->
  <div class="clouds" id="clouds-container"></div>
  <!-- Animated sun/moon background -->
  <div id="weather-bg">
    <div id="sun-bg">
      <!-- Sun SVG -->
      <svg width="120" height="120" viewBox="0 0 120 120" fill="none" xmlns="http://www.w3.org/2000/svg">
        <circle cx="60" cy="60" r="38" fill="#FFD600" />
        <g stroke="#FFD600" stroke-width="6">
          <line x1="60" y1="10" x2="60" y2="32" />
          <line x1="60" y1="88" x2="60" y2="110" />
          <line x1="10" y1="60" x2="32" y2="60" />
          <line x1="88" y1="60" x2="110" y2="60" />
          <line x1="28" y1="28" x2="42" y2="42" />
          <line x1="92" y1="92" x2="78" y2="78" />
          <line x1="28" y1="92" x2="42" y2="78" />
          <line x1="92" y1="28" x2="78" y2="42" />
        </g>
      </svg>
    </div>
    <div id="moon-bg" style="display:none;">
      <!-- Moon SVG -->
      <svg width="120" height="120" viewBox="0 0 120 120" fill="none" xmlns="http://www.w3.org/2000/svg">
        <path d="M90 60c0 16.57-13.43 30-30 30a30 30 0 010-60c1.7 0 3.37.15 5 .45A35 35 0 0090 60z" fill="#90caf9" />
      </svg>
    </div>
  </div>
  <!-- Language selector fixed to bottom right with flags, outside container -->
  <div id="lang-switcher">
    <button id="lang-en" onclick="setLang('en')" title="English" aria-label="English" type="button">
      <span style="font-size:22px;">🇬🇧</span>
    </button>
    <button id="lang-hu" onclick="setLang('hu')" title="Magyar" aria-label="Magyar" type="button">
      <span style="font-size:22px;">🇭🇺</span>
    </button>
  </div>
  <div class="container">
    
    <h2 id="title"></h2>
    <div class="controls">
      <form onsubmit="return false;">
        <div class="slider-container" style="position:relative;">
          <label for="temp" class="slider-label" id="label-temp"></label>
          <div id="temp-value" class="temp-value">24 °C</div>
          <input type="range" id="temp" name="temp" min="18" max="30" value="24"
            oninput="updateTempValue(this.value); autoSetTemperature(this.value);"
            style="position:relative; z-index:2;">
        </div>
        <div class="slider-container mode-group">
          <label class="slider-label" id="label-mode"></label>
          <div class="button-group" id="mode-group">
            <button type="button" class="mode-btn ripple" data-value="1" onclick="selectMode(this)">🔥</button>
            <button type="button" class="mode-btn ripple" data-value="2" onclick="selectMode(this)">💧</button>
            <button type="button" class="mode-btn ripple" data-value="3" onclick="selectMode(this)">🌬️</button>
            <button type="button" class="mode-btn ripple" data-value="4" onclick="selectMode(this)">❄️</button>
          </div>
        </div>
        <div class="slider-container airflow-group">
          <label class="slider-label" id="label-airflow"></label>
          <div class="button-group" id="airflow-group">
            <button type="button" class="airflow-btn ripple" data-value="0" onclick="selectAirflow(this)">🚫</button>
            <button type="button" class="airflow-btn ripple" data-value="1" onclick="selectAirflow(this)">1f</button>
            <button type="button" class="airflow-btn ripple" data-value="2" onclick="selectAirflow(this)">↕️</button>
          </div>
        </div>
        <div class="slider-container fan-group">
          <label class="slider-label" id="label-fan"></label>
          <div class="button-group" id="fan-group">
            <button type="button" class="fan-btn ripple" data-value="0" onclick="selectFan(this)">⚙️</button>
            <button type="button" class="fan-btn ripple" data-value="1" onclick="selectFan(this)">Low</button>
            <button type="button" class="fan-btn ripple" data-value="2" onclick="selectFan(this)">Medium</button>
            <button type="button" class="fan-btn ripple" data-value="3" onclick="selectFan(this)">High</button>
          </div>
        </div>
      </form>
      <div class="power-buttons">
        <button class="power-on ripple" id="btn-on" onclick="sendCommand('/on', getText('on'))"></button>
        <button class="power-off ripple" id="btn-off" onclick="sendCommand('/off', getText('off'))"></button>
      </div>
    </div>
    <div id="status"><span id="status-icon"></span></div>
  </div>
  <div id="darkmode-switcher" title="Sötét mód" aria-label="Sötét mód">
    <label class="switch">
      <input type="checkbox" id="darkmode-toggle" style="display:none;">
      <span class="slider">
        <span class="icon sun"></span>
        <span class="icon moon"></span>
      </span>
    </label>
  </div>
  <!-- Weather effects container -->
  <div id="weather-effects"></div>
  <!-- Weather info box -->
  <div id="weather-info"></div>
  
</body>

</html>
)rawliteral";

const char MAIN_JS[] PROGMEM = R"rawliteral(
// Main entry: import modules and initialize
import { selectMode, selectAirflow, selectFan, restoreUIState } from './uiState.js';
import { setLang, getText, texts } from './localization.js';
import { setMode, setAirflow, setFan, sendCommand, setTemperature, displayDeviceStatus } from './api.js';
import { setStatus } from './status.js';
import { applyDarkMode, setDarkMode } from './theme.js';
import { showRainEffect, showSnowEffect, showThunderEffect, clearThunderEffect, clearWeatherEffects, showWeatherInfo, hideWeatherInfo, fetchWeatherForLocation } from './weather.js';
import { createCloud, createInitialClouds, startCloudGeneration } from './cloud.js';
import { updateTempValue, autoSetTemperature } from './temperature.js';

// Expose functions globally for event handlers
window.setMode = setMode;
window.setAirflow = setAirflow;
window.setFan = setFan;
window.setStatus = setStatus;
window.setTemperature = setTemperature;
window.updateTempValue = updateTempValue;
window.sendCommand = sendCommand;
window.getText = getText;
window.setLang = setLang;

window.selectMode = selectMode;
window.selectAirflow = selectAirflow;
window.selectFan = selectFan;
window.autoSetTemperature = autoSetTemperature;

// Initialization
restoreUIState();
createInitialClouds();
setTimeout(startCloudGeneration, 2000);

// Check device connection after page load
setTimeout(displayDeviceStatus, 1000);
const savedLang = localStorage.getItem('climate_lang');
setLang(savedLang === 'hu' ? 'hu' : 'en');
let darkPref = localStorage.getItem('climate_darkmode');
if (darkPref === null) {
    darkPref = window.matchMedia && window.matchMedia('(prefers-color-scheme: dark)').matches ? '1' : '0';
}
setDarkMode(darkPref === '1');
fetchWeatherForLocation();
const slider = document.getElementById('temp');
updateTempValue(slider.value);

document.getElementById('darkmode-toggle').addEventListener('change', function () {
    setDarkMode(this.checked);
});
)rawliteral";

const char API_JS[] PROGMEM = R"rawliteral(
// Backend communication: fetch commands
import { getText, getCurrentLang } from './localization.js';

// Check device connection status
export function checkDeviceConnection() {
    return fetch('/status', { 
        method: 'GET',
        timeout: 5000 // 5 second timeout
    })
    .then(response => {
        if (!response.ok) {
            throw new Error(`HTTP ${response.status}`);
        }
        return true;
    })
    .catch(error => {
        console.warn('Device connection check failed:', error);
        return false;
    });
}

// Display device status on page load
export function displayDeviceStatus() {
    checkDeviceConnection().then(isConnected => {
        if (!isConnected) {
            window.setStatus(getText('device_disconnected'));
        } else {
            window.setStatus(getText('device_connected'));
        }
    });
}
export function setMode(val) {
    window.setStatus(getText('status_mode'), true);
    fetch('/setmode?mode=' + val)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            return response.text();
        })
        .then(text => window.setStatus(text))
        .catch(error => {
            console.error('Mode setting failed:', error);
            const errorMsg = getCurrentLang() === 'en' 
                ? `Error: Device not connected (${error.message})` 
                : `Hiba: Eszköz nincs csatlakoztatva (${error.message})`;
            window.setStatus(errorMsg);
        });
}
export function setAirflow(val) {
    window.setStatus(getText('status_airflow'), true);
    fetch('/setairflow?airflow=' + val)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            return response.text();
        })
        .then(text => window.setStatus(text))
        .catch(error => {
            console.error('Airflow setting failed:', error);
            const errorMsg = getCurrentLang() === 'en' 
                ? `Error: Device not connected (${error.message})` 
                : `Hiba: Eszköz nincs csatlakoztatva (${error.message})`;
            window.setStatus(errorMsg);
        });
}
export function setFan(val) {
    window.setStatus(getText('status_fan'), true);
    fetch('/setfan?fan=' + val)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            return response.text();
        })
        .then(text => window.setStatus(text))
        .catch(error => {
            console.error('Fan setting failed:', error);
            const errorMsg = getCurrentLang() === 'en' 
                ? `Error: Device not connected (${error.message})` 
                : `Hiba: Eszköz nincs csatlakoztatva (${error.message})`;
            window.setStatus(errorMsg);
        });
}
export function sendCommand(path, msg) {
    window.setStatus(msg + (getCurrentLang() === 'en' ? ' (in progress...)' : ' (folyamatban...)'), true);
    fetch(path)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            return response.text();
        })
        .then(text => window.setStatus(text))
        .catch(error => {
            console.error('Command failed:', error);
            const errorMsg = getCurrentLang() === 'en' 
                ? `Error: Device not connected (${error.message})` 
                : `Hiba: Eszköz nincs csatlakoztatva (${error.message})`;
            window.setStatus(errorMsg);
        });
}
export function setTemperature(val) {
    window.setStatus(getText('status_set'), true);
    fetch('/set?temp=' + val)
        .then(response => {
            if (!response.ok) {
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            }
            return response.text();
        })
        .then(text => window.setStatus(text))
        .catch(error => {
            console.error('Temperature setting failed:', error);
            const errorMsg = getCurrentLang() === 'en' 
                ? `Error: Device not connected (${error.message})` 
                : `Hiba: Eszköz nincs csatlakoztatva (${error.message})`;
            window.setStatus(errorMsg);
        });
    localStorage.setItem('climate_temp', val);
}

)rawliteral";

const char LOCALIZATION_JS[] PROGMEM = R"rawliteral(
// Localization: texts, language switching
export const texts = {
    en: {
        title: "Chigo Climate Control",
        temp: "Temperature:",
        mode: "Mode:",
        airflow: "Airflow:",
        fan: "Fan speed:",
        on: "Power On",
        off: "Power Off",
        status_idle: "Status: no action",
        status_on: "Powering on (in progress...)",
        status_off: "Powering off (in progress...)",
        status_set: val => `Setting temperature (${val}°C)...`,
        status_mode: "Setting mode...",
        status_airflow: "Setting airflow...",
        status_fan: "Setting fan speed...",
        error: "An error occurred!",
        device_connected: "Device connected and ready",
        device_disconnected: "Warning: Climate control device not connected"
    },
    hu: {
        title: "Chigo klíma vezérlés",
        temp: "Hőmérséklet:",
        mode: "Mód:",
        airflow: "Légáram:",
        fan: "Ventilátor sebesség:",
        on: "Bekapcsolás",
        off: "Kikapcsolás",
        status_idle: "Állapot: nincs művelet",
        status_on: "Bekapcsolás (folyamatban...)",
        status_off: "Kikapcsolás (folyamatban...)",
        status_set: val => `Hőmérséklet beállítása (${val}°C)...`,
        status_mode: "Mód beállítása...",
        status_airflow: "Légáram beállítása...",
        status_fan: "Ventilátor sebesség beállítása...",
        error: "Hiba történt!",
        device_connected: "Eszköz csatlakoztatva és készen áll",
        device_disconnected: "Figyelem: Klíma vezérlő eszköz nincs csatlakoztatva"
    }
};
let currentLang = 'en';
export function setLang(lang) {
    currentLang = lang;
    localStorage.setItem('climate_lang', lang);
    document.getElementById('title').innerText = texts[lang].title;
    document.getElementById('label-temp').innerText = texts[lang].temp;
    document.getElementById('label-mode').innerText = texts[lang].mode;
    document.getElementById('label-airflow').innerText = texts[lang].airflow;
    document.getElementById('label-fan').innerText = texts[lang].fan;
    document.getElementById('btn-on').innerText = texts[lang].on;
    document.getElementById('btn-off').innerText = texts[lang].off;
    document.getElementById('status').innerText = texts[lang].status_idle;
    document.getElementById('lang-en').classList.toggle('selected', lang === 'en');
    document.getElementById('lang-hu').classList.toggle('selected', lang === 'hu');
}
export function getText(key) {
    return typeof texts[currentLang][key] === 'function' ? texts[currentLang][key](document.getElementById('temp').value) : texts[currentLang][key];
}
export function getCurrentLang() {
    return currentLang;
}

)rawliteral";

const char STATUS_JS[] PROGMEM = R"rawliteral(
// Status display logic: feedback, icons
export function setStatus(msg, loading = false) {
    const status = document.getElementById('status');
    status.innerHTML = '';
    if (loading) {
        let iconSpan = document.createElement('span');
        if (msg.includes('Powering on') || msg.includes('Bekapcsolás')) {
            iconSpan.className = 'status-fan';
        } else if (msg.includes('Powering off') || msg.includes('Kikapcsolás')) {
            iconSpan.className = 'status-bulb';
        } else if (msg.includes('Setting temperature') || msg.includes('Hőmérséklet beállítása')) {
            iconSpan.className = 'status-thermo';
        } else {
            iconSpan.className = 'status-spin';
        }
        status.appendChild(iconSpan);
        status.appendChild(document.createTextNode(' ' + msg));
        status.style.color = "#888";
    } else {
        status.innerText = msg;
        status.style.color = "#222";
    }
}

)rawliteral";

const char TEMPERATURE_JS[] PROGMEM = R"rawliteral(
// Temperature slider logic
export function updateTempValue(val) {
    document.getElementById('temp-value').innerText = val + ' °C';
    const slider = document.getElementById('temp');
    val = parseInt(val);
    let r, g, b;
    if (val <= 20) {
        r = 25;
        g = 118;
        b = 210;
    } else if (val < 24) {
        const ratio = (val - 20) / 4;
        r = Math.round(25 + (76 - 25) * ratio);
        g = Math.round(118 + (175 - 118) * ratio);
        b = Math.round(210 + (80 - 210) * ratio);
    } else if (val <= 30) {
        const ratio = (val - 24) / 6;
        r = Math.round(76 + (255 - 76) * ratio);
        g = Math.round(175 + (82 - 175) * ratio);
        b = Math.round(80 + (82 - 80) * ratio);
    } else {
        r = 255;
        g = 82;
        b = 82;
    }
    function rgbToHex(r, g, b) {
        return '#' + [r, g, b].map(x => x.toString(16).padStart(2, '0')).join('');
    }
    const hexColor = rgbToHex(r, g, b);
    let prevStyle = document.getElementById('slider-accent-style');
    if (prevStyle) prevStyle.remove();
    const style = document.createElement('style');
    style.id = 'slider-accent-style';
    style.textContent = `#temp { accent-color: ${hexColor}; }`;
    document.head.appendChild(style);
}
let tempTimeout;
export function autoSetTemperature(val) {
    clearTimeout(tempTimeout);
    tempTimeout = setTimeout(() => window.setTemperature(val), 400);
}

)rawliteral";

const char THEME_JS[] PROGMEM = R"rawliteral(
// Theme management: dark mode
export function applyDarkMode(dark) {
    document.body.classList.toggle('darkmode', dark);
    document.querySelector('.container').classList.toggle('darkmode', dark);
    document.getElementById('status').classList.toggle('darkmode', dark);
    document.getElementById('lang-switcher').classList.toggle('darkmode', dark);
    document.querySelectorAll('button, select, input[type="submit"], .slider-label, .temp-value, label, .mode-btn, .airflow-btn, .fan-btn, .power-on, .power-off').forEach(el => {
        el.classList.toggle('darkmode', dark);
    });
    document.getElementById('darkmode-toggle').checked = dark;
    const sun = document.getElementById('sun-bg');
    const moon = document.getElementById('moon-bg');
    if (dark) {
        sun.style.opacity = 0;
        sun.style.display = 'none';
        moon.style.opacity = 1;
        moon.style.display = 'block';
    } else {
        sun.style.opacity = 1;
        sun.style.display = 'block';
        moon.style.opacity = 0;
        moon.style.display = 'none';
    }
}
export function setDarkMode(dark) {
    applyDarkMode(dark);
    localStorage.setItem('climate_darkmode', dark ? '1' : '0');
}

)rawliteral";

const char UISTATE_JS[] PROGMEM = R"rawliteral(
// UI state management: button groups, slider, restore
export function selectMode(btn) {
    document.querySelectorAll('.mode-btn').forEach(b => b.classList.remove('selected'));
    btn.classList.add('selected');
    const val = btn.getAttribute('data-value');
    window.setMode(val);
    localStorage.setItem('climate_mode', val);
}
export function selectAirflow(btn) {
    document.querySelectorAll('.airflow-btn').forEach(b => b.classList.remove('selected'));
    btn.classList.add('selected');
    const val = btn.getAttribute('data-value');
    window.setAirflow(val);
    localStorage.setItem('climate_airflow', val);
}
export function selectFan(btn) {
    document.querySelectorAll('.fan-btn').forEach(b => b.classList.remove('selected'));
    btn.classList.add('selected');
    const val = btn.getAttribute('data-value');
    window.setFan(val);
    localStorage.setItem('climate_fan', val);
}
export function restoreUIState() {
    const savedMode = localStorage.getItem('climate_mode') || '1';
    const savedAirflow = localStorage.getItem('climate_airflow') || '0';
    const savedFan = localStorage.getItem('climate_fan') || '0';
    const savedTemp = localStorage.getItem('climate_temp') || '24';
    const modeBtn = document.querySelector('.mode-btn[data-value="' + savedMode + '"]');
    if (modeBtn) modeBtn.classList.add('selected');
    const airflowBtn = document.querySelector('.airflow-btn[data-value="' + savedAirflow + '"]');
    if (airflowBtn) airflowBtn.classList.add('selected');
    const fanBtn = document.querySelector('.fan-btn[data-value="' + savedFan + '"]');
    if (fanBtn) fanBtn.classList.add('selected');
    const slider = document.getElementById('temp');
    slider.value = savedTemp;
    window.updateTempValue(savedTemp);
}

)rawliteral";

const char WEATHER_JS[] PROGMEM = R"rawliteral(
// Weather effects & API: rain, snow, thunder, info
export function showRainEffect(count = 40) {
    const container = document.getElementById('weather-effects');
    container.innerHTML = '';
    for (let i = 0; i < count; i++) {
        const drop = document.createElement('div');
        drop.className = 'raindrop';
        drop.style.left = Math.random() * 100 + 'vw';
        drop.style.animationDelay = (Math.random() * 1.2) + 's';
        container.appendChild(drop);
    }
}
export function showSnowEffect(count = 30) {
    const container = document.getElementById('weather-effects');
    container.innerHTML = '';
    for (let i = 0; i < count; i++) {
        const snow = document.createElement('div');
        snow.className = 'snowflake';
        snow.style.left = Math.random() * 100 + 'vw';
        snow.style.animationDelay = (Math.random() * 2) + 's';
        snow.style.fontSize = (Math.random() * 12 + 12) + 'px';
        snow.innerText = '❄️';
        container.appendChild(snow);
    }
}
let thunderFlashInterval = null;
export function showThunderEffect() {
    const flashDiv = document.getElementById('thunder-flash');
    clearThunderEffect();
    function flash() {
        flashDiv.classList.remove('thunder-active');
        void flashDiv.offsetWidth;
        flashDiv.classList.add('thunder-active');
    }
    function scheduleFlash() {
        flash();
        thunderFlashInterval = setTimeout(scheduleFlash, 1500 + Math.random() * 2500);
    }
    scheduleFlash();
}
export function clearThunderEffect() {
    if (thunderFlashInterval) {
        clearTimeout(thunderFlashInterval);
        thunderFlashInterval = null;
    }
    const flashDiv = document.getElementById('thunder-flash');
    flashDiv.classList.remove('thunder-active');
}
export function clearWeatherEffects() {
    document.getElementById('weather-effects').innerHTML = '';
    clearThunderEffect();
}
export function showWeatherInfo(text) {
    const info = document.getElementById('weather-info');
    info.innerText = text;
    info.classList.add('visible');
}
export function hideWeatherInfo() {
    document.getElementById('weather-info').classList.remove('visible');
}
export function fetchWeatherForLocation() {
    if (!navigator.geolocation) return;
    navigator.geolocation.getCurrentPosition(function (pos) {
        const lat = pos.coords.latitude;
        const lon = pos.coords.longitude;
        // Note: You need to get your own API key from https://openweathermap.org/api
        // and replace 'YOUR_API_KEY' with your actual key
        const apiKey = 'YOUR_API_KEY';
        if (apiKey === 'YOUR_API_KEY') {
            console.warn('Weather API key not configured');
            hideWeatherInfo();
            return;
        }
        const url = `https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lon}&units=metric&lang=hu&appid=${apiKey}`;
        fetch(url)
            .then(res => res.json())
            .then(data => {
                if (!data.weather || !data.weather[0]) return;
                const main = data.weather[0].main.toLowerCase();
                const desc = data.weather[0].description;
                const temp = Math.round(data.main.temp);
                showWeatherInfo(`${desc}, ${temp}°C`);
                clearWeatherEffects();
                if (main.includes('rain')) {
                    showRainEffect();
                } else if (main.includes('snow')) {
                    showSnowEffect();
                } else if (main.includes('thunder') || main.includes('storm')) {
                    showThunderEffect();
                } else {
                    clearWeatherEffects();
                }
            })
            .catch(() => hideWeatherInfo());
    }, function () {
        hideWeatherInfo();
    });
}

)rawliteral";

const char CLOUD_JS[] PROGMEM = R"rawliteral(
// Cloud animation logic
export function createCloud(initialPosition = null, isInitial = false) {
    const cloudsContainer = document.getElementById('clouds-container');
    const cloud = document.createElement('div');
    cloud.className = 'cloud';
    const size = Math.random() * 60 + 40;
    const height = size * 0.5;
    const topPosition = Math.random() * 70 + 5;
    const duration = Math.random() * 20 + 25;
    cloud.style.width = size + 'px';
    cloud.style.height = height + 'px';
    cloud.style.top = topPosition + '%';
    if (initialPosition !== null && isInitial) {
        cloud.style.left = initialPosition + 'px';
        cloud.style.opacity = '0.7';
        const remainingDistance = window.innerWidth + 150 - initialPosition;
        const remainingDuration = (remainingDistance / (window.innerWidth + 300)) * duration;
        cloud.style.animation = `floatFromPosition ${remainingDuration}s linear`;
    } else {
        cloud.style.animation = `floatAcross ${duration}s linear`;
    }
    const beforeSize = size * 0.6;
    const afterSize = size * 0.7;
    const style = document.createElement('style');
    const cloudId = 'cloud-' + Date.now() + '-' + Math.random().toString(36).substr(2, 9);
    cloud.id = cloudId;
    style.textContent = `
        #${cloudId}:before {
          width: ${beforeSize}px;
          height: ${beforeSize}px;
          top: ${-beforeSize / 2}px;
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
export function createInitialClouds() {
    const numClouds = Math.floor(Math.random() * 6) + 10;
    for (let i = 0; i < numClouds; i++) {
        const initialX = Math.random() * (window.innerWidth - 100);
        createCloud(initialX, true);
    }
}
export function startCloudGeneration() {
    createCloud();
    const nextCloudDelay = Math.random() * 3000 + 2000;
    setTimeout(startCloudGeneration, nextCloudDelay);
}

)rawliteral";

const char MAIN_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   CLIMATE CONTROL - MAIN STYLESHEET
   =================================== */

/* Import all modular CSS files */
@import url('base.css');
@import url('weather-bg.css');
@import url('animations.css');
@import url('clouds.css');
@import url('weather-effects.css');
@import url('buttons.css');
@import url('power-buttons.css');
@import url('control-buttons.css');
@import url('sliders.css');
@import url('status.css');
@import url('theme-switcher.css');
@import url('language-switcher.css');
@import url('dark-mode.css');
@import url('responsive.css');
)rawliteral";

const char BASE_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   BASE STYLES & LAYOUT
   =================================== */

body {
    font-family: sans-serif;
    padding: 20px;
    background: linear-gradient(to bottom, #87CEEB 0%, #98D8E8 50%, #B8E6F2 100%);
    min-height: 100vh;
    position: relative;
    overflow-x: hidden;
    margin: 0;
}

.container {
    max-width: 400px;
    margin: auto;
    background: rgba(255, 255, 255, 0.95);
    border-radius: 10px;
    box-shadow: 0 4px 16px rgba(0, 0, 0, 0.1);
    padding: 24px;
    position: relative;
    z-index: 11;
    backdrop-filter: blur(5px);
    width: calc(100% - 40px);
    min-height: auto;
}

h2 {
    text-align: center;
}

label {
    font-weight: bold;
    margin-bottom: 4px;
}

)rawliteral";

const char ANIMATIONS_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   ANIMATIONS & KEYFRAMES
   =================================== */

@keyframes sunfloat {
    0% {
        transform: translate(-50%, 0) scale(1);
    }

    100% {
        transform: translate(-50%, 16px) scale(1.04);
    }
}

@keyframes moonfloat {
    0% {
        transform: translate(-50%, 0) scale(1);
    }

    100% {
        transform: translate(-50%, 24px) scale(1.08);
    }
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

@keyframes ripple-animation {
    to {
        transform: scale(2.5);
        opacity: 0;
    }
}

@keyframes thunder-flash-bg {
    0% {
        opacity: 0;
    }

    10% {
        opacity: 0.45;
    }

    25% {
        opacity: 0.18;
    }

    40% {
        opacity: 0.32;
    }

    60% {
        opacity: 0.12;
    }

    80% {
        opacity: 0.22;
    }

    100% {
        opacity: 0;
    }
}

@keyframes spin {
    100% {
        transform: rotate(360deg);
    }
}

@keyframes blink {
    0%,
    100% {
        opacity: 1;
    }

    50% {
        opacity: 0.3;
    }
}

@keyframes pulse {
    0%,
    100% {
        transform: scale(1);
    }

    50% {
        transform: scale(1.2);
    }
}

@keyframes raindrop-fall {
    0% {
        top: -20px;
        opacity: 0.7;
    }

    80% {
        opacity: 0.7;
    }

    100% {
        top: 100vh;
        opacity: 0;
    }
}

@keyframes snowflake-fall {
    0% {
        top: -32px;
        opacity: 0.85;
        transform: translateX(0);
    }

    80% {
        opacity: 0.85;
    }

    100% {
        top: 100vh;
        opacity: 0;
        transform: translateX(20px);
    }
}

@keyframes thunderbolt-flash {
    0%,
    100% {
        opacity: 0;
    }

    10% {
        opacity: 0.85;
    }

    20% {
        opacity: 0.2;
    }

    30% {
        opacity: 0.85;
    }

    40% {
        opacity: 0.2;
    }

    50% {
        opacity: 0.85;
    }

    60% {
        opacity: 0.2;
    }

    70% {
        opacity: 0.85;
    }

    80% {
        opacity: 0.2;
    }

    90% {
        opacity: 0.85;
    }
}

)rawliteral";

const char BUTTONS_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   FORM CONTROLS & BUTTONS
   =================================== */

.controls {
    display: flex;
    flex-direction: column;
    gap: 12px;
    margin-bottom: 16px;
}

button,
select,
input[type="submit"] {
    margin: 0;
    padding: 14px;
    font-size: 18px;
    border-radius: 6px;
    border: 1px solid #bbb;
    background: #e9e9e9;
    transition: background 0.2s, box-shadow 0.2s, transform 0.15s;
    cursor: pointer;
    position: relative;
    overflow: hidden;
}

button:hover,
select:hover,
input[type="submit"]:hover {
    background: #d0eaff;
    box-shadow: 0 6px 24px #1976d244;
    transform: translateY(-2px) scale(1.04);
}

button:active {
    transform: scale(0.97);
    box-shadow: 0 2px 12px #1976d244;
}

button.ripple {
    position: relative;
    overflow: hidden;
}

.ripple-effect {
    position: absolute;
    border-radius: 50%;
    transform: scale(0);
    animation: ripple-animation 0.5s linear;
    background: rgba(25, 118, 210, 0.25);
    pointer-events: none;
    z-index: 2;
}

)rawliteral";

const char CLOUDS_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   CLOUD ANIMATIONS & ELEMENTS
   =================================== */

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

.thunder-active {
    animation: thunder-flash-bg 1.2s cubic-bezier(.7, 0, .3, 1);
}

)rawliteral";

const char CONTROL_BUTTONS_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   MODE, AIRFLOW & FAN BUTTONS
   =================================== */

.button-group {
    display: flex;
    gap: 10px;
    justify-content: center;
    margin-top: 8px;
}

.mode-btn,
.airflow-btn,
.fan-btn {
    font-size: 1.3em;
    padding: 10px 18px;
    border-radius: 8px;
    border: none;
    background: #e0f7fa;
    color: #1976d2;
    box-shadow: 0 2px 8px #b2d7ff44;
    cursor: pointer;
    transition: background 0.2s, box-shadow 0.2s, color 0.2s;
    outline: none;
    font-weight: bold;
}

.mode-btn.selected,
.airflow-btn.selected,
.fan-btn.selected {
    background: #1976d2;
    color: #fff;
    box-shadow: 0 4px 16px #1976d288;
}

.mode-btn:active,
.airflow-btn:active,
.fan-btn:active {
    background: #90caf9;
    color: #1976d2;
}

.slider-container.mode-group,
.slider-container.airflow-group,
.slider-container.fan-group {
    margin-bottom: 10px;
}

)rawliteral";

const char DARK_MODE_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   DARK MODE STYLES
   =================================== */

body.darkmode {
    background: linear-gradient(to bottom, #222 0%, #333 50%, #444 100%);
    color: #eee;
}

.container.darkmode {
    background: rgba(34, 34, 34, 0.97);
    box-shadow: 0 4px 16px #0008;
    color: #eee;
}

.slider-label.darkmode,
.temp-value.darkmode,
label.darkmode {
    color: #90caf9;
}

button.darkmode,
select.darkmode,
input[type="submit"].darkmode {
    background: #333;
    color: #90caf9;
    border: 1px solid #444;
}

button.darkmode:hover,
select.darkmode:hover,
input[type="submit"].darkmode:hover {
    background: #1976d2;
    color: #fff;
    box-shadow: 0 6px 24px #1976d244;
}

.mode-btn.darkmode,
.airflow-btn.darkmode,
.fan-btn.darkmode {
    background: #222;
    color: #90caf9;
    box-shadow: 0 2px 8px #1976d244;
}

.mode-btn.darkmode.selected,
.airflow-btn.darkmode.selected,
.fan-btn.darkmode.selected {
    background: #1976d2;
    color: #fff;
    box-shadow: 0 4px 16px #1976d288;
}

.power-on.darkmode {
    background: #388e3c;
    color: #fff;
    border: 1px solid #388e3c;
    box-shadow: 0 2px 6px #388e3c88;
}

.power-off.darkmode {
    background: #d32f2f;
    color: #fff;
    border: 1px solid #d32f2f;
    box-shadow: 0 2px 6px #d32f2f88;
}

#status.darkmode {
    background: #222;
    color: #90caf9;
}

#lang-switcher.darkmode {
    background: #222;
    box-shadow: 0 2px 8px #0008;
}

#lang-switcher button.darkmode {
    color: #90caf9;
}

)rawliteral";

const char LANGUAGE_SWITCHER_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   LANGUAGE SWITCHER
   =================================== */

#lang-switcher {
    position: fixed;
    right: 18px;
    bottom: 18px;
    z-index: 100;
    display: flex;
    gap: 8px;
    background: rgba(255, 255, 255, 0.85);
    border-radius: 24px;
    box-shadow: 0 2px 8px rgba(0, 0, 0, 0.08);
    padding: 6px 10px;
    align-items: center;
}

#lang-switcher button {
    background: none;
    border: none;
    cursor: pointer;
    outline: none;
    padding: 2px 4px;
    border-radius: 50%;
    transition: background 0.2s;
    font-size: 22px;
    line-height: 1;
}

#lang-switcher button:hover {
    background: #d0eaff;
    box-shadow: 0 2px 12px #1976d244;
    transform: scale(1.08);
}

#lang-switcher button.selected,
#lang-switcher button:focus {
    background: #d0eaff;
}

#lang-switcher button:active {
    background: #b2f7c1;
}

)rawliteral";

const char POWER_BUTTONS_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   POWER BUTTONS
   =================================== */

.power-buttons {
    display: flex;
    gap: 16px;
    justify-content: center;
    margin-bottom: 12px;
    flex-wrap: wrap;
}

.power-on,
.power-off {
    flex: 1;
    min-width: 120px;
    text-align: center;
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

)rawliteral";

const char RESPONSIVE_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   RESPONSIVE DESIGN - MOBILE
   =================================== */

@media (max-width: 500px) {
    body {
        padding: 10px;
    }

    .container {
        padding: 16px;
        width: calc(100% - 40px);
        margin: 10px auto;
    }

    button,
    select,
    input[type="submit"] {
        font-size: 16px;
        padding: 12px;
        min-height: 48px;
        /* Touch target size */
    }

    .power-buttons {
        gap: 12px;
    }

    .power-on,
    .power-off {
        min-width: 100px;
    }

    h2 {
        font-size: 1.3em;
        margin: 10px 0;
    }

    .temp-value {
        font-size: 1.1em;
    }

    .slider-container {
        margin-bottom: 16px;
    }

    input[type="range"] {
        height: 6px;
        margin-bottom: 12px;
    }

    input[type="range"]::-webkit-slider-thumb {
        width: 40px;
        height: 40px;
    }

    input[type="range"]::-moz-range-thumb {
        width: 40px;
        height: 40px;
    }

    #status {
        margin-top: 16px;
        padding: 12px;
        font-size: 14px;
    }

    .button-group {
        gap: 6px;
    }

    .mode-btn,
    .airflow-btn,
    .fan-btn {
        font-size: 1em;
        padding: 8px 10px;
    }

    #darkmode-switcher {
        top: 8px;
        right: 8px;
    }

    .switch {
        width: 44px;
        height: 26px;
    }

    .switch .icon {
        width: 16px;
        height: 16px;
    }

    .switch .slider:before {
        width: 18px;
        height: 18px;
        left: 2px;
        top: 2px;
    }

    .switch input:checked+.slider:before {
        left: 20px;
    }

    #lang-switcher {
        right: 8px;
        bottom: 8px;
        padding: 4px 6px;
    }

    #lang-switcher button {
        font-size: 18px;
    }
}

@media (max-width: 360px) {
    .container {
        padding: 12px;
    }

    .power-buttons {
        flex-direction: column;
        gap: 8px;
    }

    .power-on,
    .power-off {
        width: 100%;
        min-width: auto;
    }

    button,
    select,
    input[type="submit"] {
        font-size: 15px;
        padding: 10px;
    }
}

)rawliteral";

const char SLIDERS_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   SLIDERS & INPUT RANGES
   =================================== */

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

input[type="range"]:hover {
    background: #b2d7ff;
    box-shadow: 0 2px 12px #1976d244;
    transition: background 0.2s, box-shadow 0.2s;
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

)rawliteral";

const char STATUS_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   STATUS & INDICATORS
   =================================== */

#status {
    margin-top: 20px;
    font-weight: bold;
    padding: 10px;
    border-radius: 6px;
    background: #eef;
    min-height: 32px;
    text-align: center;
}

.status-fan {
    display: inline-block;
    width: 24px;
    height: 24px;
    background: url('data:image/svg+xml;utf8,<svg width="24" height="24" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg"><g><circle cx="12" cy="12" r="3" fill="%231976d2"/><path d="M12 2v6" stroke="%231976d2" stroke-width="2"/><path d="M12 22v-6" stroke="%231976d2" stroke-width="2"/><path d="M2 12h6" stroke="%231976d2" stroke-width="2"/><path d="M22 12h-6" stroke="%231976d2" stroke-width="2"/></g></svg>') no-repeat center/contain;
    animation: spin 1s linear infinite;
}

.status-bulb {
    display: inline-block;
    width: 22px;
    height: 22px;
    background: url('data:image/svg+xml;utf8,<svg width="22" height="22" viewBox="0 0 22 22" fill="none" xmlns="http://www.w3.org/2000/svg"><ellipse cx="11" cy="8" rx="6" ry="7" fill="%23ffd600"/><rect x="8" y="15" width="6" height="4" rx="2" fill="%23ffd600"/></svg>') no-repeat center/contain;
    animation: blink 0.7s steps(2, start) infinite;
}

.status-thermo {
    display: inline-block;
    width: 22px;
    height: 22px;
    background: url('data:image/svg+xml;utf8,<svg width="22" height="22" viewBox="0 0 22 22" fill="none" xmlns="http://www.w3.org/2000/svg"><rect x="9" y="4" width="4" height="10" rx="2" fill="%231976d2"/><circle cx="11" cy="17" r="4" fill="%23ff5252"/></svg>') no-repeat center/contain;
    animation: pulse 1s ease-in-out infinite;
}

.status-spin {
    display: inline-block;
    width: 22px;
    height: 22px;
    border: 3px solid #b2d7ff;
    border-top: 3px solid #1976d2;
    border-radius: 50%;
    animation: spin 1s linear infinite;
}

)rawliteral";

const char THEME_SWITCHER_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   THEME SWITCHER
   =================================== */

#darkmode-switcher {
    position: fixed;
    top: 18px;
    right: 18px;
    z-index: 101;
    user-select: none;
}

.switch {
    display: inline-block;
    width: 56px;
    height: 32px;
    position: relative;
}

.switch .slider {
    position: absolute;
    cursor: pointer;
    top: 0;
    left: 0;
    right: 0;
    bottom: 0;
    background: #e0e0e0;
    border-radius: 20px;
    transition: background 0.3s;
    overflow: hidden;
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 0 6px;
}

.switch .icon {
    width: 22px;
    height: 22px;
    display: block;
    position: relative;
    transition: transform 0.4s cubic-bezier(.68, -0.55, .27, 1.55), opacity 0.3s;
    opacity: 0;
    pointer-events: none;
}

.switch .icon.sun {
    background: url('data:image/svg+xml;utf8,<svg width="22" height="22" viewBox="0 0 22 22" fill="none" xmlns="http://www.w3.org/2000/svg"><circle cx="11" cy="11" r="7" fill="%23ffd600"/><g stroke="%23ffd600" stroke-width="2"><line x1="11" y1="2" x2="11" y2="6"/><line x1="11" y1="16" x2="11" y2="20"/><line x1="2" y1="11" x2="6" y2="11"/><line x1="16" y1="11" x2="20" y2="11"/><line x1="5" y1="5" x2="7" y2="7"/><line x1="15" y1="15" x2="17" y2="17"/><line x1="5" y1="17" x2="7" y2="15"/><line x1="15" y1="7" x2="17" y2="5"/></g></svg>') no-repeat center/contain;
    opacity: 1;
    transform: translateX(0);
}

.switch .icon.moon {
    background: url('data:image/svg+xml;utf8,<svg width="22" height="22" viewBox="0 0 22 22" fill="none" xmlns="http://www.w3.org/2000/svg"><path d="M16 11c0 3.314-2.686 6-6 6a6 6 0 010-12c.34 0 .675.03 1 .09A7.001 7.001 0 0016 11z" fill="%2390caf9"/></svg>') no-repeat center/contain;
    opacity: 0;
    transform: translateX(-18px);
}

.switch input:checked+.slider .icon.sun {
    opacity: 0;
    transform: translateX(18px) scale(0.8);
}

.switch input:checked+.slider .icon.moon {
    opacity: 1;
    transform: translateX(0) scale(1.1);
}

.switch .slider:before {
    content: '';
    position: absolute;
    left: 4px;
    top: 4px;
    width: 24px;
    height: 24px;
    background: #fff;
    border-radius: 50%;
    box-shadow: 0 2px 8px #1976d244;
    transition: left 0.4s cubic-bezier(.68, -0.55, .27, 1.55), background 0.3s;
}

.switch input:checked+.slider:before {
    left: 28px;
    background: #222;
}

)rawliteral";

const char WEATHER_BG_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   WEATHER BACKGROUND & EFFECTS
   =================================== */

#weather-bg {
    position: fixed;
    top: 0;
    left: 0;
    width: 100vw;
    height: 100vh;
    pointer-events: none;
    z-index: 0;
    overflow: hidden;
}

#sun-bg,
#moon-bg {
    position: absolute;
    left: 80%;
    top: 12%;
    transform: translate(-50%, 0);
    width: 120px;
    height: 120px;
    z-index: 1;
    transition: opacity 0.7s, filter 0.7s;
    filter: drop-shadow(0 0 32px #ffd60088);
    opacity: 1;
    animation: sunfloat 8s ease-in-out infinite alternate;
}

#moon-bg {
    filter: drop-shadow(0 0 32px #90caf988);
    animation: moonfloat 8s ease-in-out infinite alternate;
}

/* Weather effects container */
#weather-effects {
    position: fixed;
    top: 0;
    left: 0;
    width: 100vw;
    height: 100vh;
    pointer-events: none;
    z-index: 12;
    overflow: hidden;
}

/* Thunder flash effect */
#thunder-flash {
    position: fixed;
    top: 0;
    left: 0;
    width: 100vw;
    height: 100vh;
    background: linear-gradient(120deg, rgba(160, 160, 170, 0.55) 0%, rgba(200, 200, 210, 0.7) 100%) !important;
    opacity: 0;
    pointer-events: none;
    z-index: 0;
    transition: opacity 0.2s;
    mix-blend-mode: lighten;
}

)rawliteral";

const char WEATHER_EFFECTS_CSS[] PROGMEM = R"rawliteral(
/* ===================================
   WEATHER EFFECTS
   =================================== */

/* Rain drop style */
.raindrop {
    position: absolute;
    width: 2px;
    height: 18px;
    background: linear-gradient(to bottom, #90caf9 60%, transparent 100%);
    opacity: 0.7;
    border-radius: 1px;
    animation: raindrop-fall 1.2s linear infinite;
}

/* Snowflake style */
.snowflake {
    position: absolute;
    top: -32px;
    color: #90caf9;
    opacity: 0.85;
    animation: snowflake-fall 3.5s linear infinite;
    pointer-events: none;
    user-select: none;
    will-change: transform;
}

/* Thunderbolt style */
.thunderbolt {
    position: absolute;
    top: 0;
    width: 32px;
    height: 64px;
    opacity: 0.85;
    animation: thunderbolt-flash 1.2s linear infinite;
    pointer-events: none;
    z-index: 3;
}

)rawliteral";

