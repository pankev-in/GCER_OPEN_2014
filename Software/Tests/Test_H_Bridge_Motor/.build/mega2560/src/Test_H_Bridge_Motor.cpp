#include <Arduino.h>

void setup();
void loop();
#line 1 "src/Test_H_Bridge_Motor.ino"
/******************************************************************************************************\
 Code for Arduino to test out the operation of the L298 motor driver. A single motor between OUT1 and
 OUT2 is controlled. A standard HD44780 LCD is used to display information.
 Source code provided by Zapterra Systems.
\******************************************************************************************************/
 
const int ENA = 2;
const int IN1 = 22;
const int IN2 = 23;

void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

}
 
void loop()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);  
  delay(1000);
  digitalWrite (IN1, LOW); //Switch direction
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 255);  
  delay(1000);
}
