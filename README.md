# Chigo Climate Control

A WiFi-enabled web interface for controlling Chigo air conditioners using an ESP8266 microcontroller.

## Features
- Web-based user interface for controlling the air conditioner
- Power ON/OFF and temperature setting
- Responsive, mobile-friendly UI with animated background
- Modular code structure (SRP-compliant):
  - Web server logic
  - IR control logic
  - WiFi connection logic

## Hardware Requirements
- ESP8266-based board (e.g., NodeMCU, Wemos D1 mini)
- IR LED connected to the appropriate GPIO (default: D2)
- Chigo air conditioner (IR controlled)

## Software Requirements
- Arduino IDE
- ESP8266 board support (install via Boards Manager)
- Required libraries:
  - ESP8266WiFi
  - ESP8266WebServer

## File Structure
- `climatecontrol/`
  - `climatecontrol.ino` - Main entry point, only initializes modules
  - `ChigoIRControl.h/cpp` - IR control logic for Chigo AC
  - `WiFiControl.h/cpp` - WiFi connection logic
  - `WebServerControl.h/cpp` - Web server and HTTP endpoint logic
- `misc/`
  - `climate_control_interface.html` - Standalone HTML UI (optional)
- `remotecontrolreceiver/`
  - `remotecontrolreceiver.ino` - (Optional) IR receiver utility

## Quick Start
1. Clone the repository and open `climatecontrol.ino` in Arduino IDE.
2. Set your WiFi credentials in `climatecontrol.ino`:
   ```cpp
   const char *ssid = "YOUR_WIFI_SSID";
   const char *password = "YOUR_WIFI_PASSWORD";
   ```
3. Connect the IR LED to the correct pin (default: D2).
4. Select the correct board and port in Arduino IDE.
5. Upload the code to your ESP8266.
6. After boot, connect to the same WiFi network and open the device's IP address in your browser.

## Usage
- Use the web interface to turn the air conditioner ON/OFF and set the temperature.
- The UI is mobile-friendly and works in any modern browser.

## Project Structure & SRP
- Each module (WiFi, IR, Web) is separated for maintainability and clarity.
- The main `.ino` file only initializes and delegates to these modules.

## License
MIT License

## Author
Szabbi97
