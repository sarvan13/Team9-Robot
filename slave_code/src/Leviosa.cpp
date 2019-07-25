#include <Leviosa.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <FreeMono12pt7b.h>
#include <FreeMono9pt7b.h>
#include <stdint.h>
#include "PinNames.h"

#define REVERSE_MOTOR_PIN PA_3 //maybe (could be reverse or forward)
#define FORWARD_MOTOR_PIN PA_2 //maybe

#define LIMIT_PIN PA15

#define QRD_PIN PA5
#define QRD_THRESHOLD 300

#define DISTANCE_PER_REV 3 //mm (currently a fat guess)

#define REG_SPEED 500
#define TPWM 500
#define CLOCKF 100000

Leviosa::Leviosa()
{
    reg_speed = REG_SPEED;

    //initialize pins
    pinMode(REVERSE_MOTOR_PIN, OUTPUT);
    pinMode(FORWARD_MOTOR_PIN, OUTPUT);
    pinMode(LIMIT_PIN, INPUT);
    pinMode(QRD_PIN, INPUT);

    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 1);
    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 1);

    go_home_hermione();
    current_position = 0;

    //Set base state for QRD encoder
    if(analogRead(QRD_PIN) > QRD_THRESHOLD){
        base_state = BLACKY;
    }
    else{
        base_state=WHITEY;
    }
}

void Leviosa::go_home_hermione()
{
    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

    while(digitalRead(LIMIT_PIN) == LOW){

    }

    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
}

//Moves arm to a position above the base position
void Leviosa::wingardium_leviosa(int position)
{
    enum qrd_state middle_state;
    enum qrd_state current_state;

    //Move arm up
    if(current_position < position)
    {
        //Turn on motor so that arm moves up
        pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
        pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);

        while(current_position < position){
            if(analogRead(QRD_PIN) > QRD_THRESHOLD){
                middle_state = BLACKY;
            }
            else{
                middle_state = WHITEY;
            }

            delay(3); //delay short amount of time to get rid of noise lol

            //Read sensor again after some time to compare to previous value
            if(analogRead(QRD_PIN) > QRD_THRESHOLD){
                current_state = BLACKY;
            }
            else{
                current_state = WHITEY;
            }

            //Check if we have gone a full revolution
            if(middle_state != base_state && current_state == base_state){
                current_position += DISTANCE_PER_REV;
            }
        }
        //Turn off motors once we reach desired position
        pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
        pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

    }

    //Move arm down
    else if(current_position > position)
    {
        //Turn on motor so that arm moves down
        pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);
        pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

        while(current_position > position){
            if(analogRead(QRD_PIN) > QRD_THRESHOLD){
                middle_state = BLACKY;
            }
            else{
                middle_state = WHITEY;
            }

            delay(3); //delay short amount of time to get rid of noise lol

            //Read sensor again after some time to compare to previous value
            if(analogRead(QRD_PIN) > QRD_THRESHOLD){
                current_state = BLACKY;
            }
            else{
                current_state = WHITEY;
            }

            //Check if we have gone a full revolution
            if(middle_state != base_state && current_state == base_state){
                //Decrement current position
                current_position -= DISTANCE_PER_REV;
            }
        }
        //Turn off motors once we reach desired position
        pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
        pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
    }
}