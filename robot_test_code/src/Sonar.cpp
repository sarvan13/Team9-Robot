#include <Sonar.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "PinNames.h"

#define RIGHT_TRIG_PIN PB_12
#define RIGHT_ECHO_PIN PB_11
#define LEFT_TRIG_PIN PB_10
#define LEFT_ECHO_PIN PB_9
#define FRONT_TRIG_PIN_LOW PB_8
#define FRONT_ECHO_PIN_LOW PA_8
#define FRONT_TRIG_PIN_HIGH PB_14
#define FRONT_ECHO_PIN_HIGH PB_15

#define DISTANCETHRESH 100

Sonar::Sonar(){
  pinMode(RIGHT_TRIG_PIN, OUTPUT);
  pinMode(RIGHT_ECHO_PIN, INPUT);
  pinMode(LEFT_TRIG_PIN, OUTPUT);
  pinMode(LEFT_ECHO_PIN, INPUT);
  pinMode(FRONT_TRIG_PIN_LOW, OUTPUT);
  pinMode(FRONT_ECHO_PIN_LOW, INPUT);
  pinMode(FRONT_TRIG_PIN_HIGH, OUTPUT);
  pinMode(FRONT_ECHO_PIN_HIGH, INPUT);
}
sonar_state Sonar::check_sonar(){
    //plushies are priority, then collision
  sonar_state front = front_sonar();
  sonar_state left = side_sonar(LEFT_TRIG_PIN, LEFT_ECHO_PIN, LEFT);
  sonar_state right = side_sonar(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN, RIGHT);
  if(front == PLUSHIE_FRONT){
    sonar_value = PLUSHIE_FRONT;
    return front;
  }else if(left == PLUSHIE_LEFT){
    sonar_value = PLUSHIE_LEFT;
    return left;
  }else if(right == PLUSHIE_RIGHT){
    sonar_value = PLUSHIE_RIGHT;
    return right;
  }

  if(front == COLLISION_FRONT){
    sonar_value = COLLISION_FRONT;
    return front;
  }else if(left == COLLISION_SIDE || right == COLLISION_SIDE){
    sonar_value = COLLISION_SIDE;
    return COLLISION_SIDE;
  }

  sonar_value = NO_DETECTION;
  return NO_DETECTION;
}

sonar_state Sonar::front_sonar(){
  float low_distance = pulse(FRONT_TRIG_PIN_LOW, FRONT_ECHO_PIN_LOW);

  if(low_distance < 30){
    float high_distance = pulse(FRONT_TRIG_PIN_HIGH, FRONT_ECHO_PIN_HIGH);
    if(high_distance < 30){
        return COLLISION_FRONT;
      //senses robot, go backwards
    }else{
        return PLUSHIE_FRONT;
      //senses plushies, encoders
    }
  }
  return NO_DETECTION;
}

sonar_state Sonar::side_sonar(PinName trigpin, PinName echopin, side side){

  float distance = pulse(trigpin, echopin);

  if(distance < 30) {
    float new_distance = pulse(trigpin, echopin);
    if(distance - new_distance > DISTANCETHRESH){//if difference in distance changes above the distance threshold, sense a robot
      //senses robot, keep going straight
      return COLLISION_SIDE;
    }else{
      if(side == LEFT){
          //left side senses plushies, encoders
          return PLUSHIE_LEFT;
      }else if(side == RIGHT){
          // right side senses plushies, encoders
          return PLUSHIE_RIGHT;
      }
    }
  }
  return NO_DETECTION;
}


float Sonar::pulse(PinName trigpin, PinName echopin){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  // Sets the TRIG_PIN on HIGH state for 10 micro seconds
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
  long duration = pulseIn(echopin, HIGH);
  // Calculating the distance
  float distance= duration*0.034/2;
  return distance;
}