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
#define HIGH_QRD_THRESHOLD 800
#define LOW_QRD_THRESHOLD 100

//#define DISTANCE_PER_REV 3 //mm (currently a fat guess)

#define REG_SPEED 400
#define TPWM 500
#define CLOCKF 100000

Leviosa::Leviosa()
{
    reg_speed = REG_SPEED;
    Serial.begin(115200);
    //initialize pins
    pinMode(REVERSE_MOTOR_PIN, OUTPUT);
    pinMode(FORWARD_MOTOR_PIN, OUTPUT);
    pinMode(LIMIT_PIN, INPUT);
    pinMode(QRD_PIN, INPUT);

    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 1);
    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 1);

    // go_home_hermione();
    current_position = 900;

    //Set base state for QRD encoder
    if(analogRead(QRD_PIN) > HIGH_QRD_THRESHOLD){
       current_state = BLACKY;
    }
    else{
        current_state=WHITEY;
    }
}
/*Prints the QRD value, for testing the qrd by hand
 */
void Leviosa::read_leviosa(){
    Serial.println(analogRead(QRD_PIN));
}

/* Turns the lead screw until the limit switch is touched by the arm
 */
void Leviosa::go_home_hermione()
{
    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

    while(digitalRead(LIMIT_PIN) == LOW){
        
    }

    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
}

/* Moves the arm vertically by a specified number of revolutions 
   (position muct be given in number of revolutions)
 */
void Leviosa::wingardium_leviosa(int position)
{
    int counter;
   
    if(analogRead(QRD_PIN) > HIGH_QRD_THRESHOLD){
         current_state = BLACKY;
    }else if(analogRead(QRD_PIN) < LOW_QRD_THRESHOLD){
         current_state = WHITEY;
    }

    //Move arm up
    if(current_position < position)
    {
        //Turn on motor so that arm moves up
        pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
        pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);
        while(current_position < position){
            counter = 0;
            while(counter != 2){
                if(check_leviosa(current_state)){
                    counter++;
                }
            }
            current_position += 1;
           
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
            counter = 0;
            while(counter != 2){
                if(check_leviosa(current_state)){
                    counter++;
                }
            }
             current_position -= 1;
        
        }
        //Turn off motors once we reach desired position
        pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
        pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
    }
    
}


/* Compares the current QRD reading to the previous reading and returns 
/* 1 if they are different and 0 if the states are the same.
 */
int Leviosa::check_leviosa(qrd_state current_state){
    qrd_state state;
    if(analogRead(QRD_PIN) > HIGH_QRD_THRESHOLD){
        state = BLACKY;
    }else if(analogRead(QRD_PIN) < LOW_QRD_THRESHOLD){
        state = WHITEY;
    }
    if(state != current_state){
        this->current_state = state;
        return 1;
    }else{
        return 0;
    }
}