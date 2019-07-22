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
#define MULTIPLEX_OUT2 PA4
#define TAPEFOLLOWTHRESH 500
#define LEFT_THRESH 800
#define RIGHT_THRESH 800

#define HARDCODE_KP 120 //240
#define HARDCODE_KD 25//50
#define COUNTER_VAL 0

Tape_Detection::Tape_Detection(){
    pinMode(MULTIPLEX_OUT, INPUT_ANALOG);
    pinMode(MULTIPLEX_OUT2, INPUT_ANALOG);
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

int Tape_Detection::marker_exists(){
  int error = 0;
  float front_right_sensor = analogRead(MULTIPLEX_OUT2);
  float back_right_sensor = analogRead(MULTIPLEX_OUT2);
  float right_sensor = analogRead(MULTIPLEX_OUT2);
  // float sideLeftSensor1 = analogRead(MULTIPLEX_OUT2);
  // float sideLeftSensor2 = analogRead(MULTIPLEX_OUT2);
  // float sideLeftSensor3 = analogRead(MULTIPLEX_OUT2);

  // if(sideLeftSensor1 > TAPEFOLLOWTHRESH || sideLeftSensor2 > TAPEFOLLOWTHRESH || sideLeftSensor3 > TAPEFOLLOWTHRESH){
  //   return LEFT_MARKER;
  //} else
  if(right_sensor > TAPEFOLLOWTHRESH){
    error |= RIGHT_ON;
  }
  marker_error = error;
  return error;
}

int Tape_Detection::get_pid(){
    path_error = get_path_error();
    float p =  HARDCODE_KP * path_error;
    float d =  HARDCODE_KD * (path_error - previous_path_error);
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


  previous_path_error = path_error;
   if (mainRightSensor < TAPEFOLLOWTHRESH && mainLeftSensor < TAPEFOLLOWTHRESH && mainMiddleSensor < TAPEFOLLOWTHRESH) {
        if (previous_path_error < 0){
            path_error = -4;
        } else {
            path_error = 4;
        }
  } else if (mainLeftSensor < TAPEFOLLOWTHRESH && mainMiddleSensor < TAPEFOLLOWTHRESH){
      path_error = -2;
  } else if (mainLeftSensor < TAPEFOLLOWTHRESH) {
      path_error = -1;
  } else if (mainRightSensor< TAPEFOLLOWTHRESH && mainMiddleSensor < TAPEFOLLOWTHRESH) {
      path_error = 2;
  } else if (mainRightSensor< TAPEFOLLOWTHRESH) {
      path_error = 1;
  } else {
      path_error = 0;
  }
  Serial.println(path_error); 
  return path_error;
}

int Tape_Detection::get_marker_error(){
  float front_right_marker = analogRead(MULTIPLEX_OUT2);
  float back_right_marker = analogRead(MULTIPLEX_OUT2);
  float corner_right_marker = analogRead(MULTIPLEX_OUT2);
  int error = 0;
  if(front_right_marker > TAPEFOLLOWTHRESH && back_right_marker > TAPEFOLLOWTHRESH && corner_right_marker > TAPEFOLLOWTHRESH){
    error |= ALL_ON;
  }

  return error;

}

