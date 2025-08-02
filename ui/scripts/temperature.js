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
