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

  pinMode(ENCODER_PIN, INPUT);
  attachInterrupt(ENCODER_PIN, handle_encoder_interrupt, RISING);

  //PICKING UP STONE FROM FUNNEL
  // delay(1000);
  // leviosa.go_home_hermione();
  // delay(1000);
  // leviosa.wingardium_leviosa(20);
  // delay(500);
  // larry.go_home_larry();
  // susan.go_home_susan();
  // delay(500);
  // larry.move_larry(90);
  // susan.turn_susan(320);
  // delay(500);
  // talons.close_claw();
  // delay(1000);
  // leviosa.wingardium_leviosa(50);
  // susan.turn_susan(100);
  // delay(500);
  // talons.open_claw();
  // delay(1000);
  
  //PICKING UP STONE FROM POLE
  // leviosa.go_home_hermione();
  // delay(200);
  // leviosa.wingardium_leviosa(5);
  // delay(200);
  // leviosa.set_speed(350);
  // leviosa.go_home_hermione();
  // leviosa.set_speed(350);
  // larry.go_home_larry();
  // larry.move_larry(90);
  // susan.go_home_susan();
  // talons.open_claw();

  delay(500);
  leviosa.go_home_hermione();
  delay(200);
  susan.go_home_susan();
  Serial.println("Susan is home!");
  susan.turn_susan(-100);
  delay(200);
  susan.point_to_min_distance();
  delay(200);
  larry.go_far_larry();
  talons.hug_pole();
  delay(1000);
  leviosa.wingardium_leviosa(53);
  talons.close_claw();
  delay(1000);
  leviosa.wingardium_leviosa(70);
  // susan.turn_susan(100);
  // delay(500);
  // talons.open_claw();
  // delay(200);
  // susan.turn_susan(0);

  //DROPPING STONE TO FUNNEL
  susan.go_home_susan();
  delay(500);
  leviosa.wingardium_leviosa(30);
  delay(500);
  larry.go_home_larry();
  
  delay(500);
  larry.move_larry(90);
  susan.turn_susan(321);
  delay(500);
  delay(500);
  talons.open_claw();
  delay(500);
  susan.turn_susan(100);


  }


void loop() {
  // Serial.println(digitalRead(LIMIT_PIN));
  susan.get_sonar_distance();
}

void handle_encoder_interrupt(){
  if (larry.state == FORWARD){
    larry.current_position -= DISTANCE_PER_REV / TICKS_PER_REV;
  }
  else if (larry.state == REVERSE){
    larry.current_position += DISTANCE_PER_REV / TICKS_PER_REV;
  }

  Serial.println(current_position);

  if(larry.current_position < 0){
    larry.current_position = 0;
  } 
  
}

// // char wait_for_master() {
// //   char message = 0;
// //   while (true) {
// //     if (Serial.available() > 0) {
// //       message = Serial.read();
// //       if (message == LEFT_POST || message == RIGHT_POST || message == GAUNTLET) {
// //         return message;
// //       }
// //     }
// //   }
// // }

// void pick_up_stone_left(){

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
    
//}

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


