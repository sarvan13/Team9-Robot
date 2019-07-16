// //I2C Master Code (STM32F103C8)
// //I2C Communication between STM32 and Arduino
// //Circuit Digest
// // #include <Arduino.h>
// // #include <stdint.h>
// // #include "PinNames.h"
// #include<Wire.h>                      
// // #include<SoftWire.h>                   //Library for I2C Communication functions

// #define LED LED_BUILTIN
// #define buttonpin PA0

// // #define BPILL_ADDRESS 5

// int x = 0;

// void setup() 
// { 
  
//   Serial.begin(115200);                  //Begins Serial Communication at 9600 baud rate
//   pinMode(buttonpin,INPUT);            //Sets pin PA0 as input 
//   pinMode(LED,OUTPUT);                 //Sets PA1 as Output
//   Wire.begin();           
//            //Begins I2C communication at pin (B6,B7)
// }

// void loop()
// { 
   
//     Wire.requestFrom(8,1,1);               // request  bytes from slave arduino(8)
//     delay(500);
//     Serial.println(Wire.available());
//     delay(500);
//     byte a = Wire.read();                // receive a byte from the slave arduino and store in variable a
//     Serial.println(a);
//     // if (a==1)                            //Logic to turn Master LED ON (if received value is 1) or OFF (if received value is 0)
//     //   { 
//     //   digitalWrite(LED,HIGH);
//     //   Serial.println("Master LED ON");
//     //   }
//     // else
//     //   {
//     //   digitalWrite(LED,LOW);
//     //   Serial.println("Master LED OFF");
//     //   }
//   {
   
//   //  int pinvalue = digitalRead(buttonpin);    //Reads the status of the pin PA0
   
  
//   // if(pinvalue==HIGH)                         //Logic for Setting x value (To be sent to slave Arduino) depending upon inuput from pin PA0
//   //   {
//   //     x=1;
//   //   }
    
//   // else
//   //  {
//   //     x=0;
//   //  }
 
  
//   // Wire.beginTransmission(8);                 // starts transmit to device (8-Slave Arduino Address)
//   // Wire.write(13);                             // sends the value x to Slave
//   //  Wire.endTransmission();                    // stop transmitting
  
//   // delay(500);
//   }
// }   

// //I2C Master Code (STM32F103C8)
// //I2C Communication between STM32 and Arduino
// //Circuit Digest

// #include<Wire.h>                      
// // #include<SoftWire.h>                   //Library for I2C Communication functions

// #define LED PA1
// #define buttonpin PA0

// int x = 0;

// void setup() 
// { 
  
//   Serial.begin(115200);                  //Begins Serial Communication at 9600 baud rate
//   pinMode(buttonpin,INPUT);            //Sets pin PA0 as input 
//   pinMode(LED,OUTPUT);                 //Sets PA1 as Output
//   Wire.begin();                        //Begins I2C communication at pin (B6,B7)
// }

// void loop()
// { 
//     Wire.requestFrom(8,1);               // request  bytes from slave arduino(8)
//     delay(500);
//     byte a = Wire.read();                // receive a byte from the slave arduino and store in variable a
//     delay(500);
//     Serial.println(Wire.available());
//     Serial.println(a);
//     // if (a==1)                            //Logic to turn Master LED ON (if received value is 1) or OFF (if received value is 0)
//     //   { 
//     //   digitalWrite(LED,HIGH);
//     //   Serial.println("Master LED ON");
//     //   }
//     // else
//     //   {
//     //   digitalWrite(LED,LOW);
//     //   Serial.println("Master LED OFF");
//     //   }
//   // {
   
//   //  int pinvalue = digitalRead(buttonpin);    //Reads the status of the pin PA0
   
  
//   // if(pinvalue==HIGH)                         //Logic for Setting x value (To be sent to slave Arduino) depending upon inuput from pin PA0
//   //   {
//   //     x=1;
//   //   }
    
//   // else
//   //  {
//   //     x=0;
//   //  }
  
//   // Wire.beginTransmission(8);                 // starts transmit to device (8-Slave Arduino Address)
//   // Wire.write(x);                             // sends the value x to Slave
//   // Wire.endTransmission();                    // stop transmitting
//   // delay(500);
//   // }
// }   