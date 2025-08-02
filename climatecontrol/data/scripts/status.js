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
