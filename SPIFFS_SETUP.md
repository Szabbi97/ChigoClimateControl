# SPIFFS Web Interface Integration

This document describes how to integrate the advanced UI web interface into the Arduino ESP8266 project using SPIFFS.

## Prerequisites

1. **Arduino IDE** installed
2. **ESP8266 board package** installed in Arduino IDE
3. **ESP8266FS plugin** installed (for SPIFFS data upload)

## ESP8266FS Plugin Installation

1. Download ESP8266FS plugin: https://github.com/esp8266/arduino-esp8266fs-plugin
2. Extract and place in Arduino IDE tools folder:
   - Windows: `C:\Users\{username}\Documents\Arduino\tools\ESP8266FS\tool\esp8266fs.jar`
3. Restart Arduino IDE

## Usage

### 1. Code Upload

1. Open `climatecontrol/climatecontrol.ino` file in Arduino IDE
2. Set your WiFi network name and password:
   ```cpp
   const char *ssid = "YOUR_SSID";     // Replace with your WiFi name
   const char *password = "YOUR_PASSWORD"; // Replace with your WiFi password
   ```
3. Select appropriate ESP8266 board type and port
4. Upload code to ESP8266

### 2. SPIFFS Data Upload

1. In Arduino IDE go to **Tools > ESP8266 Sketch Data Upload**
2. Wait for upload to complete
3. This uploads all files in the `data/` folder to ESP8266 SPIFFS filesystem

### 3. Device Testing

1. Open Serial Monitor (9600 baud)
2. After ESP8266 restart you'll see connection information
3. Note down ESP8266 IP address
4. Open in browser: `http://[ESP8266_IP]`

## Features

The web interface provides the following features:

- **Modern UI**: Responsive design, dark/light theme
- **Multi-language support**: Hungarian and English
- **Weather animations**: Visual effects
- **Climate control**:
  - Power ON/OFF
  - Temperature setting (18-30°C)
  - Mode switching (heat, dehumidify, fan, cool)
  - Airflow setting
  - Fan speed setting

## API Endpoints

The web interface uses the following API endpoints:

- `GET /status` - Device status query
- `GET /on` - Turn air conditioner on
- `GET /off` - Turn air conditioner off
- `GET /set?temp=XX` - Temperature setting
- `GET /setmode?mode=X` - Mode setting (1=heat, 2=dehumidify, 3=fan, 4=cool)
- `GET /setairflow?airflow=X` - Airflow setting (0=off, 1=fixed, 2=swing)
- `GET /setfan?fan=X` - Fan speed (0=auto, 1=low, 2=medium, 3=high)

## Troubleshooting

### SPIFFS Mount Failed
If you see "SPIFFS mount failed" error:
1. Check that ESP8266FS plugin is properly installed
2. Try uploading SPIFFS data again
3. Check if there's enough memory on ESP8266

### Files not loading
1. Check Serial Monitor messages
2. Make sure files are in the `data/` folder
3. Try uploading SPIFFS data again

### WiFi connection problems
1. Check WiFi network name and password
2. Make sure ESP8266 is within WiFi range
3. Try restarting ESP8266

## Development

If you modify web interface files:
1. Save changes in the `ui/` folder
2. Copy files to the `data/` folder
3. Re-upload SPIFFS data using "ESP8266 Sketch Data Upload" function
