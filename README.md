# 🌡️ Chigo Climate Control

Modern WiFi-based web interface for controlling Chigo air conditioners using ESP8266 microcontroller.

## ✨ Features

### 🎮 Climate Control
- **Power ON/OFF**: Remote control without physical remote
- **Temperature Setting**: 18-30°C range
- **Mode Selection**: 
  - 🔥 Heat
  - 💧 Dehumidify  
  - 🌬️ Fan
  - ❄️ Cool
- **Airflow Control**: Fixed or swing
- **Fan Speed**: Auto, low, medium, high

### 🌐 Modern Web Interface
- **📱 Responsive Design**: Mobile and desktop optimized
- **🌍 Multi-language**: Hungarian and English support
- **🌙 Dark/Light Theme**: Automatic switching
- **🌦️ Weather Animations**: Rain, snow, thunder effects
- **☁️ Dynamic Background**: Animated clouds and sun/moon

### 🏗️ Advanced Architecture
- **Modular Structure**: SRP-compliant code
- **Two Installation Methods**: SPIFFS or embedded files
- **API-based Communication**: RESTful endpoints
- **Error Handling**: Automatic reconnection

## 🛠️ Hardware Requirements

- **ESP8266** based board (NodeMCU, Wemos D1 mini)
- **IR LED** connected to appropriate GPIO (default: D2)
- **Reset button** (optional) connected to D1 (GPIO5) with pull-up resistor
- **Chigo air conditioner** (IR controlled)

## 💻 Software Requirements

- **Arduino IDE** or **PlatformIO**
- **ESP8266 board support** (via Boards Manager)
- **Libraries**:
  - ESP8266WiFi
  - ESP8266WebServer
  - FS (for SPIFFS version)
- **ESP8266FS plugin** (optional, for SPIFFS version)

## 📁 Project Structure

```
📁 ChigoClimateControl/
├── 📁 climatecontrol/              # Main Arduino project
│   ├── climatecontrol.ino          # Main program
│   ├── ChigoIRControl.h/cpp        # IR control
│   ├── WiFiControl.h/cpp           # WiFi connection
│   ├── WebServerControl.h/cpp      # Web server logic
│   ├── WebResources.h              # Embedded web files
│   └── 📁 data/                    # SPIFFS files
│       ├── index.html
│       ├── 📁 scripts/
│       └── 📁 styles/
├── 📁 tools/                       # Development tools
│   └── generate_web_resources.py   # File embedding script
├── 📁 remotecontrolreceiver/       # IR code decoder
├── 📄 SPIFFS_SETUP.md             # SPIFFS installation guide
├── 📄 UI_INTEGRATION_GUIDE.md     # UI integration guide
└── 📄 WEATHER_API_SETUP.md        # Weather API setup
```

## 🚀 Quick Installation

### 1. Download Project
```bash
git clone https://github.com/Szabbi97/ChigoClimateControl.git
cd ChigoClimateControl
```

### 2. WiFi Configuration
Edit `climatecontrol/climatecontrol.ino` file:
```cpp
const char *ssid = "YOUR_WIFI_SSID";        // WiFi network name
const char *password = "YOUR_WIFI_PASSWORD"; // WiFi password
```

### 3. Hardware Assembly
- **Detailed guide**: [`HARDWARE_ASSEMBLY.md`](HARDWARE_ASSEMBLY.md)
- Connect IR LED to D2 (GPIO4) pin
- **Optional**: Connect reset button between D1 (GPIO5) and GND
  - Use internal pull-up resistor (configured in code)
  - Hold for 3 seconds to reset WiFi settings
- Position ESP8266 facing the air conditioner

### 4. Upload (Embedded Version) - Recommended
1. Open `climatecontrol/climatecontrol.ino` in Arduino IDE
2. Select ESP8266 board type and port
3. Upload: **Ctrl+U**

### 5. Testing
1. Open **Serial Monitor** (9600 baud)
2. Note down ESP8266 IP address
3. Open in browser: `http://[ESP8266_IP]`

## 📖 Detailed Guides

- **🔧 SPIFFS version installation**: [`SPIFFS_SETUP.md`](SPIFFS_SETUP.md)
- **🔀 Version switching guide**: [`UI_INTEGRATION_GUIDE.md`](UI_INTEGRATION_GUIDE.md)
- **🌦️ Weather API setup**: [`WEATHER_API_SETUP.md`](WEATHER_API_SETUP.md)

## 🎯 Usage

### Web Interface
1. **Language switching**: Click English/Hungarian flag icons
2. **Theme switching**: Sun/moon icon in bottom right corner
3. **Climate control**: Use sliders and buttons
4. **Status monitoring**: Real-time feedback

### API Endpoints
```http
GET /status                    # Device status
GET /on                        # Power on
GET /off                       # Power off
GET /set?temp=24              # Temperature setting
GET /setmode?mode=4           # Mode (1-4)
GET /setairflow?airflow=1     # Airflow (0-2)
GET /setfan?fan=2             # Fan speed (0-3)
```

### Console Commands (for Developers)
```javascript
// Weather effects testing
showRainEffect();      // Rain animation
showSnowEffect();      // Snow animation
showThunderEffect();   // Thunder effect
clearWeatherEffects(); // Clear effects

// Information display
showWeatherInfo("Test message");
hideWeatherInfo();
```

## ⚙️ Configuration Options

### Hardware Pin Assignment
```cpp
ChigoIRControl chigoIR(4); // D2 pin (GPIO4)
#define RESET_BUTTON_PIN 5  // D1 pin (GPIO5) - optional reset button
```

### WiFi Reset Options
1. **Hardware Reset Button** (recommended):
   - Connect button between D1 (GPIO5) and GND
   - Hold for 3 seconds to clear WiFi settings
   - Device will restart in configuration mode

2. **Serial Command**:
   - Open Serial Monitor (9600 baud)
   - Send: `CLEAR_WIFI`
   - Device will restart in configuration mode

3. **Configuration Portal**:
   - Automatically starts if no WiFi credentials stored
   - Creates "ChigoSetup" WiFi network
   - Browse to: `192.168.4.1`

### Weather API (Optional)
1. Register at: https://openweathermap.org/api
2. Set up API key
3. Details: [`WEATHER_API_SETUP.md`](WEATHER_API_SETUP.md)

## 🐛 Troubleshooting

### Common Issues
- **WiFi connection error**: Check SSID/password pair
- **IR not working**: Check LED polarity and position
- **Web page not loading**: Check IP address and firewall
- **Compilation error**: Install ESP8266 core and libraries

### Debug Information
```cpp
Serial.begin(9600);  // Use Serial Monitor
```

## 🛡️ Security

- **API keys**: Don't commit real API keys
- **WiFi authentication**: Use strong passwords
- **Network security**: Use on local network

## 🤝 Contributing

1. **Fork** the repository
2. **Create feature branch**: `git checkout -b feature/NewFeature`
3. **Commit changes**: `git commit -m 'Add new feature'`
4. **Push to branch**: `git push origin feature/NewFeature`
5. **Create Pull Request**

## 📄 License

MIT License - see [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Szabbi97** - [GitHub Profile](https://github.com/Szabbi97)

## 🌟 Acknowledgments

- **Arduino community** - for ESP8266 support
- **OpenWeatherMap** - for weather API service
- **Modern web technologies** - for responsive design inspiration

---

⭐ **If you like this project, give it a star!** ⭐
