#include <Talons.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "PinNames.h"

//These two control PWM duty cycle to servo - not actual angle.
#define CLOSED_ANGLE 30
#define OPEN_ANGLE 120 //about 200 degree angle
#define HUG_ANGLE 45

#define SERVO_PIN PB_1
#define TPWM 500
#define CLOCKF 100000
#define CLAW_LIMIT_PIN PB13

Talons::Talons(){
    pwm_start(SERVO_PIN, CLOCKF, TPWM, OPEN_ANGLE, 1);
    angle = OPEN_ANGLE;
}

int Talons::get_current_angle(){
    return angle;
}

void Talons::set_current_angle(int newAngle){
    angle = newAngle;
}

void Talons::close_claw(){
  pwm_start(SERVO_PIN, CLOCKF, TPWM, CLOSED_ANGLE, 0);
  set_current_angle(CLOSED_ANGLE);
}

void Talons::open_claw(){
  pwm_start(SERVO_PIN, CLOCKF, TPWM, OPEN_ANGLE, 0);
}

void Talons::hug_pole(){
  pwm_start(SERVO_PIN, CLOCKF, TPWM, HUG_ANGLE, 0);
}