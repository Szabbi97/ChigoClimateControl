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
