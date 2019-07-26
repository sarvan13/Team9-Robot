#include <Larry.h>
#include <Leviosa.h>
#include <Susan.h>
#include <Talons.h>
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


// put your setup code here, to run once:
// Larry larry;
// Talons talons;
Leviosa leviosa;
// Susan susan;

void handle_encoder_interrupt();




void setup() {

  Serial.begin(115200);
  pinMode(ENCODER_PIN, INPUT);

  attachInterrupt(ENCODER_PIN, handle_encoder_interrupt, RISING);
  Serial.println("fuck");
  
}

void loop() {


  // // put your main code here, to run repeatedly:
  // //Serial.println("fuck");
  // larry.move_larry(100);
  // talons.open_claw();

  // //open_claw();

  // delay(1000);
  // //larry.go_home_larry();
  // larry.go_far_larry();
  // delay(500);

  // talons.close_claw();



  // //close_claw();

  // delay(1000);

  leviosa.wingardium_leviosa(870);
  // leviosa.read_leviosa();

  
}

void handle_encoder_interrupt(){
  // if (larry.state == FORWARD){
  //   larry.current_position -= DISTANCE_PER_REV / TICKS_PER_REV;
  // }
  // else if (larry.state == REVERSE){
  //   larry.current_position += DISTANCE_PER_REV / TICKS_PER_REV;
  // }


  // Serial.println(larry.current_position);

  //Serial.println(larry.current_position);

}

