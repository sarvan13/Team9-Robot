#include <Arduino.h>


// char onMessage[] = "ON";
// char offMessage[] = "OFF";
// char recieve[3];

// Sending Blue Pill

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  Serial.write('Z');
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
}



// //Recieving Blue Pill

// void setup() {
//   Serial.begin(115200);
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, HIGH);
// }

// void loop() {
//   if (Serial.available() > 0) {
//     char incoming = Serial.read();
//     if (incoming == 'Z') {
//       digitalWrite(LED_BUILTIN, LOW);
//       delay(250);
//       digitalWrite(LED_BUILTIN, HIGH);
//       delay(250);
//     }
//   }
// }

/*
    int i = 0;
  digitalWrite(PB9, LOW);

  if (Serial.available() > 0){
  //  delay (100);
    while ((Serial.available() > 0) && i < 3){
      recieve[i++] = Serial.read();
      digitalWrite(PB9, HIGH);
    }
  }

  if (i > 0){
    if (recieve[0] == 'O' && recieve[1] == 'N'){
      digitalWrite(LED_BUILTIN, LOW);
    }
    else if (recieve[0] == 'O' && recieve[1] == 'F' && recieve[2] == 'F'){
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  else{
    digitalWrite(LED_BUILTIN, HIGH);
  }

 */