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

// char wait_for_master();
// void pick_up_stone_left();
// void pick_up_stone_right();
// void gauntlet_disposal();

int current_position;

// put your setup code here, to run once:
Larry larry;
Talons talons;
Leviosa leviosa;
Susan susan;

void handle_encoder_interrupt();


void setup() {

  Serial.begin(115200);

  // leviosa.go_home_hermione();
  // leviosa.wingardium_leviosa(100);
  pinMode(ENCODER_PIN, INPUT);
  // susan.go_home_susan();
  // talons.open_claw();
  
 
  
  
  // leviosa.go_home_hermione();
  attachInterrupt(ENCODER_PIN, handle_encoder_interrupt, RISING);
  // susan.turn_susan(100);
  // susan.turn_susan(0);
  //Third Test

  // susan.go_home_susan();
 
  // susan.point_to_min_distance();
  // talons.open_claw();
  // susan.point_to_min_distance();
  // larry.go_far_larry();
  // larry.move_larry(80);
  
  // talons.close_claw();
  // leviosa.wingardium_leviosa(leviosa.get_current_position() + 30);
//  talons.open_claw();
//   delay(5000);
//   talons.close_claw();
// leviosa.wingardium_leviosa(260);
//  leviosa.go_home_hermione();
// delay(5000);
// talons.open_claw();
// larry.go_home_larry();
// larry.move_larry(90);
// delay(1000);
// susan.point_to_min_distance();
// larry.go_far_larry();
// while(digitalRead(CLAW_LIMIT_PIN)){
//     leviosa.wingardium_leviosa(leviosa.get_current_position() + 1);
// }
// talons.close_claw();
// leviosa.wingardium_leviosa(leviosa.get_current_position() + 30);
// talons.open_claw();
// delay(1000);
leviosa.go_home_hermione();
// leviosa.wingardium_leviosa(5);
// delay(500);
// susan.point_to_min_distance();
// delay(1000);
// larry.go_far_larry();
// delay(1000);
// talons.close_claw();
// delay(1000);
// leviosa.wingardium_leviosa(50);
// susan.turn_susan(259);
// delay(1000);
// larry.move_larry(85);
// talons.open_claw();

// leviosa.go_home_hermione();
// leviosa.wingardium_leviosa(40);

// leviosa.go_home_hermione();
// susan.go_home_susan();
//susan.turn_susan(100);
  
}


void loop() {

 
// leviosa.read_leviosa();
  // susan.turn_susan(100);
  // delay(1000);
  // susan.turn_susan(0);
  // delay(1000);
  // delay(1000 );
  // susan.turn_susan(0);
  // Serial.println("hello");
  // talons.open_claw();
  // delay(500);
  // talons.close_claw();
  // delay(500);
  // susan.get_sonar_distance();
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
  // pick_up_stone_left();
  
}

void handle_encoder_interrupt(){
  if (larry.state == FORWARD){
    larry.current_position -= DISTANCE_PER_REV / TICKS_PER_REV;
  }
  else if (larry.state == REVERSE){
    larry.current_position += DISTANCE_PER_REV / TICKS_PER_REV;
  }
  Serial.println(larry.current_position);
  if(larry.current_position < 0) {
    larry.current_position = 0;
  } 
  
}

// char wait_for_master() {
//   char message = 0;
//   while (true) {
//     if (Serial.available() > 0) {
//       message = Serial.read();
//       if (message == LEFT_POST || message == RIGHT_POST || message == GAUNTLET) {
//         return message;
//       }
//     }
//   }
// }

void pick_up_stone_left(){

    // susan.turn_susan(-172);
    // leviosa.go_home_hermione();
    // float distance = susan.point_to_min_distance();
    // if(larry.go_far_larry() == FAIL){

    //   if(larry.go_far_larry() == FAIL)
    //     return;
    // }
    // current_position = leviosa.get_current_position();
    // while(!digitalRead(CLAW_LIMIT_PIN)){
    //   current_position++;
    //   leviosa.wingardium_leviosa(current_position);
    // }
    // talons.close_claw();
    // leviosa.wingardium_leviosa(current_position + 30);
    // larry.move_larry(larry.current_position + 20);
    // // susan.turn_susan(-344);
    // //lower by certain amount 
    
}

// void pick_up_stone_right(){
//     susan.turn_susan(172);
//    leviosa.go_home_hermione();
//     float distance = susan.point_to_min_distance();
//     if(larry.go_far_larry() == FAIL){

//       if(larry.go_far_larry() == FAIL)
//         return;
//     }
//     current_position = leviosa.get_current_position();
//     while(!digitalRead(CLAW_LIMIT_PIN)){
//       current_position++;
//       leviosa.wingardium_leviosa(current_position);
//     }
//     talons.close_claw();
//     leviosa.wingardium_leviosa(current_position + 30);
//     larry.move_larry(larry.current_position + 20);
//     susan.turn_susan(344);
// }

// void gauntlet_disposal(){

// }


