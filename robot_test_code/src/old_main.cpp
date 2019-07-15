// #include <Arduino.h>
// #include <Wire.h>
// #include <time.h>
// #include <math.h>
// #include <Adafruit_SSD1306.h>
// #include <FreeMono12pt7b.h>
// #include <FreeMono9pt7b.h>
// #include <stdint.h>
// #include "PinNames.h"






// #define BPILL_ADDRESS 5

// #define MULTIPLEX_OUT PA_0
// #define A PB_3
// #define B PB_13
// #define C PB_4
// #define LEFT_REVERSE_PIN PA_6 //ORANGE WIRE
// #define LEFT_FORWARD_PIN PA_7 //YELLOW WIRE
// #define RIGHT_FORWARD_PIN PB_1 // red
// #define RIGHT_REVERSE_PIN PB_0 //brown  
// #define KP_PIN PA_3 //yellow
// #define KD_PIN PA_2 //orang
// #define LEFT_WHEEL_INTERRUPT PB_4
// #define RIGHT_WHEEL_INTERRUPT PB_5
// #define RIGHT_TRIG_PIN PB_12
// #define RIGHT_ECHO_PIN PB_11
// #define LEFT_TRIG_PIN PB_10
// #define LEFT_ECHO_PIN PB_9
// #define FRONT_TRIG_PIN_LOW PB_8
// #define FRONT_ECHO_PIN_LOW PA_8
// #define FRONT_TRIG_PIN_HIGH PB_14
// #define FRONT_ECHO_PIN_HIGH PB_15
// #define STATE_INTERRUPT PA_5

// #define TPWM 500
// #define CLOCKF 100000


// //KP 486   KD 109

// #define DIFTHRESH 250
// #define REG_SPEED 100
// #define POT_THRESH 5

// #define DISTANCETHRESH 100

// volatile byte a = 1;

// void handle_left_wheel_interrupt();
// void handle_right_wheel_interrupt();
// void handle_state(); //implement built in led
// void qrd_behaviour();
// void sonar_behaviour();
// void masterTransmit();
// void masterRequest();
// void calculate_pid();
// void motor_control();
// void read_K_values();
// boolean ramp_branch_detection();
// boolean right_pole_detection();
// boolean left_pole_detection();
// boolean gauntlet_branch_detection();
// void front_sonar();
// void side_sonar(PinName trigpin, PinName echopin, char side);
// float pulse(PinName trigpin, PinName echopin);
// void tape_following();


// float previousError = 0.0;
// float error = 0.0;


// int count = 0;

// #define OLED_RESET -1
// Adafruit_SSD1306 display(OLED_RESET);

// float KPPrev = 0.0;
// float KDPrev = 0.0;
// double KD = 0;
// double KP = 0;

// float PID_value = 0;

// // float current_left_motor_speed = REG_SPEED;
// // float current_right_motor_speed = REG_SPEED; 

// volatile int left_i = 0;
// volatile int right_i = 0;

// int num_branch = 0; 
// int state = 0; 
// char progression_state = 'ramp_state'; //states are ramp_state, normal, sanctum_to, sanctum_from, gauntlet
// int num_stones = 0;


// void setup()
// {
//   Serial.begin(115200);
  

