// #include <PID.h>
// #include <Arduino.h>
// #include <Wire.h>
// #include <time.h>
// #include <math.h>
// #include <Adafruit_SSD1306.h>
// #include <FreeMono12pt7b.h>
// #include <FreeMono9pt7b.h>
// #include <stdint.h>
// #include "PinNames.h"

// #define OLED_RESET -1
// Adafruit_SSD1306 display(OLED_RESET);

// // #define KP_PIN PA_3 //yellow
// // #define KD_PIN PA_2 //orang

// #define POT_THRESH 5

// PID::PID(){
//   // pinMode(KP_PIN, INPUT);
//   // pinMode(KD_PIN, INPUT);

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
// }

// void PID::read_K_values(){
//     // Kp = analogRead(KP_PIN);
//     // Kd = analogRead(KD_PIN);

//      if (abs(Kp - Kp_prev) > POT_THRESH || abs(Kd-Kd_prev) > POT_THRESH) {
//       display.clearDisplay();
//       display.setFont(&FreeMono9pt7b);
//       display.setCursor(4,20);
//       display.print("KP: "); display.println(Kp);
//       display.setCursor(4,50);
//       display.print("KD: "); display.println(Kd);
//       display.display();
//       Kp_prev = Kp;
//       Kd_prev = Kd;
//       Serial.println("Hi");
//     }
//     Serial.println(Kp);Serial.println(Kd);
// }

// float PID::get_Kp(){
//     return Kp;
// }

// float PID::get_Kd(){
//     return Kd;
// }