# 🔌 Hardware Assembly Guide

## 📋 Components Required

### Essential Components
- **ESP8266** development board (NodeMCU v1.0 or Wemos D1 Mini)
- **IR LED** (940nm recommended)
- **220Ω resistor** for IR LED
- **Breadboard** or **PCB** for connections
- **Jumper wires**

### Optional Components
- **Reset button** (momentary push button)
- **Pull-up resistor** 10kΩ (if not using internal pull-up)
- **Enclosure** for protection

## 🔗 Pin Connections

### ESP8266 NodeMCU v1.0 Pinout
```
                   ┌─────────────────┐
                   │  ESP8266 NodeMCU │
                   │                 │
              3V3  ├─1             30─┤ VIN
              GND  ├─2             29─┤ GND  
               A0  ├─3             28─┤ 3V3
              D0   ├─4             27─┤ EN
              D1   ├─5  RESET BTN  26─┤ RST
              D2   ├─6   IR LED    25─┤ D8
              D3   ├─7             24─┤ D7
              D4   ├─8             23─┤ D6
              D5   ├─9             22─┤ D5
              D6   ├─10            21─┤ GND
              D7   ├─11            20─┤ 3V3
              D8   ├─12            19─┤ D4
              RX   ├─13            18─┤ D3
              TX   ├─14            17─┤ D2
              GND  ├─15            16─┤ D1
                   └─────────────────┘
```

### Connection Table
| Component | ESP8266 Pin | GPIO | Notes |
|-----------|-------------|------|--------|
| IR LED (+) | D2 | GPIO4 | Through 220Ω resistor |
| IR LED (-) | GND | - | Direct connection |
| Reset Button | D1 | GPIO5 | One side to pin, other to GND |
| Reset Button | GND | - | Internal pull-up used |

## 🔌 Wiring Diagrams

### Minimal Setup (IR LED Only)
```
ESP8266 D2 ──[220Ω]──┤>├── GND
                    IR LED
```

### Complete Setup (IR LED + Reset Button)
```
ESP8266 D2 ──[220Ω]──┤>├── GND
                    IR LED

ESP8266 D1 ──┐
             │ Push Button
ESP8266 GND ─┘
```

## 🛠️ Assembly Steps

### Step 1: IR LED Connection
1. **Connect IR LED anode** (longer leg) to **220Ω resistor**
2. **Connect resistor** to **ESP8266 D2 pin**
3. **Connect IR LED cathode** (shorter leg) to **ESP8266 GND**

### Step 2: Reset Button (Optional)
1. **Connect one button terminal** to **ESP8266 D1 pin**
2. **Connect other button terminal** to **ESP8266 GND**
3. **No external pull-up needed** (internal pull-up used)

### Step 3: Power Supply
1. **USB power**: Connect USB cable to ESP8266
2. **External power**: Use 3.3V or 5V to VIN pin (5V recommended)

## 🧪 Testing Connections

### 1. Power Test
- Upload any basic sketch
- Check Serial Monitor for boot messages
- LED should blink on boot

### 2. IR LED Test
```cpp
// Test code for IR LED
void setup() {
  pinMode(4, OUTPUT); // D2 pin
}

void loop() {
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  delay(500);
}
```

### 3. Reset Button Test
```cpp
void setup() {
  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP); // D1 pin
}

void loop() {
  if (digitalRead(5) == LOW) {
    Serial.println("Button pressed!");
    delay(100);
  }
}
```

## 🔧 Troubleshooting

### IR LED Issues
- **Check polarity**: Anode (+) to resistor, cathode (-) to GND
- **Check resistor value**: Should be 220Ω
- **Test with camera**: IR LED should glow on phone camera

### Reset Button Issues
- **Check wiring**: One side to D1, other to GND
- **Test continuity**: Button should show continuity when pressed
- **Check pin mode**: Must be INPUT_PULLUP

### Power Issues
- **Check USB cable**: Must support data transfer
- **Check power supply**: 3.3V minimum, 5V recommended
- **Check current**: IR LED draws ~20mA

## 📏 Physical Placement

### IR LED Positioning
- **Distance**: 1-3 meters from air conditioner
- **Angle**: Direct line of sight to AC IR receiver
- **Height**: Same level as AC unit (usually 2-3m high)

### ESP8266 Placement
- **WiFi range**: Within 10-30 meters of router
- **Accessibility**: Easy access for reset button
- **Ventilation**: Avoid enclosed spaces (heat dissipation)

## 🏠 Enclosure Ideas

### Simple Options
- **Plastic project box** (IP54 rated recommended)
- **3D printed case** (STL files can be provided)
- **Wall mount bracket**

### Professional Options
- **DIN rail mount enclosure**
- **Wall flush mount box**
- **Ceiling mount enclosure**

## ⚡ Power Consumption

| Component | Current Draw | Notes |
|-----------|-------------|--------|
| ESP8266 (active) | 80-170mA | During WiFi transmission |
| ESP8266 (idle) | 15-20mA | Connected to WiFi |
| IR LED | 20mA | Only during transmission |
| **Total** | **100-190mA** | Peak consumption |

### Power Supply Recommendations
- **USB adapter**: 5V/1A (1000mA) minimum
- **Battery operation**: 18650 Li-Ion (with charging circuit)
- **External PSU**: 5V/2A for reliable operation

## 📱 Mobile App Alternative

For easier configuration without reset button:
- Use **ESP8266 WiFi Manager** apps
- Scan for "ChigoSetup" network
- Configure via mobile browser at `192.168.4.1`
