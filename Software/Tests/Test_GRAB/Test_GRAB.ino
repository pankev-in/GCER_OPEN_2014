#include <Servo.h>

Servo SERVO_GRAB;
#define NUM_SERVO_GRAB_CLOSE 20
#define NUM_SERVO_GRAB_OPEN 100
#define SERVO_GRAB_PIN  8

void setup(){
  SERVO_GRAB.attach(SERVO_GRAB_PIN);
}

void loop(){
  OpenGrab();
  delay(1000);
  CloseGrab();
  delay(1000);
}

void OpenGrab(){
  SERVO_GRAB.write(NUM_SERVO_GRAB_OPEN);
}

// Open the grabbler:
// Status: Untested
void CloseGrab(){
  SERVO_GRAB.write(NUM_SERVO_GRAB_CLOSE);
}


