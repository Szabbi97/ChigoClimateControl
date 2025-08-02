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
