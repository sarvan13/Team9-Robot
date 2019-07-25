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


// put your setup code here, to run once:
Larry larry;
Talons talons;
// Leviosa leviosa;
// Susan susan;

void handle_encoder_interrupt();
void pick_up_stone();


void pick_up_stone(){

}

void setup() {

  Serial.begin(115200);
  pinMode(ENCODER_PIN, INPUT);

  attachInterrupt(ENCODER_PIN, handle_encoder_interrupt, RISING);
  Serial.println("fuck");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("fuck");
<<<<<<< HEAD
  larry.move_larry(99);
  talons.open_claw();
  //open_claw();
=======
  larry.move_larry(100);
  talons.open_claw();
<<<<<<< HEAD
=======
=======
<<<<<<< HEAD
  talons.open_claw();
=======
  //open_claw();
>>>>>>> 052726638c4e414d1bcad1889f4403f1898576fe
>>>>>>> 46be8a23352421d048885a65526c400ac2569257
>>>>>>> 29bd93ea5f784cf090581d694ba8deccbe8392f8
>>>>>>> 425447b9514828bf693a7c4ef3232fd79e6b6ad1
  delay(1000);
  //larry.go_home_larry();
  larry.go_far_larry();
  delay(500);
<<<<<<< HEAD

=======
  talons.close_claw();
<<<<<<< HEAD
=======
=======
<<<<<<< HEAD
>>>>>>> 425447b9514828bf693a7c4ef3232fd79e6b6ad1
  talons.close_claw();

  //close_claw();
<<<<<<< HEAD
=======
>>>>>>> 052726638c4e414d1bcad1889f4403f1898576fe
>>>>>>> 46be8a23352421d048885a65526c400ac2569257
>>>>>>> 29bd93ea5f784cf090581d694ba8deccbe8392f8
>>>>>>> 425447b9514828bf693a7c4ef3232fd79e6b6ad1
  delay(1000);
  
}

void handle_encoder_interrupt(){
  if (larry.state == FORWARD){
    larry.current_position -= DISTANCE_PER_REV / TICKS_PER_REV;
  }
  else if (larry.state == REVERSE){
    larry.current_position += DISTANCE_PER_REV / TICKS_PER_REV;
  }

  if (larry.current_position < 0){
    larry.current_position = 0;
  }
  Serial.println(larry.current_position);
}

