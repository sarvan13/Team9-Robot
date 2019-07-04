#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>

#define MULTIPLEX_OUT PA_0
#define A PB_3
#define B PB_4
#define C PB_5
// #define LEFT_REVERSE_PIN PA_6 //ORANGE WIRE
#define LEFT_FORWARD_PIN PA_7 //YELLOW WIRE
// #define RIGHT_FORWARD_PIN PB_1 // red
// #define RIGHT_REVERSE_PIN PB_0 //brown
#define TPWM 500
#define CLOCKF 100000

#define DIFTHRESH 100
#define REG_SPEED 150

#define KP 2
#define KD .5

float previousError = 0;
float error = 0.0;

int count = 0;

void setup()
{
  Serial.begin(115200);

  // initialize LED digital pin as an output.
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  // pinMode(LEFT_REVERSE_PIN, OUTPUT);
  // pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  // pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(MULTIPLEX_OUT, INPUT_ANALOG);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);

  //start going forwards
  // digitalWrite(LEFT_FORWARD_PIN, HIGH);
  // pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 1);
  // pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 1);
}

void loop()
{
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    float leftSensor = analogRead(MULTIPLEX_OUT);
    digitalWrite(B, HIGH);
    digitalWrite(A, HIGH);
    float rightSensor = analogRead(MULTIPLEX_OUT);
    float previousError = error;

    Serial.println("Left: "); Serial.println(leftSensor);
    Serial.println("Right: "); Serial.println(rightSensor);

    if (rightSensor < DIFTHRESH && leftSensor < DIFTHRESH) {
        if (previousError < 0){
            error = 2 * (rightSensor - DIFTHRESH);
        } else {
            error = 2 * (DIFTHRESH - leftSensor);
        }
    } else if (leftSensor < DIFTHRESH){
      error = DIFTHRESH - leftSensor;
    } else if (rightSensor < DIFTHRESH) {
      error = (rightSensor - DIFTHRESH);
    } else {
      error = 0;
    }

    // float p = KP * error;
    // float d = KD * (error - previousError);
    // // float d = 0;
    // float g = p + d;

    // if(error > 0){
    //   pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED + g, 0);
    //   pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 0);
    // }else if(error < 0){
    //   pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 0);
    //   pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED - g, 0);
    // }else {
    //   pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 0);
    //   pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 0);
    // }
    Serial.print("Error: ");
    Serial.println(error);
    delay(500);
 }
