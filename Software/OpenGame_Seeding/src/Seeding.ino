/*
 	Program: GCER 2014 OPEN GAME - Double Al.
 	Member: Kalus Ableitinger , Kevin Pan
 	Date: 07.2014
*/

//External libraries:
#include <Roomba.h>
#include <Servo.h>
#include <Motor.h>

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
#define NUM_SERVO_GRAB_CLOSE 0
#define NUM_SERVO_GRAB_OPEN 100
#define NUM_POTENTIOMETER_1_ZERO_DEGREE 330
#define NUM_POTENTIOMETER_1_MAX_ANGLE 108
#define NUM_POTENTIOMETER_1_MIN_ANGLE -98
#define NUM_POTENTIOMETER_2_ZERO_DEGREE 310
#define NUM_POTENTIOMETER_2_MAX_ANGLE 115
#define NUM_POTENTIOMETER_2_MIN_ANGLE -93
#define NUM_ROOMBA_TURN_SPEED 213
#define NUM_LIGHT_SENSOR_VALUE 40
#define NUM_CLIFF_BLACKTAPE_VALUE 200

//Objects define:
Roomba roomba (&Serial1);
Servo SERVO_FRONT;
Servo SERVO_BACK;
Servo SERVO_GRAB;
Servo SERVO_DEFENCE;
Motor m1;
Motor m2;

unsigned int u;

void setup() {
    
    Serial.begin(9600);
    Serial.println("Serial communication established");
    SERVO_FRONT.attach(SERVO_FRONT_PIN);
    SERVO_BACK.attach(SERVO_BACK_PIN);
    SERVO_GRAB.attach(SERVO_GRAB_PIN);
	SERVO_DEFENCE.attach(SERVO_DEFENSE_PIN);
	m1.attach(M1_EN_PIN, M1_INA_PIN, M1_INB_PIN);
	m2.attach(M2_EN_PIN, M2_INA_PIN, M2_INB_PIN);
    roomba.start();
    roomba.safeMode();
}

void loop() {
	secondaryArmPosition(-90);
	grabBasePosition(0);
	primaryArmPosition(10);
	SERVO_DEFENCE.write(180);
	openGrab();

	Serial.println("aligning at gametable..");
	roomba.driveDirect(-150,-150);
	delay(4000);
	roomba.driveDirect(150,150);
	delay(1500);
	turnRight();
    roomba.driveDirect(-150, -150);
 
  
	Serial.println("aligned");    
    delay(1000);
    
    roomba.driveDirect(0, 0);
   	
    Serial.println("waiting for light...");
//    while(analogRead(LIGHT_SENSOR_PIN) > NUM_LIGHT_SENSOR_VALUE) delay(10);
    Serial.println("Go!");
    
    roomba.driveDirect(300, 300);
    uint8_t buf[2];
    while(roomba.getSensors(29, buf, 2)) {
        u = bitShiftCombine(buf[0], buf[1]);
        if(u < 500) {
            break;
        }
    }
 	roomba.driveDirect(0,0);
    turnLeft();
	grabBasePosition(45);
	secondaryArmPosition(-40);
	roomba.driveDirect(200,200);
	delay(4000);
	roomba.driveDirect(0,0);


	SERVO_FRONT.detach();
	SERVO_BACK.detach();
	SERVO_DEFENCE.detach();	
	SERVO_GRAB.detach();

	delay(5000);
	robotComeBack();
	while(true){delay(1000);}

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

void robotComeBack(){
	roomba.driveDirect(300,300);
	delay(2500);
	turnRight();
	roomba.driveDirect(-150,-150);
	delay(6000);
	roomba.driveDirect(0,0);
	roomba.driveDirect(150,150);
	delay(500);
	roomba.driveDirect(0,0);
	turnLeft();
}

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
	
	if(angle > NUM_POTENTIOMETER_1_MAX_ANGLE || angle < NUM_POTENTIOMETER_1_MIN_ANGLE){		//Check if the input angle is posible
		return;
	}
	int diff =angle - checkSecondaryArmAngle();		//calculate the difference
	if(diff<5&&diff>-5){
		Serial.println("Secondary Arm is not going to turn.");
		Serial.print("Diff:");Serial.println(diff);
	}
	else if(diff>0){
		m1.forward(255);
	}
	else if(diff<0){
		m1.backward(255);
	}
	while(diff>5||diff<-5){
        diff =angle - checkSecondaryArmAngle();
	}
    m1.brake();
}

// Turn the Grabber in to an specific angle between -110 to 110 degree:
// Status: Untested
void grabBasePosition(int angle) {
	
	if(angle > NUM_POTENTIOMETER_2_MAX_ANGLE || angle < NUM_POTENTIOMETER_2_MIN_ANGLE){		//Check if the input angle is posible
		return;
	}
	int diff =angle - checkGrabAngle();		//calculate the difference
	if(diff<5&&diff>-5){
		Serial.println("Grab is not going to turn.");
		Serial.print("Diff:");Serial.println(diff);
	}
	else if(diff<0){
		m2.backward(200);       //Here is Backward!!!!
	}
	else if(diff>0){
		m2.forward(200);
	}
	while(diff>5||diff<-5){
        diff =angle - checkGrabAngle();
	}
    m2.brake();
}

// Returns the Angle of the grabbler:
// Status: TESTED
int checkGrabAngle() {
    
   	int value=analogRead(POTENTIOMETER_2_PIN);
	value=map(value,0,697,NUM_POTENTIOMETER_2_MIN_ANGLE,NUM_POTENTIOMETER_2_MAX_ANGLE);
  	return value;
}

// Returns the Angle of the secondary Arm:
// Status: TESTED
int checkSecondaryArmAngle(){
   	int value=analogRead(POTENTIOMETER_1_PIN);
   	value=map(value,0,697,NUM_POTENTIOMETER_1_MIN_ANGLE,NUM_POTENTIOMETER_1_MAX_ANGLE);
   	return value;}

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



