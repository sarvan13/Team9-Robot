#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>

#define POT PA5
#define STEP PA_2
#define MAX_PERIOD 0.01
#define MIN_PERIOD 0.0001
#define CLOCKF 100000

double period = 0.003;  // Value in seconds
double oldValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(POT, INPUT_ANALOG);
  pinMode(STEP, OUTPUT);
}

void loop() {
  double value = analogRead(POT);
  if (abs(value - oldValue) > 20 && value > 10) {
    period = value/1023 * (MAX_PERIOD - MIN_PERIOD) + MIN_PERIOD;
    pwm_start(STEP, CLOCKF, period * CLOCKF, period/2 * CLOCKF, 1);
    Serial.println(value);
    oldValue = value;
  }
  delay(10);
}
