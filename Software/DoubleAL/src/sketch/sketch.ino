#include <Roomba.h>
#include <Servo.h>

// Defines the Roomba instance and the HardwareSerial it connected to:
// &Serial1 (Arduino Mega only), Default Bandrate: 57600
Roomba roomba(&Serial1);


//SensorPins:
int LightSensorPin=0;
Servo Servo1;
Servo Servo2;

//constance:
int lightValue=650;

//variables
int light=0;
int distance=0;
int Servo1_StartValue=100;
int Servo2_StartValue=110;
unsigned int u;
int x;

void setup()
{
  Serial.begin(57600);          // baud rate of serial monitor
  Servo1.attach(6);
  Servo2.attach(7);
  roomba.start();
  roomba.fullMode();
  //roomba.safeMode();
}

void loop()
{
  
  
  
  /*
    Position adjusting and wait for light
  */
  Serial.println("Robot Started, adjesting position...");
  roomba.driveDirect(-100,-100);
  delay(2000);
  roomba.driveDirect(0,0);
  MainArm_Startposition();
  Serial.println("Position adjested.");
  Serial.println("Waiting for the light Signal...");
  while(light<=lightValue){
    light=analogRead(LightSensorPin);
    Serial.println(light);
    delay(500);
  }
  
  
  
  
  /*
    Start moving
  */
  Serial.println("\n\nStarts running...");
  for(int i=50;i<=350;i=i+50){
    Serial.print("Speed:");
    Serial.println(i);
    roomba.driveDirect(i,i);
    delay(500);
  }


  /*
    goes to the blacktape
  */
  Serial.println("Finding Black tape");
  uint8_t buf[2];
  while(roomba.getSensors(29,buf,2)){              //PacketID for left front cliff=29, 2 byte data      
      u = BitShiftCombine(buf[0], buf[1]);        
      if(u>=200){break;}                           //Black tape value
      Serial.print("Value:");
      Serial.println(u);
    delay(100);
   }
  roomba.driveDirect(0,0);                         //Stops moving and delays for 0.5s
  delay(500);
  turnLeft();                                      //turns 90 Degrees

  
  /*
    
  */
  
  
  
  while(true){
    Serial.println("Stoped Moving");
    delay(1000);
  }
  
}

int BitShiftCombine( unsigned char x_high, unsigned char x_low)
{


  int combined;  
  combined = x_high;              //send x_high to rightmost 8 bits
  combined = combined<<8;         //shift x_high over to leftmost 8 bits
  combined |= x_low;                 //logical OR keeps x_high intact in combined and fills in rightmost 8 bits 
  return combined;

}

void turnLeft(){
     roomba.drive(225, roomba.DriveInPlaceCounterClockwise);
     delay(1000);
     roomba.driveDirect(0,0);
}

void turnRight(){
    roomba.drive(225,roomba.DriveInPlaceClockwise);
    delay(1000);  
    roomba.driveDirect(0,0);
}

void MainArm_RightUp(){
    Servo1.write(Servo1_StartValue-45);
    Servo2.write(Servo2_StartValue+45);
}

void MainArm_LeftUp(){
    Servo1.write(Servo1_StartValue+45);
    Servo2.write(Servo2_StartValue-45);
}

void MainArm_Startposition(){
    Servo1.write(Servo1_StartValue);
    Servo2.write(Servo2_StartValue);
}

