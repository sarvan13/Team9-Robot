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

// #define C PB_4
#define LEFT_REVERSE_PIN PB_1 //ORANGE WIRE
#define LEFT_FORWARD_PIN PB_0 //YELLOW WIRE
#define RIGHT_REVERSE_PIN PA_6 // red, 
#define RIGHT_FORWARD_PIN PA_7 //brown
#define GROUND PB10

// #define LEFT_WHEEL_INTERRUPT PB_4
// #define RIGHT_WHEEL_INTERRUPT PB_5

#define REG_SPEED 500
#define TPWM 500
#define CLOCKF 100000

int left_i = 0;
int right_i = 0;

Movement::Movement()
{
  reg_speed = REG_SPEED;
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(GROUND, OUTPUT);

  digitalWrite(GROUND, LOW);

  pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 0, 1);
  pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 0, 1);
  pwm_start(LEFT_REVERSE_PIN, CLOCKF, TPWM, 0, 1);
  pwm_start(RIGHT_REVERSE_PIN, CLOCKF, TPWM, 0, 1);
}

void Movement::apply_pid(int pid){
    int left_motor_speed = reg_speed - pid;
    int right_motor_speed = reg_speed + pid;
    // Serial.print(left_motor_speed);
    // Serial.print(" ");
    // Serial.print(right_motor_speed);
    // Serial.print(" ");
    left_motor_speed = constrain(left_motor_speed, 0, TPWM);
    right_motor_speed = constrain(right_motor_speed, 0, TPWM);

    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 0);
    pwm_start(LEFT_REVERSE_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(RIGHT_REVERSE_PIN, CLOCKF, TPWM, 0, 0);
 

    
    // Serial.print(left_motor_speed);
    // Serial.print(" ");
    // Serial.print(right_motor_speed);
    // Serial.println(" ");

   
}

void Movement::alternate_pid(int pid){
    int left_motor_speed = reg_speed - pid;
    int right_motor_speed = reg_speed + pid;
    // Serial.print(left_motor_speed);
    // Serial.print(" ");
    // Serial.print(right_motor_speed);
    // Serial.print(" ");
    left_motor_speed = constrain(left_motor_speed, 0, TPWM);
    right_motor_speed = constrain(right_motor_speed, 0, TPWM);

    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(LEFT_REVERSE_PIN, CLOCKF, TPWM, left_motor_speed, 0);
    pwm_start(RIGHT_REVERSE_PIN, CLOCKF, TPWM, right_motor_speed, 0);
}

void Movement::turn_right()
{
    int left_motor_speed = 500;
    int right_motor_speed = 100;
    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 0);
    pwm_start(RIGHT_REVERSE_PIN, CLOCKF, TPWM, right_motor_speed, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 0, 0);

}

void Movement::turn_left()
{
    int left_motor_speed = 100;
    int right_motor_speed = 500;
    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 0,0);
    pwm_start(LEFT_REVERSE_PIN, CLOCKF, TPWM, left_motor_speed, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 0);
}

void Movement::forward(){
    int left_motor_speed = reg_speed;
    int right_motor_speed = reg_speed;
    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 0);
    pwm_start(LEFT_REVERSE_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(RIGHT_REVERSE_PIN, CLOCKF, TPWM, 0, 0);

}

void Movement::reverse(int left_speed, int right_speed)
{
    int left_motor_speed = left_speed;
    int right_motor_speed = right_speed;
    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(LEFT_REVERSE_PIN, CLOCKF, TPWM, left_motor_speed, 0);
    pwm_start(RIGHT_REVERSE_PIN, CLOCKF, TPWM, right_motor_speed, 0);
}

void Movement::grab_plushie_front(){

}

void Movement::grab_plushie_left(){

}

void Movement::grab_plushie_right(){
    
}

void Movement::stop(){
    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(LEFT_REVERSE_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(RIGHT_REVERSE_PIN, CLOCKF, TPWM, 0, 0);
}

void Movement::set_speed(int speed){
    reg_speed = speed;

}



void Movement::rotate_left(int speed){

    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, speed, 0);
    pwm_start(LEFT_REVERSE_PIN, CLOCKF, TPWM, speed, 0);
    pwm_start(RIGHT_REVERSE_PIN, CLOCKF, TPWM, 0, 0);


}

void Movement::rotate_right(int speed){
     pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, speed, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(LEFT_REVERSE_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(RIGHT_REVERSE_PIN, CLOCKF, TPWM, speed, 0);
}

void handle_left_wheel_interrupt(){
    left_i++;
}

void handle_right_wheel_interrupt(){
    right_i++;
}

