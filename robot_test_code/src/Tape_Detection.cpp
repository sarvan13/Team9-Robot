#include <Tape_Detection.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "PinNames.h"

#define MULTIPLEX_OUT PA5
#define LEFT_BACKWARDS_SENSOR PA4
#define A PB14  // Left = 000 - Right = 
#define B PB13
#define C PB12

#define TAPEFOLLOWTHRESH 480
#define BACKWARDFOLLOWTHRESH 800
#define LEFT_THRESH 670
#define RIGHT_THRESH 670
#define MARKER_THRESH 890

#define HARDCODE_KP 120 //240
#define HARDCODE_KD 25//50
#define COUNTER_VAL 0

//1 0 1 main middle sensor
//0 1 0 corner left sensor
//1 1 1 main right sensor
//0 0 0 marker left sensor
//1 0 0 marker_right sensor
//0 0 1 corner right sensor
//1 1 0 backwards right sensor
//0 1 1 main left sensor
Tape_Detection::Tape_Detection(){
    Kp = HARDCODE_KP;
    Kd = HARDCODE_KD;
    pinMode(MULTIPLEX_OUT, INPUT_ANALOG);
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(LEFT_BACKWARDS_SENSOR, INPUT_ANALOG);
}

branch_state Tape_Detection::branch_exists(){
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  float cornerRightSensor = analogRead(MULTIPLEX_OUT);

  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
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
  marker_state marker_side = NO_MARKER;
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  float marker_left_sensor = analogRead(MULTIPLEX_OUT);
  Serial.print(marker_left_sensor); Serial.print(" ");


  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  float marker_right_sensor = analogRead(MULTIPLEX_OUT);
  Serial.print(marker_right_sensor); Serial.print(" ");
  Serial.println();

  if(marker_right_sensor > MARKER_THRESH ){
    marker_side = RIGHT_MARKER;
  }

  if(marker_left_sensor > MARKER_THRESH){
    marker_side = LEFT_MARKER;
  }

  this->marker_side = marker_side;
  return marker_side;
}

int Tape_Detection::get_pid(){
    path_error = get_path_error();
    float p =  Kp * path_error;
    float d =  Kd * (path_error - previous_path_error);
    previous_path_error = path_error;
    return p + d; // = g
}

int Tape_Detection::alternate_get_pid(){
    path_error = get_alternate_path_error();
    float p = Kp * path_error;
     float d =  Kd * (path_error - previous_path_error);
    previous_path_error = path_error;
    return p + d; // = g
}

int Tape_Detection::get_alternate_path_error(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  float backwards_left_sensor = analogRead(MULTIPLEX_OUT);
  Serial.print(backwards_left_sensor); Serial.print(" ");


  float backwards_right_sensor = analogRead(LEFT_BACKWARDS_SENSOR);
  Serial.print(backwards_right_sensor); Serial.print(" ");
  


  previous_path_error = path_error;
   if(backwards_right_sensor < BACKWARDFOLLOWTHRESH && backwards_left_sensor < BACKWARDFOLLOWTHRESH){
     if (previous_path_error < 0){
            path_error = -2;
        } else {
            path_error = 2;
        }
   } else if(backwards_right_sensor < BACKWARDFOLLOWTHRESH){
     path_error = -1;
   } else if(backwards_left_sensor < BACKWARDFOLLOWTHRESH){
     path_error = 1;
   } else {
      path_error = 0;
   }
  Serial.println(path_error); 
  return path_error;
}

void Tape_Detection::set_Kp(float Kp){
  this->Kp = Kp;
}

void Tape_Detection::set_Kd(float Kd){
  this->Kd = Kd;
}

int Tape_Detection::get_path_error(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  float mainLeftSensor = analogRead(MULTIPLEX_OUT);
  Serial.print(mainLeftSensor); Serial.print(" ");

  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  float mainMiddleSensor = analogRead(MULTIPLEX_OUT);
  Serial.print(mainMiddleSensor); Serial.print(" ");

  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
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




//0 0 1 right sensor
//0 1 1 bottom right sensor
//0 1 0 top right sensor 


