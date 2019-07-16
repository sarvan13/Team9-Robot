// //I2C Slave Code (Arduino)
// //I2C Communication between STM32 and Arduino
// //Circuit Digest


// #include<Wire.h>                             //Library for I2C Communication functions

// #define LED LED_BUILTIN
// #define buttonpin PA0

// void receiveEvent(int howMany);
// void requestEvent();

// byte x =0;
// void setup() 
// {
//   Serial.begin(115200);                        //Begins Serial Communication at 9600 baud rate
//   pinMode(LED,OUTPUT);                       //Sets pin 7 as output
//   pinMode(buttonpin, INPUT);
//   Wire.begin(8);                             // join i2c bus with its slave Address as 8 at pin (A4,A5)
//   Wire.onReceive(receiveEvent);              //Function call when Slave Arduino receives value from master STM32
//   Wire.onRequest(requestEvent);              //Function call when Master STM32 request value from Slave Arduino
// }

// void loop() 
// {
  
//   delay(800);
// }

// void receiveEvent (int howMany)              //This Function is called when Slave Arduino receives value from master STM32
// {
//   byte a = Wire.read();                      //Used to read value received from master STM32 and store in variable a
//  Serial.println(a);
//   // if (a == 1)                                //Logic to turn Slave LED ON (if received value is 1) or OFF (if received value is 0)
//   // {
//   //  digitalWrite(LED,HIGH);
//   //  Serial.println("Slave LED ON");
   
//   // }
//   // else
//   // {
//   //   digitalWrite(LED,LOW);
//   //   Serial.println("Slave LED OFF");
//   // }
//   delay(500);
  
// }

// void requestEvent()                            //This Function is called when Master STM32 wants value from slave Arduino
// {
//   // int value = digitalRead(buttonpin);          //Reads the status of the pin 2   
//   // if (value == HIGH)                           //Logic to set the value of x to send to master depending upon input at pin 2
//   // {
//   //   x=1;
//   // }
//   // else 
//   // {
//   //   x=0;
//   // }
//   Serial.println("Hello");
//   Wire.write(11);                             // sends one byte of x value to master STM32
// }
  
