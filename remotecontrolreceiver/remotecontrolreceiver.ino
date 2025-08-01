#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t kRecvPin = 14;  // D5 pin (GPIO14)

IRrecv irrecv(kRecvPin);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();  // IR vevő indítása
  Serial.println("IR vevő készen áll. Nyomj meg egy gombot a távirányítón.");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(resultToHumanReadableBasic(&results));
    Serial.println(resultToSourceCode(&results));  // RAW kód generálása
    irrecv.resume();  // Következő jel fogadása
  }
}
