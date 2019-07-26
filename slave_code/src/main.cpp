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
#define DISTANCE_PER_REV 50.75 //mm (perhaps)

#define FORWARD 1
#define REVERSE -1

<<<<<<< HEAD
#define GAUNTLET 'G
=======
#define GAUNTLET 'G'
>>>>>>> dfbea0e0d088c7522824b7cf2431a8f36c7283c7
#define LEFT_POST 'L'
#define RIGHT_POST 'R'

// put your setup code here, to run once:
Larry larry;
Talons talons;
Leviosa leviosa;
Susan susan;

// void handle_encoder_interrupt();


void setup() {

  Serial.begin(115200);
  // pinMode(ENCODER_PIN, INPUT);



  // attachInterrupt(ENCODER_PIN, handle_encoder_interrupt, RISING);
  Serial.println("fuck");
  
}


void loop() {
<<<<<<< HEAD
  // put your main code here, to run repeatedly:
  //Serial.println("fuck");
  larry.move_larry(99);
  //open_claw();
  talons.open_claw();
  //open_claw();
  //larry.go_home_larry();
  larry.go_far_larry();
  delay(500);
  talons.close_claw();

  //close_claw();
  delay(1000);
=======

  

  char message = wait_for_master();
  switch(message){
    case LEFT_POST:
      pick_up_stone_left();
    case RIGHT_POST:
      pick_up_stone_right();
    case GAUNTLET:
      gauntlet_disposal();
  }
  Serial.write('D');
  susan.turn_susan(172);
  // delay(1000);
  delay(200);
  susan.turn_susan(0);
  delay(200);
  // delay(1000);

  // susan.turn_susan(162);

  // delay(3000);

  // susan.turn_susan(0);

  // delay(3000);

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

>>>>>>> dfbea0e0d088c7522824b7cf2431a8f36c7283c7
  
}

void handle_encoder_interrupt(){
  if (larry.state == FORWARD){
    larry.current_position -= DISTANCE_PER_REV / TICKS_PER_REV;
  }
  else if (larry.state == REVERSE){
    larry.current_position += DISTANCE_PER_REV / TICKS_PER_REV;
  }
<<<<<<< HEAD

  if (larry.current_position < 0){
    larry.current_position = 0;
  }
  Serial.println(larry.current_position);
=======
  // Serial.println(larry.current_position);
  if(larry.current_position < 0) {
    larry.current_position = 0;
  } 
  
}

char wait_for_master() {
  char message = 0;
  while (true) {
    if (Serial.available() > 0) {
      message = Serial.read();
      if (message == LEFT_POST || message == RIGHT_POST || message == GAUNTLET) {
        return message;
      }
    }
  }
}

void pick_up_stone_left(){
    susan.turn_susan(-172);
    leviosa.wingardium_leviosa(30);
    susan.point_to_min_distance();
    larry.go_far_larry();
    
}

void pick_up_stone_right(){
    susan.turn_susan(172);
    leviosa.wingardium_leviosa(30);
    larry.go_far_larry();
}

void gauntlet_disposal(){

>>>>>>> dfbea0e0d088c7522824b7cf2431a8f36c7283c7
}

char wait_for_master() {
  char message = 0;
  while (true) {
    if (Serial.available() > 0) {
      message = Serial.read();
      if (message == LEFT_POST)
        return message;
    }
  }
}
