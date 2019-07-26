#include <Larry.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <FreeMono12pt7b.h>
#include <FreeMono9pt7b.h>
#include <stdint.h>
#include "PinNames.h"

#define REVERSE_MOTOR_PIN PA_1 //maybe (could be reverse or FORWARD)
#define FORWARD_MOTOR_PIN PA_0 //maybe

#define RACK_LIMIT_PIN PB4
#define CLAW_LIMIT_PIN PB13

// #define ENCODER_PIN PB12

// #define TICKS_PER_REV 24.0 
// #define DISTANCE_PER_REV 5.0 //mm (perhaps)

#define MAX_DISTANCE 100 //mm

#define REG_SPEED 500
#define TPWM 500
#define CLOCKF 100000

#define FORWARD 1
#define REVERSE -1

Larry::Larry()
{
    reg_speed = REG_SPEED;

    pinMode(REVERSE_MOTOR_PIN, OUTPUT);
    pinMode(FORWARD_MOTOR_PIN, OUTPUT);
    pinMode(RACK_LIMIT_PIN, INPUT);
    pinMode(CLAW_LIMIT_PIN, INPUT);
    // pinMode(ENCODER_PIN, INPUT);

    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 1);
    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 1);

    go_home_larry();

    current_position = 0;
}

void Larry::go_home_larry()
{

    state = FORWARD;
    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

    while(digitalRead(RACK_LIMIT_PIN) == LOW){
        
    }

    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

    current_position = 0;

    Serial.print(current_position);
}

larry_success Larry::go_far_larry()
{
    state = FORWARD;
    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

    while(!digitalRead(CLAW_LIMIT_PIN) && !digitalRead(RACK_LIMIT_PIN)){

    }

    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

    if (digitalRead(RACK_LIMIT_PIN) == HIGH){
        current_position = 0;
    }
    while(digitalRead(CLAW_LIMIT_PIN)){
        //do nothing
    }
}

void Larry::move_larry(double position){
    Serial.println("sup");
    if (position >= MAX_DISTANCE){
        Serial.print("What the fuck you tryna do");
    }
    else if(current_position < position){
        state = REVERSE;
        pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
        pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);

        while(current_position < position){
            Serial.println(current_position);
            Serial.println(position);
        }

        pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
        pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

        Serial.print("done");
        
    }

    else if (current_position > position){
        state = FORWARD;
        pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);
        pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

        while(current_position > position){

        }

        pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
        pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
        
    }
    Serial.println("sup");
}