//   // initialize LED digital pin as an output.
//   pinMode(LEFT_FORWARD_PIN, OUTPUT);
//   pinMode(LEFT_REVERSE_PIN, OUTPUT);
//   pinMode(RIGHT_FORWARD_PIN, OUTPUT);
//   pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
//   pinMode(MULTIPLEX_OUT, INPUT_ANALOG);
//   pinMode(A,OUTPUT);
//   pinMode(B,OUTPUT);
//   pinMode(C,OUTPUT);
//   pinMode(KP_PIN, INPUT);
//   pinMode(KD_PIN, INPUT);
//   pinMode(LEFT_WHEEL_INTERRUPT, INPUT_PULLUP);
//   pinMode(RIGHT_WHEEL_INTERRUPT, INPUT_PULLUP);
//   pinMode(RIGHT_TRIG_PIN, OUTPUT);
//   pinMode(RIGHT_ECHO_PIN, INPUT);
//   pinMode(LEFT_TRIG_PIN, OUTPUT);
//   pinMode(LEFT_ECHO_PIN, INPUT);
//   pinMode(FRONT_TRIG_PIN_LOW, OUTPUT);
//   pinMode(FRONT_ECHO_PIN_LOW, INPUT);
//   pinMode(FRONT_TRIG_PIN_HIGH, OUTPUT);
//   pinMode(FRONT_ECHO_PIN_HIGH, INPUT);
//   pinMode(STATE_INTERRUPT, INPUT_PULLUP);
//   pinMode(LED_BUILTIN, OUTPUT);

//   attachInterrupt(LEFT_WHEEL_INTERRUPT, handle_left_wheel_interrupt, RISING);
//   attachInterrupt(RIGHT_WHEEL_INTERRUPT, handle_right_wheel_interrupt, RISING);
//   attachInterrupt(STATE_INTERRUPT, handle_state, RISING);

//   Wire.begin();
  

//   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//   display.clearDisplay();
//   display.setTextSize(1);
//   display.setTextColor(WHITE);
//   display.setCursor(0,0);
//   display.println("OLED Display 128x64");
//   display.setFont(&FreeMono12pt7b);
//   display.drawPixel(0,45,WHITE);
//   display.setCursor(4,45);
//   display.println("Welcome!");
//   display.display();

//   //start going forwards
//   // digitalWrite(LEFT_FORWARD_PIN, HIGH);
//   pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 1);
//   pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 1);

  
//   }

// void loop()
// {

//   if(progression_state == 'ramp_state'){
//     qrd_behaviour();
//     sonar_behaviour();
//   }else if(progression_state == 'normal'){
//   }else if(progression_state == 'sanctum_to'){
//     //reverse then 90 degree turn into sanctum, align to middle of sanctum hopefully
//     progression_state = 'sanctum_from';
//   }else if(progression_state == 'sanctum_from'){
//     //U-TURN straight back onto the tape
//     //essentially a do while loop until one of the sensors trigger on the tape
//     progression_state = 'gauntlet';
//     num_branch = 0;
//   }else if(progression_state == 'gauntlet'){
//     qrd_behaviour();
//     sonar_behaviour();
//   }
// }

// void handle_left_wheel_interrupt(){
//   left_i++;
// }

// void handle_right_wheel_interrupt(){
//   right_i++;
// }

// void qrd_behaviour(){
//   tape_following();
//   if(error == 100){
//     do{
//       tape_following();
//       int left_motor_speed = 110;
//       int right_motor_speed = 90;
//       pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 0);
//       pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 0);
//     }while(error != 0);
//     num_branch++;

//   }else if(error == 101){
//     do{
//       tape_following();
//       int left_motor_speed = 90;
//       int right_motor_speed = 110;
//       pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 0);
//       pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 0);
//     }while(error != 0);
//     num_branch++;

//   } else if(error == 102){
//       //tell other blue pill to begin to 
//       float sideLeftSensor1, sideLeftSensor2, sideLeftSensor3;
//       do{
//            sideLeftSensor1 = analogRead(MULTIPLEX_OUT);
//            sideLeftSensor2 = analogRead(MULTIPLEX_OUT);
//            sideLeftSensor3 = analogRead(MULTIPLEX_OUT);
//         //align with post using encoders
//       }while(sideLeftSensor1 >= DIFTHRESH && sideLeftSensor2 >= DIFTHRESH && sideLeftSensor3 > DIFTHRESH);
//       masterTransmit();
//       masterRequest();
//       num_stones++;
//   } else if(error == 103){
//       float sideRightSensor1, sideRightSensor2, sideRightSensor3;
//       do{
//           sideRightSensor1 = analogRead(MULTIPLEX_OUT);
//           sideRightSensor2 = analogRead(MULTIPLEX_OUT);
//           sideRightSensor3 = analogRead(MULTIPLEX_OUT);
//           // align with post using encoders
//       }while(sideRightSensor1 >= DIFTHRESH && sideRightSensor2 >= DIFTHRESH && sideRightSensor3 > DIFTHRESH);
//       masterTransmit();
//       masterRequest();
//       num_stones++;
//   } else if(error == 104){

