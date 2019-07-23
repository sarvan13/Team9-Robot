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

#define REVERSE_MOTOR_PIN PA_1 //maybe (could be reverse or forward)
#define FORWARD_MOTOR_PIN PA_0 //maybe

#define RACK_LIMIT_PIN PB_5
#define CLAW_LIMIT_PIN PB_13

#define ENCODER_PIN PB_12

#define TICKS_PER_REV 30 //(perhaps)
#define DISTANCE_PER_REV 5 //mm (perhaps)

#define MAX_DISTANCE 22 //mm

#define REG_SPEED 500
#define TPWM 500
#define CLOCKF 100000

Larry::Larry
{
    reg_speed = REG_SPEED;

    pinMode(REVERSE_MOTOR_PIN, OUTPUT);
    pinMode(FORWARD_MOTOR_PIN, OUTPUT);
    pinMode(RACK_LIMIT_PIN, INPUT);
    pinMode(CLAW_LIMIT_PIN, INPUT);
    pinMode(ENCODER_PIN, INPUT);

    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 1);
    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 1);

    go_home_larry();

    current_position = 0;
}

Larry::go_home_larry()
{
    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);

    while(digitalRead(RACK_LIMIT_PIN) == LOW){

    }

    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
}

Larry::go_far_larry()
{
    pwm_start(REVERSE_MOTOR_PIN, CLOCKF, TPWM, 0, 0);
    pwm_start(FORWARD_MOTOR_PIN, CLOCKF, TPWM, reg_speed, 0);

    while(digitalRead(CLAW_LIMIT_PIN)) == LOW && current_position < MAX_DISTANCE){
        current_position = digitalRead()
    }
}