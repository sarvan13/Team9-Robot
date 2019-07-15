#include <Tape_Detection.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "PinNames.h"

#define MULTIPLEX_OUT PA_0
#define A PB3
#define B PB13
#define C PB4
#define DIFTHRESH 250



Tape_Detection::Tape_Detection(){
    pinMode(MULTIPLEX_OUT, INPUT_ANALOG);
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
}

branch_state Tape_Detection::branch_exists(){
  float cornerLeftSensor = analogRead(MULTIPLEX_OUT);
  float cornerRightSensor = analogRead(MULTIPLEX_OUT);

  if(cornerLeftSensor > DIFTHRESH){
    return LEFT_BRANCH;
  }else if(cornerRightSensor > DIFTHRESH){
    return RIGHT_BRANCH;
  }else{
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

  if(sideLeftSensor1 > DIFTHRESH || sideLeftSensor2 > DIFTHRESH || sideLeftSensor3 > DIFTHRESH){
    return LEFT_MARKER;
  }else if(sideRightSensor1 > DIFTHRESH || sideRightSensor2 > DIFTHRESH || sideRightSensor3 > DIFTHRESH){
    return RIGHT_MARKER;
  }else{
    return NO_MARKER;
  }

}

int Tape_Detection::get_pid(){
    pid.read_K_values();
    get_path_error();
    float p =  pid.get_Kp() * error;
    float d =  pid.get_Kd() * (error - previous_error);
    float PID_value = (p + d) / 15.0;
    return PID_value;
}

int Tape_Detection::get_path_error(){
  float mainLeftSensor = analogRead(MULTIPLEX_OUT);
  float mainRightSensor = analogRead(MULTIPLEX_OUT);
  float mainMiddleSensor = analogRead(MULTIPLEX_OUT);
  previous_error = error;
   if (mainRightSensor < DIFTHRESH && mainLeftSensor < DIFTHRESH && mainMiddleSensor < DIFTHRESH) {
        if (previous_error < 0){
            error = -5;
        } else {
            error = 5;
        }
  } else if (mainLeftSensor < DIFTHRESH && mainMiddleSensor < DIFTHRESH){
      error = -3;
  } else if (mainLeftSensor < DIFTHRESH) {
      error = -1;
  } else if (mainRightSensor< DIFTHRESH && mainMiddleSensor < DIFTHRESH) {
      error = 3;
  } else if (mainRightSensor< DIFTHRESH) {
      error = 1;
  } else {
      error = 0;
  }
  return error;
}

int Tape_Detection::get_marker_error(){

}

