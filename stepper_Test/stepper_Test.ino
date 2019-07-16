#include <Arduino.h>

#define POT PA5
#define STEP PA2
#define LOOP_DELAY 10
#define MAX_PERIOD 2000

double period = 0;
int timer = 0, oldValue = 0;

void setup() {
    Serial.begin(115200);
    pinMode(POT, INPUT_ANALOG);
    pinMode(STEP, OUTPUT);
}

void loop() {
    double value = analogRead(POT);
    Serial.println(value);
    if (abs(oldValue - value) > 10 && value > 10) {
      period = value/4095 * MAX_PERIOD;
      oldValue = value;
    }

    if (timer > period) {
      timer = 0;
      digitalWrite(STEP, !digitalRead(STEP));
    }
    timer += LOOP_DELAY;
    delayMicroseconds(LOOP_DELAY);
}
