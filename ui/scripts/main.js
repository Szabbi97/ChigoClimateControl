// --- Climate Control UI Logic ---
// Button group selection logic (SRP: UI state)
function selectMode(btn) {
    document.querySelectorAll('.mode-btn').forEach(b => b.classList.remove('selected'));
    btn.classList.add('selected');
    const val = btn.getAttribute('data-value');
    setMode(val);
    localStorage.setItem('climate_mode', val);
}
function selectAirflow(btn) {
    document.querySelectorAll('.airflow-btn').forEach(b => b.classList.remove('selected'));
    btn.classList.add('selected');
    const val = btn.getAttribute('data-value');
    setAirflow(val);
    localStorage.setItem('climate_airflow', val);
}
function selectFan(btn) {
    document.querySelectorAll('.fan-btn').forEach(b => b.classList.remove('selected'));
    btn.classList.add('selected');
    const val = btn.getAttribute('data-value');
    setFan(val);
    localStorage.setItem('climate_fan', val);
}

// --- State Initialization (SRP: UI state restore) ---
document.addEventListener('DOMContentLoaded', function () {
    // Restore from localStorage
    const savedMode = localStorage.getItem('climate_mode') || '1';
    const savedAirflow = localStorage.getItem('climate_airflow') || '0';
    const savedFan = localStorage.getItem('climate_fan') || '0';
    const savedTemp = localStorage.getItem('climate_temp') || '24';
    // Select mode button
    const modeBtn = document.querySelector('.mode-btn[data-value="' + savedMode + '"]');
    if (modeBtn) modeBtn.classList.add('selected');
    // Select airflow button
    const airflowBtn = document.querySelector('.airflow-btn[data-value="' + savedAirflow + '"]');
    if (airflowBtn) airflowBtn.classList.add('selected');
    // Select fan button
    const fanBtn = document.querySelector('.fan-btn[data-value="' + savedFan + '"]');
    if (fanBtn) fanBtn.classList.add('selected');
    // Restore temperature slider
    const slider = document.getElementById('temp');
    slider.value = savedTemp;
    updateTempValue(savedTemp);
});

// --- Language Management (SRP: Localization) ---
const texts = {
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
        error: "An error occurred!"
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
        error: "Hiba történt!"
    }
};
let currentLang = 'en';
function setLang(lang) {
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
    // Highlight selected flag
    document.getElementById('lang-en').classList.toggle('selected', lang === 'en');
    document.getElementById('lang-hu').classList.toggle('selected', lang === 'hu');
}
function getText(key) {
    return typeof texts[currentLang][key] === 'function' ? texts[currentLang][key](document.getElementById('temp').value) : texts[currentLang][key];
}

// --- Climate Control Commands (SRP: Backend communication) ---
function setMode(val) {
    setStatus(getText('status_mode'), true);
    fetch('/setmode?mode=' + val)
        .then(response => {
            if (!response.ok) throw new Error('HTTP error');
            return response.text();
        })
        .then(text => setStatus(text))
        .catch(() => setStatus(getText('error')));
}
function setAirflow(val) {
    setStatus(getText('status_airflow'), true);
    fetch('/setairflow?airflow=' + val)
        .then(response => {
            if (!response.ok) throw new Error('HTTP error');
            return response.text();
        })
        .then(text => setStatus(text))
        .catch(() => setStatus(getText('error')));
}
function setFan(val) {
    setStatus(getText('status_fan'), true);
    fetch('/setfan?fan=' + val)
        .then(response => {
            if (!response.ok) throw new Error('HTTP error');
            return response.text();
        })
        .then(text => setStatus(text))
        .catch(() => setStatus(getText('error')));
}
function sendCommand(path, msg) {
    setStatus(msg + (currentLang === 'en' ? ' (in progress...)' : ' (folyamatban...)'), true);
    fetch(path)
        .then(response => response.text())
        .then(text => setStatus(text))
        .catch(() => setStatus(getText('error')));
}
function setTemperature(val) {
    setStatus(getText('status_set'), true);
    fetch('/set?temp=' + val)
        .then(response => response.text())
        .then(text => setStatus(text))
        .catch(() => setStatus(getText('error')));
    localStorage.setItem('climate_temp', val);
}

