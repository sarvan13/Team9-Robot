#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>
#include "PinNames.h"

#define BPILL_ADDRESS 5

#define LED_PIN A7

volatile byte x = 1;

void receiveEvent(int numBytes) {
  digitalWrite(LED_PIN, LOW);
  Serial.println("received");
  x = Wire.read();
  Serial.println(String(x));
  digitalWrite(LED_PIN, HIGH);
}

void requestEvent() {
  Wire.write(2);
  Serial.println("reQUESTED");
  // digitalWrite(LED_PIN, HIGH);
  // delay(200);
  // Wire.write(17);
  // digitalWrite(LED_PIN, LOW);
}

void setup() {
  delay(5000);
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  Wire.begin(BPILL_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.println("setup");
  delay(2000);
}

void loop() {
  delay(500);
}