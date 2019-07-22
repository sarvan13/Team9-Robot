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

#define STATE_INTERRUPT PA_5

#define COUNTER_THRESH 100

void handle_state(); //implement built in led
void align_marker();

enum progression_state
{
  RAMP_STATE,
  NORMAL,
  AVOID_COLLISION,
  GRAB_PLUSHIE,
  GRAB_STONE,
  SANCTUM_TO,
  SANCTUM_FROM,
  GAUNTLET
};

int state = 0; 
progression_state progress = RAMP_STATE; //states are ramp_state, normal, sanctum_to, sanctum_from, gauntlet, can probably change to enum
int num_stones = 0;
int counter = 0;

Tape_Detection tape_detection;
Movement movement;
// Communication comm;
// Sonar sonar;

void setup()
{
  Serial.begin(115200);

  //initialize LED digital pin as an output.
  // pinMode(STATE_INTERRUPT, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  // attachInterrupt(STATE_INTERRUPT, handle_state, RISING); 
  // movement.forward();
}


void loop()
{
  // tape_detection.get_path_error();
  tape_detection.branch_exists();
// movement.apply_pid(tape_detection.get_pid());
// tape_detection.branch_exists();

//  tape_detection.branch_exists();
// 
  // if(progress == RAMP_STATE){
  //   for(int i = 0; i < 2; i++){
  //     while(tape_detection.branch_exists() == NO_BRANCH || tape_detection.branch_side == LEFT_BRANCH)
  //     {
  //       movement.apply_pid(tape_detection.get_pid());
  //     }
  //     if(tape_detection.branch_side == RIGHT_BRANCH) {
  //       Serial.println("right branch detected");
  //       movement.stop();
  //       delay(200);
  //       movement.turn_right();
  //       delay(150);
  //       movement.set_speed(150);
  //       while(tape_detection.get_path_error() !=0){

  //       }
  //     }
  //   }
  // progress = NORMAL;
  // } else if(progress == NORMAL){
  //   movement.set_speed(300);
  //   while(!(tape_detection.marker_exists() & RIGHT_ON)){
  //       movement.apply_pid(tape_detection.get_pid());
  //   }
  //   if(tape_detection.marker_side){
  //     progress = GRAB_STONE;
  //   }
  // } else if(progress == GRAB_STONE){
  //   while(!(tape_detection.get_marker_error() & ALL_ON)){
  //     align_marker();
  //   }
  //   movement.stop();
  // }
  
  
  // }else if(progress == NORMAL){
  //   if(num_stones >= 2){
  //     progress = SANCTUM_TO;
  //   }
  //   while(sonar.check_sonar() == NO_DETECTION && tape_detection.marker_exists() == NO_BRANCH){
  //     movement.apply_pid(tape_detection.get_pid());
  //   }
  //   if(sonar.sonar_value > 4){
  //     progress = AVOID_COLLISION;
  //   }else if(sonar.sonar_value <= 4){
  //     progress = GRAB_PLUSHIE;
  //   }else if(tape_detection.marker_side){
  //     progress = GRAB_STONE;
  //   }
  // }
  // } else if(progress == AVOID_COLLISION){

  // } else if(progress == GRAB_PLUSHIE){
  //   switch(sonar.sonar_value){
  //       case PLUSHIE_LEFT:
  //           movement.grab_plushie_left();
  //           break;
  //       case PLUSHIE_RIGHT:
  //           movement.grab_plushie_right();
  //           break;
  //       case PLUSHIE_FRONT:
  //           movement.grab_plushie_front();
  //           break;
  //       default:
  //           return;
  //   }
  // } else if(progress == GRAB_STONE){
  //   //align_marker
  //   comm.master_transmit_stone();
  //   comm.master_request();
  //   num_stones++;
  // } else if(progress == SANCTUM_TO){
  //   //reverse then 90 degree turn into sanctum, align to middle of sanctum hopefully
  //   progress = SANCTUM_FROM;
  // }else if(progress == SANCTUM_FROM){
  //   //U-TURN straight back onto the tape
  //   //essentially a do while loop until one of the sensors trigger on the tape
  //   progress = GAUNTLET;
  // }else if(progress == GAUNTLET){
  //   for(int i = 0; i < 2; i++){
  //     while(tape_detection.branch_exists() == NO_BRANCH){
  //       movement.apply_pid(tape_detection.get_pid());
  //     }
  //     if(tape_detection.branch_side == RIGHT_BRANCH){

  //     }
  //     if(tape_detection.branch_side == LEFT_BRANCH){

  //     }
  //   }
  //   movement.reverse();
  //   comm.master_transmit_gauntlet();
  //   comm.master_request();
  //   progress = NORMAL;
  // }
  

}

void handle_state(){
  state++; 
  if(state%2 == 0){ //if it's in first state
    digitalWrite(LED_BUILTIN, HIGH);
  }else{// if it's in second state
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void align_marker(){
    if(counter < COUNTER_THRESH){
        movement.rotate_forward();
    }else{
        movement.rotate_backward();
    }
    counter++;
}



//Classes 
// Tape Following class, Sonar class, communications class, encoder class, potentially a front claw motor class   
