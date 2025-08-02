// Backend communication: fetch commands
import { getText, getCurrentLang } from './localization.js';
export function setMode(val) {
    window.setStatus(getText('status_mode'), true);
    fetch('/setmode?mode=' + val)
        .then(response => {
            if (!response.ok) throw new Error('HTTP error');
            return response.text();
        })
        .then(text => window.setStatus(text))
        .catch(() => window.setStatus(getText('error')));
}
export function setAirflow(val) {
    window.setStatus(getText('status_airflow'), true);
    fetch('/setairflow?airflow=' + val)
        .then(response => {
            if (!response.ok) throw new Error('HTTP error');
            return response.text();
        })
        .then(text => window.setStatus(text))
        .catch(() => window.setStatus(getText('error')));
}
export function setFan(val) {
    window.setStatus(getText('status_fan'), true);
    fetch('/setfan?fan=' + val)
        .then(response => {
            if (!response.ok) throw new Error('HTTP error');
            return response.text();
        })
        .then(text => window.setStatus(text))
        .catch(() => window.setStatus(getText('error')));
}
export function sendCommand(path, msg) {
    window.setStatus(msg + (getCurrentLang() === 'en' ? ' (in progress...)' : ' (folyamatban...)'), true);
    fetch(path)
        .then(response => response.text())
        .then(text => window.setStatus(text))
        .catch(() => window.setStatus(getText('error')));
}
export function setTemperature(val) {
    window.setStatus(getText('status_set'), true);
    fetch('/set?temp=' + val)
        .then(response => response.text())
        .then(text => window.setStatus(text))
        .catch(() => window.setStatus(getText('error')));
    localStorage.setItem('climate_temp', val);
}
