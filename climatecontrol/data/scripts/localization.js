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
