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
#define DIR PB15
#define STEP PB14
#define LIMIT_PIN PB4

#define RPM 1
#define MICROSTEPPING 1

#define TRIGGER_PIN PB11
#define ECHO_PIN PB10

#define SWEEP_STEPS 60
#define GEAR_RATIO 124/36

#define CLOCKWISE 1
#define COUNTERCLOCKWISE 0

#define STEPS_PER_REV MOTOR_STEPS*GEAR_RATIO

A4988 stepper(MOTOR_STEPS, DIR, STEP);

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
    //go_home_susan();
    current_position = 0;
}

void Susan::go_home_susan(){
    while(digitalRead(LIMIT_PIN) == LOW){
        // stepper.move(1); //rotate the stepper by one tick until we reach home
    }
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
        delay(10);
        digitalWrite(STEP, LOW);
        delay(10);
    }

    current_position = steps;
}

void Susan::send_step(){
    digitalWrite(STEP, HIGH);
    delay(10);
    digitalWrite(STEP, LOW);
    delay(10);
    current_position += digitalRead(DIR) ? 1 : -1;
}

void Susan::set_dir(int dir){
    if(dir){
        digitalWrite(DIR, CLOCKWISE);
    } else{
        digitalWrite(DIR, COUNTERCLOCKWISE);
    }
}

void Susan::point_to_min_distance(){
    int steps_from_start = 0;
    int best_num_steps_from_start = 0;
    float distance = get_sonar_distance();
    float min_distance = distance;
    int clock_flag = -1; //To know which direction to turn 
    int final_position;
    set_dir(COUNTERCLOCKWISE);
    //Sweep from center in counterclockwise direction
    while (steps_from_start < SWEEP_STEPS){
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
    for(int i = 0; i < 2 * SWEEP_STEPS; i++){
        send_step();
    }
    
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
    if (clock_flag == -1){
        final_position = current_position - best_num_steps_from_start;
        
        turn_susan(final_position);
    }
    else{
        final_position = current_position + best_num_steps_from_start;

        turn_susan(final_position);
    }  
}

float Susan::get_sonar_distance(){
    long duration;
    float distance;
    // Clears the TRIGGER_PIN
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    // Sets the TRIGGER_PIN on HIGH state for 10 micro seconds
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
    duration = pulseIn(ECHO_PIN, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    Serial.println(distance);
    return distance;
}
