#include <Communication.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <FreeMono12pt7b.h>
#include <FreeMono9pt7b.h>
#include <stdint.h>
#include "PinNames.h"

#define BPILL_ADDRESS 5

Communication::Communication(){
    Wire.begin();
}

void Communication::master_request(){
  Serial.println("Entering master request");
  delay(500);
  Wire.requestFrom(BPILL_ADDRESS,1,1);
  delay(500);
  while(Wire.available()){
    byte a = Wire.read();
    Serial.println(a);
  }
  delay(5000);
}

void Communication::master_transmit_stone(){
  Wire.beginTransmission(BPILL_ADDRESS);                           
  Wire.write(12);                        
  Wire.endTransmission(); 
  delay(7000);
}

void Communication::master_transmit_gauntlet(){
  Wire.beginTransmission(BPILL_ADDRESS);                           
  Wire.write(12);                        
  Wire.endTransmission(); 
  delay(7000);
}


