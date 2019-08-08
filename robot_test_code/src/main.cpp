#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include "PinNames.h"
#include <Tape_Detection.h>
#include <Sonar.h>
#include <Movement.h>
#include <Communication.h>


#define COLLISION_DETECT_PIN PB3
#define OUT_1 PB4
#define OUT_2 PB5
#define IN PB6
#define STATE_SWITCH PA15

//void handle_state(); //implement built in led

enum progression_state
{
  RAMP_STATE,
  NORMAL,
  AVOID_COLLISION,
  GRAB_PLUSHIE,
  GRAB_STONE,
  SANCTUM_TO,
  SANCTUM_FROM,
  GAUNTLET,
  FROM_GAUNTLET,
  GAUNTLET_RETURN,
  STOP
};

enum state
{
  RIGHT_SIDE,
  LEFT_SIDE
};

state side_state;
progression_state progress = RAMP_STATE; //states are ramp_state, normal, sanctum_to, sanctum_from, gauntlet, can probably change to enum

volatile int counter = 0;
int gauntlet_counter = 0;

Tape_Detection tape_detection;
Movement movement;
// Communication comm;
// Sonar sonar;

void handle_collision();
void position_arm_left();
void position_arm_right();
void drop_stone_gauntlet();
void tape_follow_for_millis(int millis);
void tape_follow_backwards_for_millis(int millis);


void handle_collision(){
  counter++;
  Serial.println(counter);
  movement.reverse(300, 300);
  delay(500);
  movement.stop();
}

void setup()
{

  Serial.begin(115200);

  //initialize LED digital pin as an output.
  // pinMode(STATE_INTERRUPT, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(COLLISION_DETECT_PIN, INPUT);
  pinMode(OUT_1, OUTPUT);
  pinMode(OUT_2, OUTPUT);
  pinMode(IN, INPUT);
  pinMode(STATE_SWITCH, INPUT);
  digitalWrite(OUT_1, LOW);
  digitalWrite(OUT_2, LOW);

  if(digitalRead(STATE_SWITCH) == HIGH){
    side_state = LEFT_SIDE;
  }else{
    side_state = RIGHT_SIDE;
  }

}

