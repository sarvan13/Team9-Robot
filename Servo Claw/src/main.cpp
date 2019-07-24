#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "PinNames.h"


#define CNTRL_PIN PA_1
#define FORWARD_PIN PA_7
#define REVERSE_PIN PA_6
#define TPWM 500
#define CLOCKF 100000
#define DIFTHRESH 5
#define CLAW_LIM_SWITCH PB13
#define RACK_LIM_SWITCH PB4
#define ROT_ENCODER PB12

#define SERVO_PIN PB_1
 

 
int servoAngle = 0;   // servo position in degrees

float previousControl = 0.0;
 
void setup()
{
  Serial.begin(115200);  
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(CLAW_LIM_SWITCH, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(CNTRL_PIN, INPUT_ANALOG);
  pinMode(FORWARD_PIN, OUTPUT);
  pinMode(REVERSE_PIN, OUTPUT);
  pinMode(ROT_ENCODER, INPUT);
  pwm_start(SERVO_PIN, CLOCKF, TPWM, 120, 1); 
}
 
 int loops = 0;
 int encoderVal = 0;
 int prevEncoderVal = 0;
 int reLo = 0;
void loop()
{
//control the servo's direction and the position of the motor
  //  Serial.print("CLAW: ");Serial.println(digitalRead(CLAW_LIM_SWITCH));
  //  Serial.print("RACK: ");Serial.println(digitalRead(RACK_LIM_SWITCH));
  //  pwm_start(SERVO_PIN, CLOCKF, TPWM, 30, 0);      // Turn SG90 servo Left to 45 degrees
  //  delay(2000);          // Wait 1 second
  //  pwm_start(SERVO_PIN, CLOCKF, TPWM, 120, 0);      // Turn SG90 servo back to 90 degrees (center position)
  //  delay(1000);  
  if(digitalRead(RACK_LIM_SWITCH) == 1 || digitalRead(CLAW_LIM_SWITCH) == 1) {
   pwm_start(SERVO_PIN, CLOCKF, TPWM, 30, 0);      // Turn SG90 servo Left to 45 degrees
   delay(2000); 
   for(servoAngle = 30; servoAngle < 120; servoAngle++)  //move the micro servo from 0 degrees to 180 degrees
  {                                  
    if(servoAngle % 2 == 0) {
    pwm_start(SERVO_PIN, CLOCKF, TPWM, servoAngle, 0);              
    delay(50);  
    }                 
  }
  delay(500);
  } 

  encoderVal = digitalRead(ROT_ENCODER);
  if(encoderVal != prevEncoderVal) {
    loops++;
    prevEncoderVal = encoderVal;
  }
  if(loops % 48 == 0 && loops != 0) {
    reLo++;
  }
  Serial.print("You have gone: ");Serial.print((loops / 2) * (360.0 / 24.0));Serial.println(" degrees.");

  //  pwm_start(REVERSE_PIN, CLOCKF, TPWM, 450, 1);
  // pwm_start(FORWARD_PIN, CLOCKF, TPWM, 450, 1);
  //  delay(1000); 
  //   pwm_start(REVERSE_PIN, CLOCKF, TPWM, 400, 1);
  //   pwm_start(FORWARD_PIN, CLOCKF, TPWM, 400, 1);
  //   delay(1000);
  //   pwm_start(REVERSE_PIN, CLOCKF, TPWM, 300, 1);
  //   pwm_start(FORWARD_PIN, CLOCKF, TPWM, 300, 1);
  //   delay(1000);
  //   pwm_start(REVERSE_PIN, CLOCKF, TPWM, 200, 1);
  //   pwm_start(FORWARD_PIN, CLOCKF, TPWM, 200, 1);
  //   delay(1000);
  //   pwm_start(REVERSE_PIN, CLOCKF, TPWM, 100, 1);
  //   pwm_start(FORWARD_PIN, CLOCKF, TPWM, 100, 1);
  //   delay(1000);
  //   pwm_start(REVERSE_PIN, CLOCKF, TPWM, 50, 1);
  //   pwm_start(FORWARD_PIN, CLOCKF, TPWM, 50, 1);
  //   delay(1000);
  //   pwm_start(REVERSE_PIN, CLOCKF, TPWM, 0, 1);
  //   pwm_start(FORWARD_PIN, CLOCKF, TPWM, 0, 1);
  //   delay(1000);
  
  //  servo.write(135);     // Turn SG90 servo Right to 135 degrees
  //  delay(1000);          // Wait 1 second
  //  servo.write(90);      // Turn SG90 servo back to 90 degrees (center position)
  //  delay(1000);
 
//end control the servo's direction and the position of the motor
 
 
//control the servo's speed  
 
//if you change the delay value (from example change 50 to 10), the speed of the servo changes
  // for(servoAngle = 30; servoAngle < 120; servoAngle++)  //move the micro servo from 0 degrees to 180 degrees
  // {                                  
  //   if(servoAngle % 2 == 0) {
  //   pwm_start(SERVO_PIN, CLOCKF, TPWM, servoAngle, 0);              
  //   delay(50);  
  //   }                 
  // }
  // delay(1000);
 
  // for(servoAngle = 120; servoAngle >= 35; servoAngle--)  //now move back the micro servo from 0 degrees to 180 degrees
  // {                                
  //  if(servoAngle % 2 == 0) {
  //   pwm_start(SERVO_PIN, CLOCKF, TPWM, servoAngle, 0);              
  //   delay(50);  
  //   }            
  // }
  //end control the servo's speed  
}