//   } else if(error == 105){

//   } else{
//     calculate_pid();
//     motor_control();
//   }
//   read_K_values();

//   if(num_branch == 2 && progression_state == 'ramp_state'){
//     progression_state = 'normal';
//   }

//   if(num_stones == 2){
//     progression_state = 'sanctum_to';
//   }
// }

// void handle_state(){
//   state++; 
//   if(state%2 == 0){ //if it's in first state
//     digitalWrite(LED_BUILTIN, HIGH);
//   }else{// if it's in second state
//     digitalWrite(LED_BUILTIN, LOW);
//   }
// }

// void tape_following(){
//   float mainLeftSensor = analogRead(MULTIPLEX_OUT);
//   float mainRightSensor = analogRead(MULTIPLEX_OUT);
//   float mainMiddleSensor = analogRead(MULTIPLEX_OUT);
//   boolean detected;
  
//   if(progression_state == 'ramp_state'){
//     detected = ramp_branch_detection();
//     if(detected){
//       return;
//     }
//   }else if(progression_state == 'normal'){
//     if(state%2 == 0){
//       detected = right_pole_detection();
//     }else{
//       detected = left_pole_detection();
//     }
    
//     if(detected){
//       return;
//     }
//   }else if(progression_state == 'gauntlet'){
//     detected = gauntlet_branch_detection();
//     if(detected){
//       return;
//     }
//   }

//   if (mainRightSensor < DIFTHRESH && mainLeftSensor < DIFTHRESH && mainMiddleSensor < DIFTHRESH) {
//         if (previousError < 0){
//             error = -5;
//         } else {
//             error = 5;
//         }
//   } else if (mainLeftSensor < DIFTHRESH && mainMiddleSensor < DIFTHRESH){
//       error = -3;
//   } else if (mainLeftSensor < DIFTHRESH) {
//       error = -1;
//   } else if (mainRightSensor< DIFTHRESH && mainMiddleSensor < DIFTHRESH) {
//       error = 3;
//   } else if (mainRightSensor< DIFTHRESH) {
//       error = 1;
//   } else {
//       error = 0;
//   }

// }

// boolean ramp_branch_detection(){
//   float cornerLeftSensor = analogRead(MULTIPLEX_OUT);
//   float cornerRightSensor = analogRead(MULTIPLEX_OUT);
//   if(cornerRightSensor < DIFTHRESH && num_branch < 2){
//       error = 100;
//       return true;
//   } else if(cornerLeftSensor < DIFTHRESH && num_branch < 2){
//       error = 101;
//       return true;
//   }
//   return false;
// }

// boolean gauntlet_branch_detection(){
//   float cornerLeftSensor = analogRead(MULTIPLEX_OUT);
//   float cornerRightSensor = analogRead(MULTIPLEX_OUT);

//   if(cornerRightSensor < DIFTHRESH && num_branch == 1){
//     error = 104;
//     return true;
//   }else if(cornerRightSensor < DIFTHRESH && num_branch == 2){
//     error = 105; 
//     return true;
//   }
//   return false;
// }

// boolean right_pole_detection(){
//   float sideRightSensor1 = analogRead(MULTIPLEX_OUT);
//   float sideRightSensor2 = analogRead(MULTIPLEX_OUT);
//   float sideRightSensor3 = analogRead(MULTIPLEX_OUT);

//   if((sideRightSensor1 < DIFTHRESH || sideRightSensor2 < DIFTHRESH || sideRightSensor3 < DIFTHRESH) && num_stones != 2){
//       error = 103;
//       return true;
//   }
//   return false;
// }

