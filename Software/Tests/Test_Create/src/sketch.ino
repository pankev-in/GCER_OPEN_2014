#include <Roomba.h>

Roomba roomba (&Serial1);

void setup()
{
	Serial.begin(9600);
	roomba.start();
    roomba.safeMode();
}

void loop()
{
roomba.driveDirect(-200, -200);
delay(5000);
roomba.driveDirect(0, 0);
while(true){delay(1000);}
}
