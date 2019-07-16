/*
  Rotary Encoder Demo
  rot-encode-demo.ino
  Demonstrates operation of Rotary Encoder
  Displays results on Serial Monitor
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
#include<Arduino.h>
#include <String.h>

 // Rotary Encoder Inputs
 #define INTERRUPTPIN PB4


 void handle_interrupt();
 volatile int i = 0;
 
 int prev_i = i;


 void setup() {
   
   // Set encoder pins as inputs
   pinMode(INTERRUPTPIN, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(INTERRUPTPIN), handle_interrupt, RISING);
   



   // Setup Serial Monitor
   Serial.begin (115200);

   

 }

 void handle_interrupt()
 {
   i++;
 }

 void loop() {

   
   
   if(prev_i != i || i == 0){
      Serial.println(i);
      prev_i = i;
   }
   delay(10);
 
 }