// boolean left_pole_detection(){
//   float sideLeftSensor1 = analogRead(MULTIPLEX_OUT);
//   float sideLeftSensor2 = analogRead(MULTIPLEX_OUT);
//   float sideLeftSensor3 = analogRead(MULTIPLEX_OUT);

//   if((sideLeftSensor1 < DIFTHRESH || sideLeftSensor2 < DIFTHRESH || sideLeftSensor3 < DIFTHRESH) && num_stones != 2){
//       error = 102;
//       return true;
//   }
//   return false;

// }

// void read_K_values(){
//     KP = (float) analogRead(KP_PIN);
//     KD = (float) analogRead(KD_PIN);
    
//     if (abs(KP - KPPrev) > POT_THRESH || abs(KD-KDPrev) > POT_THRESH) {
//       display.clearDisplay();
//       display.setFont(&FreeMono9pt7b);
//       display.setCursor(4,20);
//       display.print("KP: "); display.println(KP);
//       display.setCursor(4,50);
//       display.print("KD: "); display.println(KD);
//       display.display();
//       KPPrev = KP;
//       KDPrev = KD;
//       Serial.println("Hi");
//     }
//     Serial.println(KP);Serial.println(KD);
// }

// void calculate_pid(){
//     float p = KP * error;
//     float d = KD * (error - previousError);
//     PID_value = (p + d) / 15.0;
// }

// void motor_control(){
//   int left_motor_speed = REG_SPEED - PID_value;
//   int right_motor_speed = REG_SPEED + PID_value;

//   left_motor_speed = constrain(left_motor_speed, 0, TPWM);
//   right_motor_speed = constrain(right_motor_speed, 0, TPWM);

//   pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 0);
//   pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 0);
// }

// void sonar_behaviour(){
//   front_sonar();
//   side_sonar(LEFT_TRIG_PIN, LEFT_ECHO_PIN, 'left');
//   side_sonar(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN, 'right');
// }

// void front_sonar(){
//   float low_distance = pulse(FRONT_TRIG_PIN_LOW, FRONT_ECHO_PIN_LOW);

//   if(low_distance < 30){
//     float high_distance = pulse(FRONT_TRIG_PIN_HIGH, FRONT_ECHO_PIN_HIGH);
//     if(high_distance < 30){
//       //senses robot, go backwards
//     }else{
//       //senses plushies, encoders
//     }
//   }
// }

// void side_sonar(PinName trigpin, PinName echopin, char side){

//   float distance = pulse(trigpin, echopin);

//   if(distance < 30) {
//     float new_distance = pulse(trigpin, echopin);
//     if(distance - new_distance > DISTANCETHRESH){//if difference in distance changes above the distance threshold, sense a robot
//       //senses robot, keep going straight
//     }else{
//       if(side == 'left'){
//           //left side senses plushies, encoders
//       }else if(side == 'right'){
//           // right side senses plushies, encoders
//       }
//     }
//   }
// }

// float pulse(PinName trigpin, PinName echopin){
//   digitalWrite(trigpin, LOW);
//   delayMicroseconds(2);
//   // Sets the TRIG_PIN on HIGH state for 10 micro seconds
//   digitalWrite(trigpin, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigpin, LOW);
//   // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
//   long duration = pulseIn(echopin, HIGH);
//   // Calculating the distance
//   float distance= duration*0.034/2;
//   return distance;
// }

// void masterRequest() {
//   Serial.println("Entering master request");
//   delay(500);
//   Wire.requestFrom(BPILL_ADDRESS,1,1);
//   delay(500);
//   while(Wire.available()){
//     byte a = Wire.read();
//     Serial.println(a);
//   }
  
//   delay(5000);
// }

// void masterTransmit() {
//   Wire.beginTransmission(BPILL_ADDRESS);                           
//   Wire.write(12);                        
//   Wire.endTransmission(); 
//   delay(7000);
// }

// //Classes 
// // Tape Following class, Sonar class, communications class, encoder class, potentially a front claw motor class   
