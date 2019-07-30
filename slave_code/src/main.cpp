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

#define GAUNTLET 'G'
#define LEFT_POST 'L'
#define RIGHT_POST 'R'

char wait_for_master();
void pick_up_stone_left();
void pick_up_stone_right();
void gauntlet_disposal();

int current_position;

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
  susan.point_to_min_distance();
  
}


void loop() {
  //First test if sonar works

  // char message = wait_for_master();
  // switch(message){
  //   case LEFT_POST:
  //     pick_up_stone_left();
  //   case RIGHT_POST:
  //     pick_up_stone_right();
  //   case GAUNTLET:
  //     gauntlet_disposal();
  // }

  // Serial.write('D');
}

void handle_encoder_interrupt(){
  if (larry.state == FORWARD){
    larry.current_position -= DISTANCE_PER_REV / TICKS_PER_REV;
  }
  else if (larry.state == REVERSE){
    larry.current_position += DISTANCE_PER_REV / TICKS_PER_REV;
  }
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
    leviosa.go_home_hermione();
    float distance = susan.point_to_min_distance();
    if(larry.go_far_larry() == FAIL){

      if(larry.go_far_larry() == FAIL)
        return;
    }
    current_position = leviosa.get_current_position();
    while(!digitalRead(CLAW_LIMIT_PIN)){
      current_position++;
      leviosa.wingardium_leviosa(current_position);
    }
    talons.close_claw();
    leviosa.wingardium_leviosa(current_position + 30);
    larry.move_larry(larry.current_position + 20);
    susan.turn_susan(-344);
    //lower by certain amount 
    
}

void pick_up_stone_right(){
    susan.turn_susan(172);
   leviosa.go_home_hermione();
    float distance = susan.point_to_min_distance();
    if(larry.go_far_larry() == FAIL){

      if(larry.go_far_larry() == FAIL)
        return;
    }
    current_position = leviosa.get_current_position();
    while(!digitalRead(CLAW_LIMIT_PIN)){
      current_position++;
      leviosa.wingardium_leviosa(current_position);
    }
    talons.close_claw();
    leviosa.wingardium_leviosa(current_position + 30);
    larry.move_larry(larry.current_position + 20);
    susan.turn_susan(344);
}

void gauntlet_disposal(){

}


