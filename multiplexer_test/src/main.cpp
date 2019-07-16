#include <Arduino.h>

#define A PB9
#define B PB8
#define C PB7
#define IN_0 PA1
#define IN_1 PA2
#define IN_2 PA3
#define MULTIPLEX_OUT PA0

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(IN_0, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT); 
  pinMode(MULTIPLEX_OUT, INPUT_ANALOG);
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(IN_0, LOW);
  digitalWrite(IN_1, HIGH);

  digitalWrite(IN_2, HIGH);

}

void loop() {
  Serial.print("MULTIPLEX OUTPUT 1: ");
 int multiplexOut = analogRead(MULTIPLEX_OUT);
 Serial.println(multiplexOut);

 delay(1000);

//   digitalWrite(A, LOW);
//   digitalWrite(B, LOW);
//   digitalWrite(C, HIGH);

//  Serial.print("MULTIPLEX OUTPUT 2: ");
//  multiplexOut = analogRead(MULTIPLEX_OUT);
//  Serial.println(multiplexOut);

// delay(1000);

//   digitalWrite(A, LOW);
//   digitalWrite(B, HIGH);
//   digitalWrite(C, LOW);

//   Serial.print("MULTIPLEX OUTPUT 3: ");
//  multiplexOut = analogRead(MULTIPLEX_OUT);
//  Serial.println(multiplexOut);

//  delay(1000);


}