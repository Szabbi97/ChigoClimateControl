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