// --- Status Display Logic (SRP: UI feedback) ---
function setStatus(msg, loading = false) {
    const status = document.getElementById('status');
    status.innerHTML = '';
    if (loading) {
        // Select animation by message
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

// --- Temperature Slider Logic (SRP: UI temperature) ---
function updateTempValue(val) {
    document.getElementById('temp-value').innerText = val + ' °C';
    // Color scale: 18°C = blue, 24°C = yellow, 30°C = red
    const slider = document.getElementById('temp');
    val = parseInt(val);
    let r, g, b;
    // Simplified: blue (20°C) -> green (24°C) -> red (30°C)
    if (val <= 20) {
        r = 25;
        g = 118;
        b = 210;
        // blue
    } else if (val < 24) {
        // blue -> green
        const ratio = (val - 20) / 4;
        r = Math.round(25 + (76 - 25) * ratio);
        g = Math.round(118 + (175 - 118) * ratio);
        b = Math.round(210 + (80 - 210) * ratio);
    } else if (val <= 30) {
        // green -> red
        const ratio = (val - 24) / 6;
        r = Math.round(76 + (255 - 76) * ratio);
        g = Math.round(175 + (82 - 175) * ratio);
        b = Math.round(80 + (82 - 80) * ratio);
    } else {
        r = 255;
        g = 82;
        b = 82;
        // red
    }
    // RGB -> HEX conversion
    function rgbToHex(r, g, b) {
        return '#' + [r, g, b].map(x => x.toString(16).padStart(2, '0')).join('');
    }
    const hexColor = rgbToHex(r, g, b);
    // Only change accentColor (thumb/filled part), not track background
    // Remove previous dynamic style if exists
    let prevStyle = document.getElementById('slider-accent-style');
    if (prevStyle) prevStyle.remove();
    // Create new style element for accent-color
    const style = document.createElement('style');
    style.id = 'slider-accent-style';
    style.textContent = `#temp { accent-color: ${hexColor}; }`;
    document.head.appendChild(style);
}
let tempTimeout;
function autoSetTemperature(val) {
    clearTimeout(tempTimeout);
    tempTimeout = setTimeout(() => setTemperature(val), 400);
}
const slider = document.getElementById('temp');
updateTempValue(slider.value);

// --- Dark Mode Logic (SRP: Theme management) ---
function applyDarkMode(dark) {
    document.body.classList.toggle('darkmode', dark);
    document.querySelector('.container').classList.toggle('darkmode', dark);
    document.getElementById('status').classList.toggle('darkmode', dark);
    document.getElementById('lang-switcher').classList.toggle('darkmode', dark);
    document.querySelectorAll('button, select, input[type="submit"], .slider-label, .temp-value, label, .mode-btn, .airflow-btn, .fan-btn, .power-on, .power-off').forEach(el => {
        el.classList.toggle('darkmode', dark);
    });
    document.getElementById('darkmode-toggle').checked = dark;
    // Sun/moon animation
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
function setDarkMode(dark) {
    applyDarkMode(dark);
    localStorage.setItem('climate_darkmode', dark ? '1' : '0');
}
document.getElementById('darkmode-toggle').addEventListener('change', function () {
    setDarkMode(this.checked);
});
document.addEventListener('DOMContentLoaded', function () {
    let darkPref = localStorage.getItem('climate_darkmode');
    if (darkPref === null) {
        darkPref = window.matchMedia && window.matchMedia('(prefers-color-scheme: dark)').matches ? '1' : '0';
    }
    setDarkMode(darkPref === '1');
});

// --- Weather Effects & API (SRP: Weather visualization) ---
function showRainEffect(count = 40) {
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
function showSnowEffect(count = 30) {
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
function showThunderEffect() {
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
function clearThunderEffect() {
    if (thunderFlashInterval) {
        clearTimeout(thunderFlashInterval);
        thunderFlashInterval = null;
    }
    const flashDiv = document.getElementById('thunder-flash');
    flashDiv.classList.remove('thunder-active');
}
function clearWeatherEffects() {
    document.getElementById('weather-effects').innerHTML = '';
    clearThunderEffect();
}
function showWeatherInfo(text) {
    const info = document.getElementById('weather-info');
    info.innerText = text;
    info.classList.add('visible');
}
function hideWeatherInfo() {
    document.getElementById('weather-info').classList.remove('visible');
}
function fetchWeatherForLocation() {
    if (!navigator.geolocation) return;
    navigator.geolocation.getCurrentPosition(function (pos) {
        const lat = pos.coords.latitude;
        const lon = pos.coords.longitude;
        // OpenWeatherMap API (replace YOUR_API_KEY with your own key)
        const apiKey = 'YOUR_API_KEY';
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
document.addEventListener('DOMContentLoaded', function () {
    fetchWeatherForLocation();
});

// --- Cloud Animation Logic (SRP: Weather visualization) ---
function createCloud(initialPosition = null, isInitial = false) {
    const cloudsContainer = document.getElementById('clouds-container');
    const cloud = document.createElement('div');
    cloud.className = 'cloud';
    // Random cloud size and position
    const size = Math.random() * 60 + 40; // 40-100px width
    const height = size * 0.5; // height is half the width
    const topPosition = Math.random() * 70 + 5; // 5-75% height
    const duration = Math.random() * 20 + 25; // 25-45 seconds
    cloud.style.width = size + 'px';
    cloud.style.height = height + 'px';
    cloud.style.top = topPosition + '%';
    // If initial position is given (on page load)
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
function createInitialClouds() {
    const numClouds = Math.floor(Math.random() * 6) + 10; // 10-15 clouds
    for (let i = 0; i < numClouds; i++) {
        const initialX = Math.random() * (window.innerWidth - 100);
        createCloud(initialX, true);
    }
}
function startCloudGeneration() {
    createCloud();
    const nextCloudDelay = Math.random() * 3000 + 2000;
    setTimeout(startCloudGeneration, nextCloudDelay);
}
document.addEventListener('DOMContentLoaded', function () {
    createInitialClouds();
    setTimeout(startCloudGeneration, 2000);
    const savedLang = localStorage.getItem('climate_lang');
    setLang(savedLang === 'hu' ? 'hu' : 'en');
});