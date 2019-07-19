#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>
#include <Adafruit_SSD1306.h>
#include <FreeMono12pt7b.h>
#include <FreeMono9pt7b.h>

// #define MULTIPLEX_OUT PA_0
// #define A PB_3
// #define B PB_13
// #define C PB_4
#define LEFT_REVERSE_PIN PB_1 //ORANGE WIRE
#define LEFT_FORWARD_PIN PB_0 //YELLOW WIRE
#define RIGHT_FORWARD_PIN PA_6 // red, 
#define RIGHT_REVERSE_PIN PA_7 //brown
#define GROUND PB10
#define KP_PIN PA1 //yellow
#define KD_PIN PA2 //orange
#define MULTIPLEX_OUT PA5
#define A PB12  // Left = 000 - Right = 
#define B PB13
#define C PB14

#define TPWM 500
#define CLOCKF 100000


#define DIFTHRESH 300
#define REG_SPEED 300

#define POT_THRESH 10
#define HARDCODE_KP 120 //120
#define HARDCODE_KD 25 //25

float previousError = 0;
float error = 0.0;

int count = 0;

double Kp;
double Kd;
double previous_Kp= 0;
double previous_Kd = 0;

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);


void setup()
{
  Serial.begin(115200);
  

  // initialize LED digital pin as an output.
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  pinMode(GROUND, OUTPUT);
  pinMode(MULTIPLEX_OUT, INPUT_ANALOG);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(KP_PIN, INPUT);
  pinMode(KD_PIN, INPUT);



  

  // display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // display.clearDisplay();
  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0,0);
  // display.println("OLED Display 128x64");
  // display.setFont(&FreeMono12pt7b);
  // display.drawPixel(0,45,WHITE);
  // display.setCursor(4,45);
  // display.println("Welcome!");
  // display.display();

  //start going forwards
  // digitalWrite(LEFT_FORWARD_PIN, HIGH);
 
  // pwm_start(PB_10, CLOCKF, TPWM, TPWM, 1);

  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);

  digitalWrite(GROUND, LOW);

  pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 1);
  pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 1);

  Kp = analogRead(KP_PIN);
  Kd = analogRead(KD_PIN);
  
  }

void loop()
{

  
  // pwm_start(A, CLOCKF, TPWM, 0, 1);
  // pwm_start(B, CLOCKF, TPWM, 0, 1);
  // pwm_start(C, CLOCKF, TPWM, 0, 1);

  //   float leftSensor = analogRead(MULTIPLEX_OUT);
    
  // pwm_start(B, CLOCKF, TPWM, TPWM, 1);
  // pwm_start(C, CLOCKF, TPWM, TPWM, 1);
  //   float rightSensor = analogRead(MULTIPLEX_OUT);
  
  //0 0 0
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  float leftSensor = analogRead(MULTIPLEX_OUT);
  Serial.print(leftSensor); Serial.print(" ");


  //0 1 0
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  float middleSensor = analogRead(MULTIPLEX_OUT);
  Serial.print(middleSensor); Serial.print(" ");


  //1 0 0
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  float rightSensor = analogRead(MULTIPLEX_OUT);
  Serial.print(rightSensor); Serial.print(" ");
  
  
  
  // // 0 1 1  //threshold 300
  // digitalWrite(A, LOW);
  // digitalWrite(B, HIGH);
  // digitalWrite(C, HIGH);
  // float cornerRightSensor = analogRead(MULTIPLEX_OUT);
  // Serial.print(cornerRightSensor); Serial.print(" ");

  // //0 0 1 //threshold 500
  // digitalWrite(A, LOW);
  // digitalWrite(B, LOW);
  // digitalWrite(C, HIGH);
  // float cornerLeftSensor = analogRead(MULTIPLEX_OUT);
  // Serial.print(cornerLeftSensor); Serial.print(" ");


  

  

  

  float previousError = error;



    // display.clearDisplay();
    // display.setFont(&FreeMono9pt7b);
    // display.setCursor(4,20);
    // display.print("L: "); display.println(leftSensor);
    // display.setCursor(4,50);
    // display.print("R: "); display.println(rightSensor);
    // display.display();


    if (rightSensor < DIFTHRESH && leftSensor < DIFTHRESH && middleSensor < DIFTHRESH) {
        if (previousError < 0){
            error = -4;
        } else {
            error = 4;
        }
    } else if (leftSensor < DIFTHRESH && middleSensor < DIFTHRESH){
      error = -2;
    } else if (leftSensor < DIFTHRESH) {
      error = -1;
    } else if (rightSensor < DIFTHRESH && middleSensor < DIFTHRESH) {
      error = 2;
    } else if (rightSensor < DIFTHRESH) {
      error = 1;
    } else {
      error = 0;
    }
    Serial.print(error);

    // Kp = (float) analogRead(KP_PIN);
    // Kd = (float) analogRead(KD_PIN);
    // if(abs(Kp-previous_Kp) > POT_THRESH || abs(Kd - previous_Kd) > POT_THRESH){
    //   display.clearDisplay();
    //   display.setFont(&FreeMono9pt7b);
    //   display.setCursor(4,20);
    //   display.print("KP: "); display.println(Kp);
    //   display.setCursor(4,50);
    //   display.print("KD: "); display.println(Kd);
    //   display.display();
    //   previous_Kp = Kp;
    //   previous_Kd = Kd;
    // }

    float p = HARDCODE_KP * error;
    float d = HARDCODE_KD * (error - previousError);
    // float d = 0;
    float g = (p + d);
    int left_motor_speed = REG_SPEED - g;
    left_motor_speed = constrain(left_motor_speed, 0, TPWM);
    int right_motor_speed = REG_SPEED + g;
    right_motor_speed = constrain(right_motor_speed, 0, TPWM);

    Serial.print(" ");
    Serial.print(left_motor_speed);
    Serial.print(" ");
    Serial.print(right_motor_speed);

    pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, left_motor_speed, 0);
    pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, right_motor_speed, 0);

    Serial.println();
 }
