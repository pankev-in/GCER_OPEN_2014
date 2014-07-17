#include <Roomba.h>
#include <Servo.h>
#include <Motor.h>
#include <Robot_Arm.h>


//static pin connections:
int M1_Pins[]={4,50,51};
int M2_Pins[]={5,52,53};
int S1Pin=6;
int S2Pin=7;
int S3Pin=8;
int lightPin=0;
int Pot1Pin=1;
int Pot2Pin=2;

//constant sensor values:
int lightValue = 43;

//Object arm and roomba:
Robot_Arm arm(M1_Pins,M2_Pins,S1Pin,S2Pin,S3Pin,Pot1Pin,Pot2Pin);
Roomba roomba(&Serial1);

void setup() {
  Serial.begin(57600);          // baud rate of serial monitor
  //roomba.start();
  //roomba.fullMode();
  //roomba.safeMode();
}

void loop() {
  /*
  Position adjusting and wait for light
  
  Serial.println("Robot Started, adjesting position...");
  roomba.driveDirect(-100, -100);
  delay(2000);
  roomba.driveDirect(0, 0);                                   //Roomba stops moving
  Serial.println("Position adjested.");
  Serial.println("Waiting for the light Signal...");
  /*
  int light = analogRead(lightPin);
  while (light <= lightValue) {
    light = analogRead(lightPin);
    Serial.println(light);
    delay(50);
  }*/
  
  

  while(true){
    arm.CloseGrab();
    delay(1000);
    arm.OpenGrab();
    delay(1000);
  }
}


void turnLeft(){}

void turnRight(){}

void upPosition(){}

void downPosition(){}

void getDownHangerFront(){}

void getDownHangerbBack(){}


