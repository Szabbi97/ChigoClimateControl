// Main entry: import modules and initialize
import { selectMode, selectAirflow, selectFan, restoreUIState } from './uiState.js';
import { setLang, getText, texts } from './localization.js';
import { setMode, setAirflow, setFan, sendCommand, setTemperature } from './api.js';
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

window.selectMode = selectMode;
window.selectAirflow = selectAirflow;
window.selectFan = selectFan;
window.autoSetTemperature = autoSetTemperature;

// Initialization
restoreUIState();
createInitialClouds();
setTimeout(startCloudGeneration, 2000);
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