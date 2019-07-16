/*
 * Test OLED display 1306 pixel size 128x64, 0.96 inch
 * Interface I2C
 * Important! Define SSD1306_128_64 in Adafruit_SSD1306.h
 * 
 * Wiring: SCLK  .. B6
 *         SDA   .. B7
 *         
 *         
 */

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <FreeMono12pt7b.h>

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//------------

#define OLED_RESET -1  // Not used
Adafruit_SSD1306 display(OLED_RESET);


//------------
void setup() {
  // Serial.begin(115200);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done

  // Clear the buffer.
  display.clearDisplay();

  // Draw a test
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
}

//------------
void loop() {
  // put your main code here, to run repeatedly:

}