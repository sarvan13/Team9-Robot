#include <Susan.h>
#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <FreeMono12pt7b.h>
#include <FreeMono9pt7b.h>
#include <stdint.h>
#include "PinNames.h"
#include <A4988.h>

// using a 200-step motor (most common)
#define MOTOR_STEPS 200
// configure the pins connected
#define DIR PB14
#define STEP PB15

#define LIMIT_PIN PA15

#define RPM 1
#define MICROSTEPPING 1

#define TRIGGER_PIN PB11
#define ECHO_PIN PB10

#define GEAR_RATIO 124/36

#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0

#define STEPS_PER_REV MOTOR_STEPS*GEAR_RATIO


Susan::Susan(){
    //Set Default to turn counterclockwise
    pinMode(DIR, OUTPUT);
    pinMode(STEP, OUTPUT);
    pinMode(LIMIT_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT); // Sets the TRIGGER_PIN as an Output
    pinMode(ECHO_PIN, INPUT); // Sets the ECHO_PIN as an Input

    digitalWrite(DIR, LOW);
    digitalWrite(STEP, LOW);

    //Set reference point
    current_position = 0;

    sweep_angle = 60; //Default number of steps used for the first post
}

void Susan::go_home_susan(){
    if(current_position >= 0) {
        set_dir(COUNTERCLOCKWISE);
    } else {
        set_dir(CLOCKWISE);
    }
    int count = 0;
    while(!digitalRead(LIMIT_PIN)){
        send_step(); //rotate the stepper by one tick until we reach home
        count++;
        if(count == 250) {
            if(digitalRead(DIR) == CLOCKWISE) {
                set_dir(COUNTERCLOCKWISE);
            } else {
                set_dir(CLOCKWISE);
            }
        }
    }
    current_position = 0;
}

void Susan::go_home_susan_CW(){
    if(current_position >= 0) {
        set_dir(CLOCKWISE);
    } else {
        set_dir(COUNTERCLOCKWISE);
    }
    int count = 0;
    while(!digitalRead(LIMIT_PIN)){
        send_step(); //rotate the stepper by one tick until we reach home
        count++;
        if(count == 250) {
            if(digitalRead(DIR) == CLOCKWISE) {
                set_dir(COUNTERCLOCKWISE);
            } else {
                set_dir(CLOCKWISE);
            }
        }
    }
    current_position = 0;
}

/* Paramters: absolute value in degrees that we want to turn to relative to
/* home position. Between -344 and 344 steps
 */ //gear ratio 124:36
void Susan::turn_susan(int steps){

    steps = constrain(steps, -344, 344);
    int distance = steps - current_position;
    if (distance < 0) {
        digitalWrite(DIR, LOW);
    } else {
        digitalWrite(DIR, HIGH);
    }

    for (int i = 0; i < abs(distance); i++) {
        digitalWrite(STEP, HIGH);
        delay(3);
        digitalWrite(STEP, LOW);
        delay(3);
    }

    current_position = steps;
}

void Susan::send_step(){
    digitalWrite(STEP, HIGH);
    delay(5);
    digitalWrite(STEP, LOW);
    delay(5);
    current_position += digitalRead(DIR) ? 1 : -1;
}

void Susan::set_dir(int dir){
    if(dir){
        digitalWrite(DIR, CLOCKWISE);
    } else{
        digitalWrite(DIR, COUNTERCLOCKWISE);
    }
}

float Susan::point_to_min_distance(){
    int steps_from_start = 0;
    int best_num_steps_from_start = 0;
    float distance = get_sonar_distance();
    float min_distance = distance;
    int clock_flag = -1; //To know which direction to turn 
    int final_position;
    set_dir(COUNTERCLOCKWISE);
    //Sweep from center in counterclockwise direction
    while (steps_from_start < sweep_angle){
        send_step();
        steps_from_start += 1;
        distance = get_sonar_distance();
        if (distance < min_distance){
            min_distance = distance;
            best_num_steps_from_start = steps_from_start;
        }
    }

    //Sweep from most clockwise point to center
    set_dir(CLOCKWISE);
    delay(500);
    for(int i = 0; i < 2 * sweep_angle; i++){
        send_step();
    }
    delay(500);
    set_dir(COUNTERCLOCKWISE);
    while (steps_from_start > 0){
        send_step();
        steps_from_start -= 1;
        distance = get_sonar_distance();
        if (distance < min_distance){
            min_distance = distance;
            best_num_steps_from_start = steps_from_start;
            clock_flag = 1;
        }
    }

    //Rotate to final position
    //Check where min is relative to the start position (current position)
    delay(500);
    if (clock_flag == -1){
        final_position = current_position - best_num_steps_from_start;
        
        turn_susan(final_position);
    }
    else{
        final_position = current_position + best_num_steps_from_start;

        turn_susan(final_position);
    }  

    return min_distance; 
}

float Susan::get_sonar_distance(){
    long duration;
    float distance;
    // Clears the TRIGGER_PIN
    delayMicroseconds(2);
    // Sets the TRIGGER_PIN on HIGH state for 10 micro seconds
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
    duration = pulseIn(ECHO_PIN, HIGH, 10000);    // Calculating the distance
    distance= duration*0.034/2;
    if(distance <= 0) {
        distance = 1000;
    }
    
    return distance;
}

void Susan::set_sweep_angle(int steps){
    sweep_angle = steps;
}
