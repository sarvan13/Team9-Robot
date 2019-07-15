#include <Movement.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <FreeMono12pt7b.h>
#include <FreeMono9pt7b.h>
#include <stdint.h>
#include "PinNames.h"

#define LEFT_REVERSE_PIN PA_6 //ORANGE WIRE
#define LEFT_FORWARD_PIN PA_7 //YELLOW WIRE
#define RIGHT_FORWARD_PIN PB_1 // red
#define RIGHT_REVERSE_PIN PB_0 //brown  

#define LEFT_WHEEL_INTERRUPT PB_4
#define RIGHT_WHEEL_INTERRUPT PB_5

#define REG_SPEED 100
#define TPWM 500
#define CLOCKF 100000

void handle_left_wheel_interrupt();
void handle_right_wheel_interrupt();

int left_i = 0;
int right_i = 0;

Movement::Movement()
{
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(LEFT_WHEEL_INTERRUPT, INPUT_PULLUP);
  pinMode(RIGHT_WHEEL_INTERRUPT, INPUT_PULLUP);

  attachInterrupt(LEFT_WHEEL_INTERRUPT, handle_left_wheel_interrupt, RISING);
  attachInterrupt(RIGHT_WHEEL_INTERRUPT, handle_right_wheel_interrupt, RISING);
}

void Movement::apply_pid(int pid){
    int left_motor_speed = REG_SPEED - pid;
    int right_motor_speed = REG_SPEED + pid;
    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 0);
}

void Movement::turn_right()
{
    int left_motor_speed = 90;
    int right_motor_speed = 110;
    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 0);
}

void Movement::turn_left()
{
    int left_motor_speed = 110;
    int right_motor_speed = 90;
    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 0);
}

void Movement::forward(){
    int left_motor_speed = REG_SPEED;
    int right_motor_speed = REG_SPEED;
    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 1);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 1);

}

void Movement::u_turn()
{

}

void Movement::reverse()
{

}

void Movement::grab_plushie_front(){

}

void Movement::grab_plushie_left(){

}

void Movement::grab_plushie_right(){
    
}

void handle_left_wheel_interrupt(){
    left_i++;
}

void handle_right_wheel_interrupt(){
    right_i++;
}

