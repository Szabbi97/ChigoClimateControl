#ifndef CHIGO_IR_CONTROL_H
#define CHIGO_IR_CONTROL_H

#include <IRremoteESP8266.h>
#include <IRsend.h>

class ChigoIRControl {
public:
    ChigoIRControl(uint16_t irLedPin);
    void begin();
    void powerOn();
    void powerOff();
    bool setTemperature(int temp);
    bool setMode(int mode); // 1: heating, 2: drying, 3: blowing, 4: cooling
    bool setAirflow(int airflow); // 0: none, 1: 1f, 2: swing
    bool setFanSpeed(int speed); // 0: auto, 1: low, 2: medium, 3: high

    // IR raw data arrays for modes
    static const uint16_t rawData_mode_heating[99];
    static const uint16_t rawData_mode_drying[99];
    static const uint16_t rawData_mode_blowing[99];
    static const uint16_t rawData_mode_cooling[99];
    // IR raw data arrays for airflow
    static const uint16_t rawData_airflow_none[99];
    static const uint16_t rawData_airflow_1f[99];
    static const uint16_t rawData_airflow_swing[99];
    // IR raw data arrays for fan
    static const uint16_t rawData_fan_auto[99];
    static const uint16_t rawData_fan_low[99];
    static const uint16_t rawData_fan_medium[99];
    static const uint16_t rawData_fan_high[99];

private:
    IRsend irsend;
    static const uint16_t rawData_on[99];
    static const uint16_t rawData_off[99];
    static const uint16_t rawData_18[99];
    static const uint16_t rawData_19[99];
    static const uint16_t rawData_20[99];
    static const uint16_t rawData_21[99];
    static const uint16_t rawData_22[99];
    static const uint16_t rawData_23[99];
    static const uint16_t rawData_24[99];
    static const uint16_t rawData_25[99];
    static const uint16_t rawData_26[99];
    static const uint16_t rawData_27[99];
    static const uint16_t rawData_28[99];
    static const uint16_t rawData_29[99];
    static const uint16_t rawData_30[99];
};

#endif // CHIGO_IR_CONTROL_H