void loop()
{
  // tape_detection.get_path_error();
  // movement.apply_pid(tape_detection.get_pid());
  // tape_detection.branch_exists();
  // tape_detection.marker_exists();
  // tape_detection.get_alternate_path_error();
  // movement.alternate_pid(tape_detection.alternate_get_pid());
  if(side_state == LEFT_SIDE){
    if(progress == RAMP_STATE){
      for(int i = 0; i < 2; i++){
        while(tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == RIGHT_BRANCH)
        {
          movement.apply_pid(tape_detection.get_pid());
        }
        if(tape_detection.branch_side == LEFT_BRANCH) {
          Serial.println("left branch detected");
          movement.stop();
          delay(200);
          movement.turn_left();
          delay(200);
          while(abs(tape_detection.get_path_error()) >= 4){

          }
          tape_follow_for_millis(100);
        }
      }
      tape_follow_for_millis(500);
    progress = NORMAL;
    } else if(progress == NORMAL){          
          while(tape_detection.marker_exists() == NO_MARKER){
            movement.apply_pid(tape_detection.get_pid());
          }
          movement.stop();
          delay(200);
          movement.set_speed(100);
          tape_detection.set_Kp(40);
          tape_detection.set_Kd(0);
          while(tape_detection.marker_exists() == NO_MARKER){
            movement.alternate_pid(tape_detection.alternate_get_pid());
          }
          delay(100);
          movement.stop();
          delay(40);
          position_arm_left();
          delay(300);
          while(digitalRead(IN)){

          }
          delay(200);
          digitalWrite(OUT_1, LOW);
          digitalWrite(OUT_2, LOW);
      
      progress = GAUNTLET;
    }else if(progress == GAUNTLET){
      if(gauntlet_counter == 0){
        movement.rotate_right(90);
        delay(1000);
        while(abs(tape_detection.get_path_error()) >=4){

        }
      }

      // Cross two branches
      movement.set_speed(500);
      tape_detection.set_Kp(120);
      tape_detection.set_Kd(25);
      while (tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == RIGHT_BRANCH)
      {
        movement.apply_pid(tape_detection.get_pid());
      }
      tape_follow_for_millis(700);
      unsigned long start_time = millis();
      while (tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == RIGHT_BRANCH && millis() - start_time < 1000)
      { 
        movement.apply_pid(tape_detection.get_pid());
      }
    
    // Do a U-turn
    movement.rotate_left(200);
    delay(100);
    while (abs(tape_detection.get_path_error()) >= 4)
    {}
    tape_follow_for_millis(225);
    movement.rotate_right(90);
    delay(2000);
    while (abs(tape_detection.get_path_error()) >= 2)
    {}
    movement.set_speed(140);
    tape_detection.set_Kp(35);
    tape_detection.set_Kd(15);
    tape_follow_for_millis(600);

    // Align back QRDs
    unsigned long start = millis();
    movement.rotate_left(80);
    while(tape_detection.get_alternate_path_error() != 0 && millis() - start < 1000){
     
    }
    movement.stop();
    delay(100);
    start = millis();
    movement.rotate_right(80);
    while(tape_detection.get_alternate_path_error() != 0 && millis() - start < 2000){
     
    }

    movement.set_speed(100);
    tape_detection.set_Kp(40);
    tape_detection.set_Kd(0);
   
   tape_follow_backwards_for_millis(3000);

    movement.stop();
    drop_stone_gauntlet();
    delay(300);
    while(digitalRead(IN)){
        
    }
    digitalWrite(OUT_1, LOW);
    digitalWrite(OUT_2, LOW);
    delay(200);
    if(gauntlet_counter == 0){
      progress = FROM_GAUNTLET;
    } else{
      progress = STOP;
    }
    gauntlet_counter++;
    } else if(progress == FROM_GAUNTLET){
      movement.set_speed(500);
      tape_detection.set_Kp(120);
      tape_detection.set_Kd(25);
      tape_follow_for_millis(70);
      while(tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == LEFT_BRANCH){
        movement.apply_pid(tape_detection.get_pid());
      }
      movement.stop();
      delay(200);
      movement.rotate_right(250);
      delay(200);
      while(abs(tape_detection.get_path_error()) >= 4){

      }
      tape_follow_for_millis(900);
      while(tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == RIGHT_BRANCH){
        movement.apply_pid(tape_detection.get_pid());
      }
      movement.stop();
      delay(200);
      movement.turn_left();
      delay(200);
      while(abs(tape_detection.get_path_error()) >= 4)
      {

      }
      tape_follow_for_millis(4000);
        while(tape_detection.marker_exists() == NO_MARKER || tape_detection.marker_side == RIGHT_MARKER){
          movement.apply_pid(tape_detection.get_pid());
        }
      movement.stop();
      delay(200);
      movement.set_speed(100);
      tape_detection.set_Kp(40);
      tape_detection.set_Kd(0);
      while (tape_detection.marker_exists() == NO_MARKER)
      {
        movement.alternate_pid(tape_detection.alternate_get_pid());
      }
      delay(100);
      movement.stop();
      delay(40);
      position_arm_left();
      delay(300);
      while(digitalRead(IN)){

      }
      digitalWrite(OUT_1, LOW);
      digitalWrite(OUT_2, LOW);
      delay(200);

      progress = GAUNTLET_RETURN;
    } else if(progress == GAUNTLET_RETURN){
      movement.rotate_right(90);
      delay(1000);
      while(abs(tape_detection.get_path_error()) >=4){

      }
      movement.set_speed(140);
      tape_detection.set_Kp(30);
      tape_detection.set_Kd(15);
      while(tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == LEFT_BRANCH){
        movement.apply_pid(tape_detection.get_pid());
      }
    progress = GAUNTLET;
    } else if(progress == STOP){
      movement.stop();
    }
  }
else{
  if (progress == RAMP_STATE)
  {
    for (int i = 0; i < 2; i++)
    {
      while (tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == LEFT_BRANCH)
      {
        movement.apply_pid(tape_detection.get_pid());
      }
      if (tape_detection.branch_side == RIGHT_BRANCH)
      {
        Serial.println("left branch detected");
        movement.stop();
        delay(200);
        movement.turn_right();
        delay(200);
        while (abs(tape_detection.get_path_error()) >= 4)
        {
        }
        tape_follow_for_millis(900);
      }
    }
    tape_follow_for_millis(500);
    progress = NORMAL;
  }
  else if (progress == NORMAL)
  {
      while (tape_detection.marker_exists() == NO_MARKER)
      {
        movement.apply_pid(tape_detection.get_pid());
      }
      movement.stop();
      delay(200);
      movement.set_speed(100);
      tape_detection.set_Kp(40);
      tape_detection.set_Kd(0);
      while (tape_detection.marker_exists() == NO_MARKER)
      {
        movement.alternate_pid(tape_detection.alternate_get_pid());
      }
      delay(100);
      movement.stop();
      delay(40);
      position_arm_right();
      delay(300);
      while(digitalRead(IN)){

      }
      digitalWrite(OUT_1, LOW);
      digitalWrite(OUT_2, LOW);
      delay(200);
    progress = GAUNTLET;
  }
  else if (progress == GAUNTLET)
  {
    if(gauntlet_counter == 0){
      movement.rotate_left(90);
      delay(1000);
      while (abs(tape_detection.get_path_error()) >= 4)
      {
      }
    }

    // Cross two branches
    movement.set_speed(500);
    tape_detection.set_Kp(120);
    tape_detection.set_Kd(25);
    while (tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == LEFT_BRANCH)
    {
      movement.apply_pid(tape_detection.get_pid());
    }
    tape_follow_for_millis(700);
    unsigned long start_time = millis();
    while (tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == LEFT_BRANCH && millis() - start_time < 1000)
    { 
      movement.apply_pid(tape_detection.get_pid());
    }
  
    // Do a U-Turn
    tape_follow_for_millis(500);
    movement.rotate_right(200);
    delay(100);
    while (abs(tape_detection.get_path_error()) >= 4)
    {}
    tape_follow_for_millis(225);
    movement.rotate_left(90);
    delay(2000);
    while (abs(tape_detection.get_path_error()) >= 2)
    {}
    movement.set_speed(140);
    tape_detection.set_Kp(35);
    tape_detection.set_Kd(15);
    tape_follow_for_millis(600);

    // Align back QRDs
    start_time = millis();
    movement.rotate_right(80);
    while(tape_detection.get_alternate_path_error() != 0 && millis() - start_time < 1000){
     
    }
    movement.stop();
    delay(100);
    start_time = millis();
    movement.rotate_left(80);
    while(tape_detection.get_alternate_path_error() != 0 && millis() - start_time < 2000){
     
    }

    movement.set_speed(100);
    tape_detection.set_Kp(40);
    tape_detection.set_Kd(0);
    
    tape_follow_backwards_for_millis(3000);

    movement.stop();
    drop_stone_gauntlet();
    delay(300);
    while(digitalRead(IN)){
        
    }
    digitalWrite(OUT_1, LOW);
    digitalWrite(OUT_2, LOW);
    delay(200);

    if(gauntlet_counter == 0){
      progress = FROM_GAUNTLET;
    } else{
      progress = STOP;
    }
    gauntlet_counter++;
  }
  else if (progress == FROM_GAUNTLET)
  { 
      movement.set_speed(500);
      tape_detection.set_Kp(120);
      tape_detection.set_Kd(25);
      tape_follow_for_millis(70);
     while(tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == RIGHT_BRANCH){
        movement.apply_pid(tape_detection.get_pid());
      }
      movement.stop();
      delay(200);
      movement.rotate_left(250);
      delay(200);
      while(abs(tape_detection.get_path_error()) >= 4){

      }
      tape_follow_for_millis(900);
      while(tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == LEFT_BRANCH){
        movement.apply_pid(tape_detection.get_pid());
      }
      movement.stop();
      delay(200);
      movement.turn_right();
      delay(200);
      while(abs(tape_detection.get_path_error()) >= 4)
      {

      }
      tape_follow_for_millis(4000);
  
      while(tape_detection.marker_exists() == NO_MARKER || tape_detection.marker_side == LEFT_MARKER){
        movement.apply_pid(tape_detection.get_pid());
      }
      movement.stop();
      delay(200);
      movement.set_speed(100);
      tape_detection.set_Kp(40);
      tape_detection.set_Kd(0);
      while (tape_detection.marker_exists() == NO_MARKER)
      {
        movement.alternate_pid(tape_detection.alternate_get_pid());
      }
      delay(100);
      movement.stop();
      delay(40);
      position_arm_right();
      delay(300);
      while(digitalRead(IN)){

      }
      digitalWrite(OUT_1, LOW);
      digitalWrite(OUT_2, LOW);
      delay(200);

      progress = GAUNTLET_RETURN;
  }
  else if (progress == GAUNTLET_RETURN)
  {

      movement.rotate_left(90);
      delay(1000);
      while(abs(tape_detection.get_path_error()) >=4){

      }
      movement.set_speed(140);
      tape_detection.set_Kp(30);
      tape_detection.set_Kd(15);
      while(tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == RIGHT_BRANCH){
        movement.apply_pid(tape_detection.get_pid());
      }

    progress = GAUNTLET;
     
  
  }
  else if (progress == STOP)
  {
    movement.stop();
  }
}
}


void tape_follow_for_millis(int duration) {
  unsigned long start_time = millis();
  while (millis() - start_time < duration) {
    movement.apply_pid(tape_detection.get_pid());
  }
}

void tape_follow_backwards_for_millis(int duration){
  unsigned long start_time = millis();
  while(millis() - start_time < duration){
    movement.alternate_pid(tape_detection.alternate_get_pid());
  }
}

void position_arm_left(){
  digitalWrite(OUT_1, LOW);
  digitalWrite(OUT_2, HIGH);

}

void position_arm_right(){
  digitalWrite(OUT_1, HIGH);
  digitalWrite(OUT_2, LOW);
}

void drop_stone_gauntlet(){
  digitalWrite(OUT_1, HIGH);
  digitalWrite(OUT_2, HIGH);
}

