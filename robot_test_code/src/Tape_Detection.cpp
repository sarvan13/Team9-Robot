#include <Tape_Detection.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "PinNames.h"

#define MULTIPLEX_OUT PA5
#define A PB12  // Left = 000 - Right = 
#define B PB13
#define C PB14
#define TAPEFOLLOWTHRESH 500
#define LEFT_THRESH 800
#define RIGHT_THRESH 800

#define HARDCODE_KP 120 //240
#define HARDCODE_KD 25 //50
#define COUNTER_VAL 0


Tape_Detection::Tape_Detection(){
    pinMode(MULTIPLEX_OUT, INPUT_ANALOG);
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
}

branch_state Tape_Detection::branch_exists(){
  // digitalWrite(A, LOW);
  // digitalWrite(B, LOW);
  // digitalWrite(C, HIGH);
  // float cornerLeftSensor = analogRead(MULTIPLEX_OUT);

  // digitalWrite(A, LOW);
  // digitalWrite(B, HIGH);
  // digitalWrite(C, HIGH);
  // float cornerRightSensor = analogRead(MULTIPLEX_OUT);
  
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  float cornerRightSensor = analogRead(MULTIPLEX_OUT);

  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  float cornerLeftSensor = analogRead(MULTIPLEX_OUT);

  Serial.print(cornerLeftSensor); Serial.print(" "); Serial.print(cornerRightSensor);  Serial.print(" "); 
  if(cornerLeftSensor > LEFT_THRESH) {
    branch_side = LEFT_BRANCH;
    Serial.println("Left Branch");
    return LEFT_BRANCH;
  } else if(cornerRightSensor > RIGHT_THRESH) {
    branch_side = RIGHT_BRANCH;
    Serial.println("Right Branch");
    return RIGHT_BRANCH;
  } else {
    Serial.println("No Branch");
    branch_side = NO_BRANCH;
    return NO_BRANCH;
  }
}

marker_state Tape_Detection::marker_exists(){
  float sideRightSensor1 = analogRead(MULTIPLEX_OUT);
  float sideRightSensor2 = analogRead(MULTIPLEX_OUT);
  float sideRightSensor3 = analogRead(MULTIPLEX_OUT);
  float sideLeftSensor1 = analogRead(MULTIPLEX_OUT);
  float sideLeftSensor2 = analogRead(MULTIPLEX_OUT);
  float sideLeftSensor3 = analogRead(MULTIPLEX_OUT);

  if(sideLeftSensor1 > TAPEFOLLOWTHRESH || sideLeftSensor2 > TAPEFOLLOWTHRESH || sideLeftSensor3 > TAPEFOLLOWTHRESH){
    return LEFT_MARKER;
  }else if(sideRightSensor1 > TAPEFOLLOWTHRESH || sideRightSensor2 > TAPEFOLLOWTHRESH || sideRightSensor3 > TAPEFOLLOWTHRESH){
    return RIGHT_MARKER;
  }else{
    return NO_MARKER;
  }
}

int Tape_Detection::get_pid(){
    error = get_path_error();
    float p =  HARDCODE_KP * error;
    float d =  HARDCODE_KD * (error - previous_error);
    return p + d; // = g
}

int Tape_Detection::get_path_error(){
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  float mainLeftSensor = analogRead(MULTIPLEX_OUT);
  Serial.print(mainLeftSensor); Serial.print(" ");

  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  float mainMiddleSensor = analogRead(MULTIPLEX_OUT);
  Serial.print(mainMiddleSensor); Serial.print(" ");

  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  float mainRightSensor = analogRead(MULTIPLEX_OUT);
  Serial.print(mainRightSensor); Serial.print(" ");


  previous_error = error;
   if (mainRightSensor < TAPEFOLLOWTHRESH && mainLeftSensor < TAPEFOLLOWTHRESH && mainMiddleSensor < TAPEFOLLOWTHRESH) {
        if (previous_error < 0){
            error = -4;
        } else {
            error = 4;
        }
  } else if (mainLeftSensor < TAPEFOLLOWTHRESH && mainMiddleSensor < TAPEFOLLOWTHRESH){
      error = -2;
  } else if (mainLeftSensor < TAPEFOLLOWTHRESH) {
      error = -1;
  } else if (mainRightSensor< TAPEFOLLOWTHRESH && mainMiddleSensor < TAPEFOLLOWTHRESH) {
      error = 2;
  } else if (mainRightSensor< TAPEFOLLOWTHRESH) {
      error = 1;
  } else {
      error = 0;
  }
  Serial.println(error); 
  return error;
}

int Tape_Detection::get_marker_error(){

}

