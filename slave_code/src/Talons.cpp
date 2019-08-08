#include <Talons.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "PinNames.h"

//These two control PWM duty cycle to servo - not actual angle.
#define CLOSED_ANGLE 100
#define OPEN_ANGLE 270 //about 200 degree angle
#define FINAL_ANGLE 160

#define SERVO_PIN PB_1
#define TPWM 500
#define CLOCKF 100000
#define CLAW_LIMIT_PIN PB13

Talons::Talons(){
    angle = OPEN_ANGLE;
    pwm_start(SERVO_PIN, CLOCKF, TPWM, OPEN_ANGLE, 1);
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

void Talons::final_open_claw(){
  pwm_start(SERVO_PIN, CLOCKF, TPWM, FINAL_ANGLE, 0);
}
