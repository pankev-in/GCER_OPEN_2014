#include <Arduino.h>
#include <Roomba.h>
#include <Servo.h>
#include <Motor.h>
void setup();
void loop();
void turnRight();
void turnLeft();
void turnAround();
int bitShiftCombine( unsigned char x_high, unsigned char x_low);
void primaryArmPosition(int Angle);
void secondaryArmPosition(int angle);
void grabBasePosition(int angle);
int checkGrabAngle();
int checkSecondaryArmAngle();
void openGrab();
void closeGrab();
bool checkGrabTouch();
#line 1 "src/Seeding.ino"
/*
 	Program: GCER 2014 OPEN GAME - Double Al.
 	Member: Kalus Ableitinger , Kevin Pan
 	Date: 07.2014
*/

//External libraries:
//#include <Roomba.h>
//#include <Servo.h>
//#include <Motor.h>

//Pin connections:
#define M1_EN_PIN 2
#define M1_INA_PIN 22
#define M1_INB_PIN 23
#define M2_EN_PIN 3
#define M2_INA_PIN 24
#define M2_INB_PIN  25
#define SERVO_FRONT_PIN  4
#define SERVO_BACK_PIN  5
#define SERVO_GRAB_PIN  6
#define SERVO_DEFENSE_PIN 7
#define LIGHT_SENSOR_PIN  0
#define POTENTIOMETER_1_PIN  1
#define POTENTIOMETER_2_PIN  2

//Constants:
#define NUM_SERVO_FRONT_ZERO_DEGREE 90
#define NUM_SERVO_BACK_ZERO_DEGREE 95
#define NUM_SERVO_GRAB_CLOSE 20
#define NUM_SERVO_GRAB_OPEN 100
#define NUM_POTENTIOMETER_1_ZERO_DEGREE 500
#define NUM_POTENTIOMETER_2_ZERO_DEGREE 450
#define NUM_ROOMBA_TURN_SPEED 213
#define NUM_LIGHT_SENSOR_VALUE 40
#define NUM_CLIFF_BLACKTAPE_VALUE 200

//Objects define:
Roomba roomba (&Serial1);
Servo SERVO_FRONT;
Servo SERVO_BACK;
Servo SERVO_GRAB;
Motor m1;
Motor m2;

void setup() {
    
    Serial.begin(57600);
    Serial.println("Serial communication established");
	/*
    SERVO_FRONT.attach(SERVO_FRONT_PIN);
    SERVO_BACK.attach(SERVO_BACK_PIN);
    SERVO_GRAB.attach(SERVO_GRAB_PIN);
    m1.attach(M1_EN_PIN, M1_INA_PIN, M1_INB_PIN);
    m2.attach(M2_EN_PIN, M2_INA_PIN, M2_INB_PIN);
	*/
    roomba.start();
    roomba.safeMode();
    //roomba.fullMode();
}

void loop() {
	/*
    Serial.println("aligning at gametable..");
    romba.driveDirect(-50, -50);
    
	primaryArmPosition(0);
    secondaryArmPosition(120);
    
    delay(2000);
    
    roomba.driveDirect(0, 0);
    
    Serial.println("waiting for light...");
    while(analogRead(LIGHT_SENSOR_PIN) > NUM_LIGHT_SENSOR_VALUE) delay(10);
    Serial.println("Go!");
    
    roomba.driveDirect(150, 150);
    
    uint8_t buf[2];
    while(roomba.getSensors(29, buf, 2)) {
        
        u = bitShiftCombine(buf[0], buf[1]);
        if(u >= 200) {
            
            break;
        }
        
        Serial.print("cliff value: ");
        Serial.println(u);
        delay(100);
    }
    */
    turnLeft();
    turnRight();
	//while (true){delay(1000);}
}

/*
########################################
	METHOD: ROOMBA SENSOR
########################################
*/

/*
########################################
	METHOD: ROOMBA DRIVE
########################################
*/

// Roomba Creat turns Right(Clock wise):
// Status: TESTED
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

/*
########################################
	METHOD: OTHER
########################################
*/

// Shifting two unsigned int* together, Need for sensor data read:
// Status: TESTED
int bitShiftCombine( unsigned char x_high, unsigned char x_low) {
    
    int combined;
    combined = x_high;             	 //send x_high to rightmost 8 bits
    combined = combined << 8;     	 //shift x_high over to leftmost 8 bits
    combined |= x_low;               //logical OR keeps x_high intact in combined and fills in rightmost 8 bits
    return combined;
}

/*
########################################
	METHOD: THE ROBOT ARM
########################################
*/

// Turn Primary arm in to an specific angle between -45 to 45 degree:
// Status: TESTED
void primaryArmPosition(int Angle) {
    
  if(Angle > 45||Angle < -45) return;
  else{
      
	SERVO_FRONT.write(NUM_SERVO_FRONT_ZERO_DEGREE - Angle);
 	SERVO_BACK.write(NUM_SERVO_BACK_ZERO_DEGREE + Angle);
  }
}

// Turn Secondary arm in to an specific angle between -110 to 110 degree:
// Status: Untested
void secondaryArmPosition(int angle){

    if(angle > 110 || angle < -110) return;

    int dif = angle - checkSecondaryArmAngle();

    if(dif < 0) {
    
        m1.backward(100);
    } else if(dif > 0) {
      
        m1.forward(100);
    } else return;

    while(angle - checkSecondaryArmAngle() > 5) delay(10);
    m1.brake();
}

// Turn the Grabber in to an specific angle between -110 to 110 degree:
// Status: Untested
void grabBasePosition(int angle) {
    
    if(angle > 110 || angle < -110) return;

    int dif = angle - checkGrabAngle();

    if(dif < 0) {
       
        m2.backward(100);
    } else if(dif > 0) {
        
        m1.forward(100);
    } else return;
		     
    while(angle - checkSecondaryArmAngle() > 5) delay(10);
    m1.brake();
}

// Returns the Angle of the grabbler:
// Status: TESTED
int checkGrabAngle() {
    
    int value = analogRead(POTENTIOMETER_2_PIN);
    value = int((value-NUM_POTENTIOMETER_2_ZERO_DEGREE) / (1023 / 230));
    return value;
}

// Returns the Angle of the secondary Arm:
// Status: TESTED
int checkSecondaryArmAngle(){
    
    int value = analogRead(POTENTIOMETER_1_PIN);
    value = int((value-NUM_POTENTIOMETER_1_ZERO_DEGREE) / (1023 / 230));
    return value;
}

// Open the grabbler:
// Status: TESTED
void openGrab(){
    
  SERVO_GRAB.write(NUM_SERVO_GRAB_OPEN);
}

// Open the grabbler:
// Status: TESTED
void closeGrab(){
    
  SERVO_GRAB.write(NUM_SERVO_GRAB_CLOSE);
}

bool checkGrabTouch() {
    
    return false;
}



