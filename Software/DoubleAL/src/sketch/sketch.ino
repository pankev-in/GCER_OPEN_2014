#include <Roomba.h>

// Defines the Roomba instance and the HardwareSerial it connected to:
// &Serial1 (Arduino Mega only), Default Bandrate: 57600
Roomba roomba(&Serial1);


//SensorPins:
int LightSensorPin=0;

//constance:
int lightValue=650;

//variables
int light=0;
int distance=0;
unsigned int u;
int x;

void setup()
{
  Serial.begin(57600);          // baud rate of serial monitor
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
    Serial.println(i);
    roomba.driveDirect(i,i);
    delay(500);
  }

  uint8_t buf[2];
  while(roomba.getSensors(29,buf,2)){            // packetID, destination, length (bytes) 
    u = BitShiftCombine(buf[0], buf[1]);        // Value sent as 16 bit signed value high byte first.
      if(u>=2000){break;}
    delay(500);
   }
  roomba.driveDirect(0,0);
  
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



