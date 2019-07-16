#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>

#include "PinNames.h"


#define LED_PIN PA7

#define BPILL_ADDRESS 5

volatile byte a = 1;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);


  digitalWrite(LED_PIN, HIGH);
  delay(5000);
  digitalWrite(LED_PIN, LOW);
  Wire.begin();

}


void masterRequest() {
  Serial.println("Entering master request");
  delay(500);
  Wire.requestFrom(BPILL_ADDRESS,1,1);
  delay(500);
  byte a = Wire.read();
  Serial.println(a);
  delay(5000);
}

void masterTransmit() {
  digitalWrite(LED_PIN, HIGH);
  delay(5);
  digitalWrite(LED_PIN, LOW);
  Wire.beginTransmission(BPILL_ADDRESS);                           
  Wire.write(12);                        
  Wire.endTransmission(); 
  delay(7000);
}

void loop() {
  Serial.println("Looping");
  delay(500);
  masterRequest();
   masterTransmit();
}