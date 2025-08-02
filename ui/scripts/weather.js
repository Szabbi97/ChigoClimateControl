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
