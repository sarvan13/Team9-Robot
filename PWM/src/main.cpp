#include <Arduino.h>
#include <Wire.h>
#include <time.h>
#include <math.h>

#define CNTRL_PIN PA_1
#define FORWARD_PIN PA_7
#define REVERSE_PIN PA_6
#define TPWM 500
#define CLOCKF 100000
#define DIFTHRESH 5

float previousControl = 0.0;

void setup()
{
  Serial.begin(115200);

  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(CNTRL_PIN, INPUT_ANALOG);
  pinMode(FORWARD_PIN, OUTPUT);
  pinMode(REVERSE_PIN, OUTPUT);
}

void loop()
{
    
    float cntrl = analogRead(CNTRL_PIN);

    Serial.println(cntrl);

    if (abs(cntrl - previousControl) > DIFTHRESH) {
        if(cntrl < 512){
            pwm_start(REVERSE_PIN, CLOCKF, TPWM, (512-cntrl)/(512)*TPWM, 1);
            pwm_start(FORWARD_PIN, CLOCKF, TPWM, 0, 1);
        }
        else{
            pwm_start(FORWARD_PIN, CLOCKF, TPWM, (cntrl-512)/(512)*TPWM, 1);
            pwm_start(REVERSE_PIN, CLOCKF, TPWM, 0, 1);
        }
        
        previousControl = cntrl;
    } 

}