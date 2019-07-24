#include <Larry.h>
#include <Leviosa.h>
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

#define ENCODER_PIN PB12

#define TICKS_PER_REV 24.0 
#define DISTANCE_PER_REV 50.0 //mm (perhaps)

#define FORWARD 1
#define REVERSE -1

#define SERVO_PIN PB_1
#define TPWM 500
#define CLOCKF 100000
#define CLAW_LIMIT_PIN PB13
#define CLOSED_ANGLE 30

// put your setup code here, to run once:
Larry larry;
// Leviosa leviosa;
// Susan susan;

void handle_encoder_interrupt();
void pick_up_stone();
void close_claw();
void open_claw();

void pick_up_stone(){

}

void setup() {

  Serial.begin(115200);
  pinMode(ENCODER_PIN, INPUT);

  pinMode(SERVO_PIN, OUTPUT);
  pinMode(CLAW_LIMIT_PIN, INPUT);
  pwm_start(SERVO_PIN, CLOCKF, TPWM, 120, 1);

  attachInterrupt(ENCODER_PIN, handle_encoder_interrupt, RISING);
  Serial.println("fuck");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("fuck");
  larry.move_larry(100);
  //open_claw();
  delay(1000);
  //larry.go_home_larry();
  larry.go_far_larry();
  delay(500);
  //close_claw();
  delay(1000);
  
}

void handle_encoder_interrupt(){
  if (larry.state == FORWARD){
    larry.current_position -= DISTANCE_PER_REV / TICKS_PER_REV;
  }
  else if (larry.state == REVERSE){
    larry.current_position += DISTANCE_PER_REV / TICKS_PER_REV;
  }

  //Serial.println(larry.current_position);
}

void open_claw(){
  int servoAngle = 0;
  for(servoAngle = 30; servoAngle < 120; servoAngle++) {
    if(servoAngle % 2 == 0) {
    pwm_start(SERVO_PIN, CLOCKF, TPWM, servoAngle, 0);
    delay(50); //change this to change speed
    }
  }
}

void close_claw(){
  pwm_start(SERVO_PIN, CLOCKF, TPWM, CLOSED_ANGLE, 0);
}

