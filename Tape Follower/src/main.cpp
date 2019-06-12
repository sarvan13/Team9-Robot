#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>

#define LEFT_SENSOR PB_0
#define RIGHT_SENSOR PB_1
#define LEFT_FORWARD_PIN PA_6
#define LEFT_REVERSE_PIN PA_7
#define RIGHT_FORWARD_PIN PA_4 
#define RIGHT_REVERSE_PIN PA_5
#define TPWM 500
#define CLOCKF 100000
#define DIFTHRESH 5

float previousLeft = 0.0;
float previousRight = 0.0;
int count = 0;

void setup()
{
  Serial.begin(115200);

  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEFT_SENSOR, INPUT_ANALOG);
  pinMode(RIGHT_SENSOR, INPUT_ANALOG);
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT);

  //start going forwards
  // pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 200, 1);
  // pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 200, 1);
}


void loop()
{
    // if(count == 5) {
    //   pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 0, 1);
    //   pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 0, 1);
    // }

    float leftSensor = analogRead(LEFT_SENSOR);
    float rightSensor = analogRead(RIGHT_SENSOR);


    Serial.println("Left: "); Serial.println(leftSensor);
    Serial.println("Right: "); Serial.println(rightSensor);

    if (abs(leftSensor - previousLeft) > DIFTHRESH || abs(rightSensor - previousRight) > DIFTHRESH) {
        // somehow adjust the speed of both motors to turn a little bit to the needed side
        
        previousLeft = leftSensor;
        previousRight = rightSensor;
    } 
    delay(1000);

    count++;
}