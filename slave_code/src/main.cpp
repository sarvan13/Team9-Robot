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

#define IN_1 PB5
#define IN_2 PB6
#define OUT PB7

#define STATE_DEBOUNCE 5
// #define GAUNTLET 'G'
// #define LEFT_POST 'L'
// #define RIGHT_POST 'R'

// char wait_for_master();
void pick_up_stone_left();
void pick_up_stone_right();
void gauntlet_disposal();

int current_position;

int arm_counter = 0;

// put your setup code here, to run once:
Larry larry;
Talons talons;
Leviosa leviosa;
Susan susan;

enum arm_state {
  LEFT_POLE,
  RIGHT_POLE
};

void handle_encoder_interrupt();

arm_state arm_side;

void setup() {

  Serial.begin(115200);

  pinMode(ENCODER_PIN, INPUT);
  attachInterrupt(ENCODER_PIN, handle_encoder_interrupt, RISING);
  pinMode(IN_1, INPUT);
  pinMode(IN_2, INPUT);
  pinMode(OUT, OUTPUT);
  digitalWrite(OUT, LOW);



  //SETUP
  leviosa.go_home_hermione();
  leviosa.wingardium_leviosa(85);
  delay(200);
  larry.go_home_larry();
  larry.move_larry(80);
  delay(200);
  susan.go_home_susan();
  talons.open_claw();
 

  }


void loop() {

  int pin_1 = HIGH;
  int pin_2 = HIGH;
  for (int i = 0; i < STATE_DEBOUNCE; i++) {
    pin_1 = pin_1 && digitalRead(IN_1);
    pin_2 = pin_2 && digitalRead(IN_2);
  }

  if(pin_1 == HIGH && pin_2 == HIGH){
          digitalWrite(OUT, HIGH);
          Serial.println("GAUNTLET");
          gauntlet_disposal();
          digitalWrite(OUT, LOW);
          delay(500);
          larry.move_larry(80);
          delay(200);
          susan.turn_susan(100);
          delay(200);
  }else if(pin_1 == HIGH && pin_2 == LOW){
           digitalWrite(OUT, HIGH);
          Serial.println("LEFT_POST");
          pick_up_stone_left();
          digitalWrite(OUT, LOW);
          delay(500);
          susan.turn_susan(100);
          delay(200);
          arm_counter++;
          arm_side = LEFT_POLE;
  }else if(pin_1 == LOW && pin_2 == HIGH){
          digitalWrite(OUT, HIGH);
          Serial.println("RIGHT_POST");
          pick_up_stone_right();
          digitalWrite(OUT, LOW);
          delay(500);
          susan.turn_susan(100);
          delay(200);
          arm_counter++;
          arm_side = RIGHT_POLE;
          
  }else{
    digitalWrite(OUT, LOW);
    Serial.println("NOTHING"); 
  }

  
}


void pick_up_stone_left(){
  digitalWrite(OUT, HIGH);
  if(arm_counter == 1){
    leviosa.wingardium_leviosa(33);
    delay(200);
    susan.go_home_susan();
    delay(200);
  }
  susan.turn_susan(200);
  delay(200);
  if(arm_counter == 0){
    larry.go_far_larry();
    delay(200);
  }else{
    larry.move_larry(64);
    delay(200);
  }
  larry.move_larry(larry.current_position + 20);
  if(arm_counter == 1){
    susan.set_sweep_angle(30);
  }
  susan.point_to_min_distance();
  delay(400);
  if(arm_counter == 0){
    larry.go_far_larry();
    delay(200);
  }else{
    larry.move_larry(64);
    delay(200);
  }
 
  larry.move_larry(larry.current_position + 8);
  delay(200);
  talons.close_claw();
  delay(1000);
  if(arm_counter == 0){
    leviosa.wingardium_leviosa(92);
    delay(200);
    larry.go_far_larry();
    delay(200);
    leviosa.wingardium_leviosa(100);
    delay(200);
  }else{
    leviosa.wingardium_leviosa(43);
    delay(200);
    larry.move_larry(64);
    delay(200);
    leviosa.wingardium_leviosa(50);
    delay(200);
  }
  susan.go_home_susan();
  delay(200);
  larry.move_larry(90);

  digitalWrite(OUT, LOW);
}

void pick_up_stone_right(){
  digitalWrite(OUT, HIGH);
  if(arm_counter == 1){
    leviosa.wingardium_leviosa(35);
    delay(200);
    susan.go_home_susan();
    delay(200);
  }
  susan.turn_susan(-160);
  delay(200);
  larry.go_far_larry();
  delay(200);
  larry.move_larry(larry.current_position + 20);
  if(arm_counter == 1){
    susan.set_sweep_angle(40);
  }
  susan.point_to_min_distance();
  delay(400);
  larry.go_far_larry();
  delay(200);
  if(arm_counter == 0){
    larry.move_larry(larry.current_position + 8);
  }
  
  delay(200);
  talons.close_claw();
  delay(1000);
  if(arm_counter == 0){
    leviosa.wingardium_leviosa(92);
    delay(200);
    larry.go_far_larry();
    delay(200);
    leviosa.wingardium_leviosa(100);
    delay(200);
  }else{
    leviosa.wingardium_leviosa(43);
    delay(200);
    larry.go_far_larry();
    delay(200);
    leviosa.wingardium_leviosa(50);
    delay(200);
  }
  susan.go_home_susan();
  delay(200);
  larry.move_larry(90);
  digitalWrite(OUT, LOW);
}

void gauntlet_disposal(){
  digitalWrite(OUT, HIGH);
  larry.move_larry(80);
  delay(200);
  leviosa.go_home_hermione();
  delay(200);
  susan.go_home_susan();
  if(arm_side == LEFT_POLE){
    if(arm_counter == 1){
      susan.turn_susan(10);
      delay(200);
      larry.go_home_larry();
      delay(200);
      talons.open_claw();
    }else{
      susan.turn_susan(40);
      delay(200);
      larry.go_home_larry();
      delay(200);
      talons.final_open_claw();
    }
  }else{
    if(arm_counter == 1){
      susan.turn_susan(10);
      delay(200);
      larry.go_home_larry();
      delay(200);
      talons.open_claw();
    }else{
      susan.turn_susan(43);
      delay(200);
      larry.go_home_larry();
      delay(200);
      talons.final_open_claw();
    }
  }
  

  digitalWrite(OUT, LOW);
}

void handle_encoder_interrupt(){
  if (larry.state == FORWARD){
    larry.current_position -= DISTANCE_PER_REV / TICKS_PER_REV;
  }
  else if (larry.state == REVERSE){
    larry.current_position += DISTANCE_PER_REV / TICKS_PER_REV;
  }
  if(larry.current_position < 0){
    larry.current_position = 0;
  } 

}


