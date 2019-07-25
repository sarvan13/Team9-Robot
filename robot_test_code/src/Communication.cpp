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
  byte a = NOT_DONE;
  while(a == NOT_DONE){
    while(Wire.available()){
      a = Wire.read();
      Serial.println(a);
    }
    delay(5000);
  }
}

void Communication::master_transmit_stone_left(){
  Wire.beginTransmission(BPILL_ADDRESS);                           
  Wire.write(LEFT_POLE_PICKUP);                        
  Wire.endTransmission(); 
  delay(7000);
}

void Communication::master_transmit_stone_right(){
  Wire.beginTransmission(BPILL_ADDRESS);                           
  Wire.write(RIGHT_POLE_PICKUP);                        
  Wire.endTransmission(); 
  delay(7000);
}

void Communication::master_transmit_gauntlet(){
  Wire.beginTransmission(BPILL_ADDRESS);                           
  Wire.write(GAUNTLET_PICKUP);                        
  Wire.endTransmission(); 
  delay(7000);
}


