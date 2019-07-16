// #include <Arduino.h>
// #include <Wire.h>
// #include <time.h>
// #include <math.h>

// #define LEFT_SENSOR PA3
// #define RIGHT_SENSOR PA2
// #define RIGHT_REVERSE_PIN PA_7
// #define RIGHT_FORWARD_PIN PA_6
// #define LEFT_REVERSE_PIN PB_1 
// #define LEFT_FORWARD_PIN PB_0
// #define TPWM 500
// #define CLOCKF 100000
// #define DIFTHRESH 100

// float previousLeft = 0.0;
// float previousRight = 0.0;
// int count = 0;

// void setup()
// {
//   Serial.begin(115150);

//   // initialize LED digital pin as an output.
//   pinMode(LEFT_FORWARD_PIN, OUTPUT);
//   pinMode(LEFT_REVERSE_PIN, OUTPUT);
//   pinMode(RIGHT_FORWARD_PIN, OUTPUT);
//   pinMode(RIGHT_REVERSE_PIN, OUTPUT);
//   pinMode(LEFT_SENSOR, INPUT_ANALOG);
//   pinMode(RIGHT_SENSOR, INPUT_ANALOG);
//   //start going forwards
//   // digitalWrite(LEFT_FORWARD_PIN, HIGH);
//   pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 70, 1);
//   pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 70, 1);
// }

// int lastOn = 0;
// void loop()
// {
//     if(count == 1500) {
//       pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 0, 1);
//       pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 0, 1);
//     }

//     int leftSensor = analogRead(LEFT_SENSOR);
    
//     int rightSensor = analogRead(RIGHT_SENSOR);


//     Serial.println("Left: "); Serial.println(leftSensor);
//     Serial.println("Right: "); Serial.println(rightSensor);


//     if(leftSensor < DIFTHRESH && rightSensor < DIFTHRESH) {
//       if(lastOn == 1) {
//         pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 150, 1);
//         pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 100, 1);
//       } else {
//         pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 150,1);
//         pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 100, 1);
//       }
//     }
//     else if (leftSensor < DIFTHRESH) {
//       pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 150,1);
//       pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 100, 1);
//     } else if(rightSensor < DIFTHRESH) {
//         // somehow adjust the speed of both motors to turn a little bit to the needed side
//       pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 150, 1);
//       pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 100, 1);
//     }  else {
//       pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, 150, 1);
//       pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, 100, 1);
//     }
//     previousLeft = leftSensor;
//     previousRight = rightSensor;
    
//     if(leftSensor > DIFTHRESH && rightSensor < DIFTHRESH) {
//       lastOn = 1;
//     } else if (rightSensor > DIFTHRESH && leftSensor < DIFTHRESH) {
//       lastOn = 0;
//     }

//     count++;
// }
