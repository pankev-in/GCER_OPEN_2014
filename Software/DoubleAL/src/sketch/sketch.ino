#include <Roomba.h>

Roomba roomba(&Serial1);

void setup()
{
    roomba.start();
    roomba.safeMode();
}

void loop()
{
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
}
