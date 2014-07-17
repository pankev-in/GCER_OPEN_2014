#include <Roomba.h>

Roomba roomba(&Serial1);

void setup()
{
//    Serial.begin(9600);
     
    roomba.start();
    roomba.fullMode();
}

void loop()
{
  // Serial.println("driveDirect");
  delay(1000);
  roomba.driveDirect(300 , 300);   // Often the first call after restart is not registered. This is an ongoing problem with no known fix.
  roomba.driveDirect(300 , 300);   // Left/Right Wheel velocity (mm/s)
  delay(1000);
  roomba.driveDirect(-300 , 300);  // Left/Right Wheel velocity (mm/s)
  delay(1000);
  roomba.driveDirect(300, -300);   // Left/Right Wheel velocity (mm/s)
  delay(1000);  
  roomba.driveDirect(0, 0);        // Left/Right Wheel velocity (mm/s)
  delay(2000);   

  // Serial.println("drive");  
  roomba.drive(300, 300);                   // Velocity (mm/s), Radius (mm)
  delay(1000);
  roomba.drive(300, -300);
  delay(1000);
  roomba.drive(300, roomba.DriveStraight);                  //DriveStraight is a special case. See Public Types in Roomba Class Reference
  delay(1000);
  roomba.drive(300, roomba.DriveInPlaceClockwise);
  delay(1000);
  roomba.drive(300, roomba.DriveInPlaceCounterClockwise);
  delay(1000);  
  roomba.drive(0, 0);
  delay(1000);
}
