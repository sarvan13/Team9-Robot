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
#define LEFT_REVERSE_PIN PA_6 //ORANGE WIRE
#define LEFT_FORWARD_PIN PA_7 //YELLOW WIRE
#define RIGHT_FORWARD_PIN PB_1 // red
#define RIGHT_REVERSE_PIN PB_0 //brown  
#define KP_PIN PA_3 //yellow
#define KD_PIN PA_2 //orange
#define TEST PB_13
#define TPWM 500
#define CLOCKF 100000
#define LEFT_SENSOR PA_5
#define RIGHT_SENSOR PA_4
#define MIDDLE_SENSOR PA_1

//KP 486   KD 109

#define DIFTHRESH 250
#define REG_SPEED 100
#define POT_THRESH 5


float previousError = 0;
float error = 0.0;

int count = 0;

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

float KPPrev = 0.0;
float KDPrev = 0.0;
void setup()
{
  Serial.begin(115200);
  

  // initialize LED digital pin as an output.
  pinMode(LEFT_FORWARD_PIN, OUTPUT);
  pinMode(LEFT_REVERSE_PIN, OUTPUT);
  pinMode(RIGHT_FORWARD_PIN, OUTPUT);
  pinMode(RIGHT_REVERSE_PIN, OUTPUT); 
  // pinMode(MULTIPLEX_OUT, INPUT_ANALOG);
  // pinMode(A,OUTPUT);
  // pinMode(B,OUTPUT);
  // pinMode(C,OUTPUT);
  pinMode(KP_PIN, INPUT);
  pinMode(KD_PIN, INPUT);
  pinMode(TEST, OUTPUT);
  pinMode(LEFT_SENSOR, INPUT_ANALOG);
  pinMode(RIGHT_SENSOR, INPUT_ANALOG);
  pinMode(MIDDLE_SENSOR, INPUT_ANALOG);


  

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("OLED Display 128x64");
  display.setFont(&FreeMono12pt7b);
  display.drawPixel(0,45,WHITE);
  display.setCursor(4,45);
  display.println("Welcome!");
  display.display();

  //start going forwards
  // digitalWrite(LEFT_FORWARD_PIN, HIGH);
  pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 1);
  pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 1);
  // pwm_start(PB_10, CLOCKF, TPWM, TPWM, 1);

  
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
  float leftSensor = analogRead(LEFT_SENSOR);
  float rightSensor = analogRead(RIGHT_SENSOR);
  float middleSensor = analogRead(MIDDLE_SENSOR);
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
            error = -5;
        } else {
            error = 5;
        }
    } else if (leftSensor < DIFTHRESH && middleSensor < DIFTHRESH){
      error = -3;
    } else if (leftSensor < DIFTHRESH) {
      error = -1;
    } else if (rightSensor < DIFTHRESH && middleSensor < DIFTHRESH) {
      error = 3;
    } else if (rightSensor < DIFTHRESH) {
      error = 1;
    } else {
      error = 0;
    }

    double KP = (float) analogRead(KP_PIN);
    double KD = (float) analogRead(KD_PIN);
    
    if (abs(KP - KPPrev) > POT_THRESH || abs(KD-KDPrev) > POT_THRESH) {
      display.clearDisplay();
      display.setFont(&FreeMono9pt7b);
      display.setCursor(4,20);
      display.print("KP: "); display.println(KP);
      display.setCursor(4,50);
      display.print("KD: "); display.println(KD);
      display.display();
      KPPrev = KP;
      KDPrev = KD;
      Serial.println("Hi");
    }
    Serial.println(KP);Serial.println(KD);

    float p = KP * error;
    float d = KD * (error - previousError);
    // float d = 0;
    float g = (p + d) / 15.0;

    if(error < 0){
      pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED - g/2, 0);
      pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED + g/2, 0);
      // Serial.println("goes right");
      // Serial.println(g);
    }else if(error > 0){
      pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED - g/2, 0);
      pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED + g/2, 0);
      // Serial.println("goes left");
      // Serial.println(g);
    }else {
      pwm_start(LEFT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 0);
      pwm_start(RIGHT_FORWARD_PIN, CLOCKF, TPWM, REG_SPEED, 0);
      // Serial.println(TPWM); Serial.println(REG_SPEED);
    }
 }
