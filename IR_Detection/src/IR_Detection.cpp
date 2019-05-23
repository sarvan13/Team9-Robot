#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <FreeMono12pt7b.h>
#include <time.h>
#include <math.h>


// Set LED_BUILTIN if it is not defined by Arduino framework
// #define LED_BUILTIN 13
#define IN_PIN PA5
#define NUM_SAMPLES 200
#define THRESHOLD_10K 3
#define THRESHOLD_1K 20

#define OLED_RESET -1  // Not used
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

float raw_in[NUM_SAMPLES];
float tenK[NUM_SAMPLES * 2];
float oneK[NUM_SAMPLES * 2];

void setup()
{
  Serial.begin(115200);

  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(IN_PIN, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)  
  display.clearDisplay();
  display.setTextSize(1);
  display.setFont(&FreeMono12pt7b);
  display.setTextColor(WHITE);
  display.display();
}

void loop()
{
  unsigned long startTime = micros();
  float sum = 0;
  for(int i = 0; i < NUM_SAMPLES; i++) {
    raw_in[i] = analogRead(IN_PIN);
    sum += raw_in[i];
  }

  // Sample period in milliseconds
  float samplePeriod = (float) (micros() - startTime) / NUM_SAMPLES;
  float rawAvg =  sum / NUM_SAMPLES;

  // Subtract average from raw signal
  for (int i=0; i < NUM_SAMPLES; i++) {
    raw_in[i] = (raw_in[i] - rawAvg) / rawAvg;
  }

  // // Calculate intensity using RMS voltage
  // sum = 0;
  // for (int i=0; i < NUM_SAMPLES; i++) {
  //   sum += raw_in[i] * raw_in[i];
  // }
  // float intensity = sqrt(sum / NUM_SAMPLES);

  for(int i = 0; i < 400; i++) {
    tenK[i] = sin(2 * PI * pow(10,4) * i * samplePeriod / 1000000);
  }
  for(int i = 0; i < 400; i++) {
    oneK[i] = sin(2 * PI * pow(10,3) * i * samplePeriod / 1000000);
  }
  
  float corrTenMax = 0;
  float corrOneMax = 0;
  for(int n = 0; n < 200; n++) {
    float corrTen = 0;
    float corrOne = 0;
    for(int i = 0; i < 200; i++) {
      corrTen += raw_in[i] * tenK[i+n];
      corrOne += raw_in[i] * oneK[i+n];
    }
    if(corrTen > corrTenMax ) {
      corrTenMax = corrTen;
    }
    if(corrOne > corrOneMax) {
      corrOneMax = corrOne;
    }
  }

  display.clearDisplay();
  display.setCursor(0,45);
  if(corrTenMax > THRESHOLD_10K) {
    display.println("10K Hz");
  } else if (corrOneMax > THRESHOLD_1K) {
    display.println("1k Hz");
  } else {
    display.println("NO SIGNAL");
  }
  display.display();

  Serial.print("Corr 1 Max: ");
  Serial.println(corrOneMax);
  Serial.print("Corr 10 Max: ");
  Serial.println(corrTenMax);
  Serial.print("Sample period: ");
  Serial.println(samplePeriod);
  delay(100);
}
