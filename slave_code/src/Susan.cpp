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
#define DIR PB3
#define STEP PB14
#define LIMIT_PIN PB4

#define RPM 1
#define MICROSTEPPING 1

#define TRIGGER_PIN PB11
#define ECHO_PIN PB10

#define SWEEP_ANGLE 30

A4988 stepper(MOTOR_STEPS, DIR, STEP);

Susan::Susan(){
    //Set Default to turn counterclockwise
    digitalWrite(DIR, HIGH);
    //Initialize stepper motor
    stepper.begin(RPM, MICROSTEPPING);

    pinMode(LIMIT_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT); // Sets the TRIGGER_PIN as an Output
    pinMode(ECHO_PIN, INPUT); // Sets the ECHO_PIN as an Input

    //Set reference point
    go_home_susan();
    current_position = 0;
}

void Susan::go_home_susan(){
    while(digitalRead(LIMIT_PIN) == LOW){
        stepper.rotate(0.5); //rotate the stepper by half a degree until we reach home
    }
}

/* Paramters: absolute value in degrees that we want to turn to relative to
/* home position. Between 0 and 360 degrees
 */
void Susan::turn_susan(double degrees){
    //Calculate angle needed to rotate in either direction from current postition
    double to_rotate_pos = abs(degrees - current_position);
    double to_rotate_neg = abs(current_position + 360 - degrees);

    if (to_rotate_neg > to_rotate_pos){
        //Turn stepper oppposite direction
        digitalWrite(DIR, LOW);
        //Rotate by necessary amount
        stepper.rotate(to_rotate_neg);
        //Set back to default
        digitalWrite(DIR, HIGH);
    }
    else{
        stepper.rotate(to_rotate_pos);
    }

    current_position = degrees;

}

void Susan::point_to_min_distance(){
    int degrees_from_start = 0;
    int best_angle_from_start = 0;
    float distance = 10000; //arbitrarily high number should be distance from start
    float min_distance = distance;
    int clock_flag = -1; //To know which direction to turn 
    int final_position;

    //Sweep from center in counterclockwise direction
    while (degrees_from_start < SWEEP_ANGLE){
        stepper.rotate(1);
        degrees_from_start += 1;
        distance = get_sonar_distance();
        if (distance < min_distance){
            min_distance = distance;
            best_angle_from_start = degrees_from_start;
        }
    }

    //Sweep from most clockwise point to center
    //Turn to most clockwise position
    digitalWrite(DIR, LOW);
    stepper.rotate(2*SWEEP_ANGLE);
    //Start turning back to center
    digitalWrite(DIR, HIGH);
    
    while (degrees_from_start > 0){
        stepper.rotate(1);
        degrees_from_start -= 1;
        distance = get_sonar_distance();
        if (distance < min_distance){
            min_distance = distance;
            best_angle_from_start = degrees_from_start;
            clock_flag = 1;
        }
    }

    //Rotate to final position
    //Check where min is relative to the start position (current position)
    if (clock_flag == 1){
        final_position = current_position - best_angle_from_start;

        //Absolute angles must be between 0 and 360 degrees
        if (final_position < 0){
            final_position += 360; 
        }

        turn_susan(final_position);
    }
    else{
        final_position = current_position + best_angle_from_start;

        //Absolute angles must be between 0 and 360 degrees
        if (final_position > 360){
            final_position -= 360;
        }

        turn_susan(final_position);
    }  
}

float get_sonar_distance(){
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

    return distance;
}
