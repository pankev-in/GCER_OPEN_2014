#include <Roomba.h>
#define NUM_ROOMBA_TURN_SPEED 213

Roomba roomba (&Serial1);

void setup()
{
	Serial.begin(9600);
	roomba.start();
    roomba.safeMode();
}

void loop()
{
turnRight();
roomba.driveDirect(-200, -200);
delay(5000);
roomba.driveDirect(0, 0);
while(true){delay(1000);}
}

void turnRight() {
    
    roomba.drive(NUM_ROOMBA_TURN_SPEED, roomba.DriveInPlaceClockwise);
    delay(1000);
    roomba.driveDirect(0, 0);
}

// Roomba Creat turns left(Inclock wise):
// Status: TESTED
void turnLeft() {
    
    roomba.drive(NUM_ROOMBA_TURN_SPEED, roomba.DriveInPlaceCounterClockwise);
    delay(1000);
    roomba.driveDirect(0, 0);
}

// Roomba Creat turns 180(Clock wise):
// Status: TESTED
void turnAround() {
    
    roomba.drive(NUM_ROOMBA_TURN_SPEED, roomba.DriveInPlaceClockwise);
    delay(2000);
    roomba.driveDirect(0, 0);
}


