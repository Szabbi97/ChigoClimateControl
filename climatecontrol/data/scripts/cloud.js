// Cloud animation logic
export function createCloud(initialPosition = null, isInitial = false) {
    const cloudsContainer = document.getElementById('clouds-container');
    const cloud = document.createElement('div');
    cloud.className = 'cloud';
    const size = Math.random() * 60 + 40;
    const height = size * 0.5;
    const topPosition = Math.random() * 70 + 5;
    const duration = Math.random() * 20 + 25;
    cloud.style.width = size + 'px';
    cloud.style.height = height + 'px';
    cloud.style.top = topPosition + '%';
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
export function createInitialClouds() {
    const numClouds = Math.floor(Math.random() * 6) + 10;
    for (let i = 0; i < numClouds; i++) {
        const initialX = Math.random() * (window.innerWidth - 100);
        createCloud(initialX, true);
    }
}
export function startCloudGeneration() {
    createCloud();
    const nextCloudDelay = Math.random() * 3000 + 2000;
    setTimeout(startCloudGeneration, nextCloudDelay);
}
