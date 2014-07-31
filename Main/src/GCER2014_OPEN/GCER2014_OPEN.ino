//
//  GCER OPEN GAME 2014
//
//
//  Created by Kevin Pan on 7/27/14.
//
//

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
#define LIGHT_SENSOR_PIN A0
#define POTENTIOMETER_1_PIN  A1
#define POTENTIOMETER_2_PIN  A2
//Constants:
#define NUM_SERVO_FRONT_ZERO_DEGREE 80
#define NUM_SERVO_BACK_ZERO_DEGREE 95
#define NUM_SERVO_GRAB_CLOSE 180
#define NUM_SERVO_GRAB_OPEN 0
#define NUM_SERVO_DEFENCE_MAX 150
#define NUM_SERVO_DEFENCE_MIN 35
#define NUM_POTENTIOMETER_1_ZERO_DEGREE 330
#define NUM_POTENTIOMETER_1_MAX_ANGLE 108
#define NUM_POTENTIOMETER_1_MIN_ANGLE -98
#define NUM_POTENTIOMETER_2_ZERO_DEGREE 310
#define NUM_POTENTIOMETER_2_MAX_ANGLE 115
#define NUM_POTENTIOMETER_2_MIN_ANGLE -93
#define NUM_ROOMBA_TURN_SPEED 213
#define NUM_LIGHT_SENSOR_VALUE 700
#define NUM_CLIFF_BLACKTAPE_VALUE 200

//Objects define:
Roomba roomba (&Serial1);
Servo sf;
Servo sb;
Servo sg;
Servo sd;
Motor m1;
Motor m2;
int x;
unsigned int u;

 /*
 ##############################################################################################
 ##                                                                                          ##
 ##                                    Main Program                                          ##
 ##                                                                                          ##
 ##############################################################################################
 */
void setup(){
    Serial.begin(9600);
    Serial.println("Serial communication established,waiting for commands");
    
    //attaching Servos and Motors:
    m1.attach(M1_EN_PIN, M1_INA_PIN, M1_INB_PIN);
    m2.attach(M2_EN_PIN, M2_INA_PIN, M2_INB_PIN);
    sf.attach(4);
    sf.write(NUM_SERVO_FRONT_ZERO_DEGREE);
    sb.attach(5);
    sb.write(NUM_SERVO_BACK_ZERO_DEGREE);
    sg.attach(6);
    sg.write(NUM_SERVO_GRAB_CLOSE);
    sd.attach(7);
    sd.write(NUM_SERVO_DEFENCE_MIN);
    
    //starting Position:
    primaryArmPosition(0);
    secondaryArmPosition(-90);
    grabBasePosition(90);
    
    
    Serial.println("Robot position initalised");
    roomba.start();
        //roomba.fullMode();
    roomba.safeMode();
}

void loop(){
    
    /*
     #####################################################
        STAGE1: ALINING POSITIONS AND WAIT FOR LIGHT
     #####################################################
    */
    
    //Aligning Gametable:
    Serial.println("Aligning Gametable...");
    roomba.driveDirect(-150,-150);
    delay(2000);
    roomba.driveDirect(200,200);
    delay(2500);
    turnAngle(90,250);
    roomba.driveDirect(-150, -150);
    delay(2000);
    roomba.driveDirect(0, 0);
    Serial.println("Robot aligned, please put the hanger on the grabber...");
    
    //Put hangers on the grabber:
    delay(1000);
    openGrab();
    delay(3000);
    closeGrab();
    Serial.println("Got the Grabber, waiting for light...");
    
    //Wait for light:
    int light=analogRead(LIGHT_SENSOR_PIN);
    while(light < NUM_LIGHT_SENSOR_VALUE){
        light=analogRead(LIGHT_SENSOR_PIN);
        Serial.print("Light Value:");Serial.println(light);
        delay(10);
    }
    Serial.println("ROBOT START MOVING!!!\n\n");

    /*
    #####################################################
        STAGE2: PUT STARTING HANGERS ON THE RACK
    #####################################################
    */
    
    //Go to the Black tape:
    roomba.driveDirect(300, 300);
    Serial.println("Going to the Black Tape");
    uint8_t buf[2];
    while(roomba.getSensors(31, buf, 2)) {
        u = BitShiftCombine(buf[0], buf[1]);
        if(u < 500) {
            roomba.driveDirect(0,0);
            break;
        }
    }
    
    //Changing Robot Arm Pos:
    sd.write(NUM_SERVO_DEFENCE_MAX);
    primaryArmPosition(45);
    secondaryArmPositionMIN();
    turnAngle(-90,250);
    
    //Put the hangers on the rack:
    grabBasePosition(NUM_POTENTIOMETER_2_MAX_ANGLE);
    robotPos(45,-10,30,NUM_SERVO_GRAB_CLOSE,NUM_SERVO_DEFENCE_MAX);
    robotPos(30,-3,0,NUM_SERVO_GRAB_CLOSE,NUM_SERVO_DEFENCE_MAX);
    delay(1000);
    openGrab();
    
    //Leave the hangers away:
    roomba.driveDirect(-150,-150);
    delay(500);
    roomba.driveDirect(0,0);
    primaryArmPosition(45);
    secondaryArmPositionMIN();
    
    /*
    #####################################################
     STAGE3: GET THE HANGERS FORM THE CENTRAL RACK
    #####################################################
    */
    


    /*
    #####################################################
                        E      N       D
    #####################################################
    */
    disableEverything();
    while(true){
      Serial.println("Robot stops moving...");
      SensorValue();
      delay(1000);
    }
    
}
/*
 ##############################################################################################
 ##                                                                                          ##
 ##                                  Robot Arm Functions                                     ##
 ##                                                                                          ##
 ##############################################################################################
*/

void robotPos(int primaryArmPos, int secondaryArmPos, int grabBasePos, int grabPos, int defensePos) {
    
    //checking if the angles are posible
    if(primaryArmPos > 55|| primaryArmPos < -55)return;
    if(secondaryArmPos > NUM_POTENTIOMETER_1_MAX_ANGLE || secondaryArmPos < NUM_POTENTIOMETER_1_MIN_ANGLE)return;
    if(grabBasePos > NUM_POTENTIOMETER_2_MAX_ANGLE || grabBasePos < NUM_POTENTIOMETER_2_MIN_ANGLE)return;
    if(grabPos > NUM_SERVO_GRAB_CLOSE || grabPos < NUM_SERVO_GRAB_OPEN)return;
    if(defensePos > NUM_SERVO_DEFENCE_MAX || NUM_SERVO_DEFENCE_MIN < 0)return;
    
    //Changing Servos:
    sf.write(NUM_SERVO_FRONT_ZERO_DEGREE - primaryArmPos);
    sb.write(NUM_SERVO_BACK_ZERO_DEGREE - primaryArmPos);
    sd.write(defensePos);
    sg.write(grabPos);
    
    //Motor 1 - Secondary Arm: moving directions:
    int secondaryDiff = secondaryArmPos - checkSecondaryArmAngle();
	if(secondaryDiff < 5 && secondaryDiff > -5){
		Serial.println("Secondary Arm is not going to turn.");
		Serial.print("Diff:");
                Serial.println(secondaryDiff);
	} else if(secondaryDiff > 0){
		m1.forward(255);
	} else if(secondaryDiff < 0){
		m1.backward(255);
	}
    
    //Motor 2 - Grab Base: moving directions:
    int grabDiff = secondaryArmPos - checkGrabAngle();
    if(grabDiff < 5 && grabDiff > -5){
  		Serial.println("Grab is not going to turn.");
		Serial.print("Diff:");
                Serial.println(grabDiff);
	} else if(grabDiff < 0){
              m2.backward(200);
	} else if(grabDiff > 0){
	      m2.forward(200);
	}


     boolean grabok=false;
     boolean secondaryok=false;
     while(grabok==false || secondaryok==false){
        grabDiff = grabBasePos - checkGrabAngle();
        secondaryDiff = secondaryArmPos - checkSecondaryArmAngle();
        Serial.println(secondaryDiff);
        if(secondaryok==false && secondaryDiff < 5 && secondaryDiff > -5){
            m1.brake();
            secondaryok=true;
        }
        if(grabok==false && grabDiff < 5 && grabDiff > -5){
            m2.brake();
            grabok=true;
        }
    }
}


void secondaryArmPositionMAX(){
    secondaryArmPosition(90);
    m1.forward(255);
    delay(1000);
    m1.brake();
}

void secondaryArmPositionMIN(){
    secondaryArmPosition(-90);
    m1.backward(255);
    delay(1000);
    m1.brake();
}

void primaryArmPosition(int Angle) {
    if(Angle > 45||Angle < -45) return;
    else{
        sf.write(NUM_SERVO_FRONT_ZERO_DEGREE - Angle);
        sb.write(NUM_SERVO_BACK_ZERO_DEGREE - Angle);
    }
}

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

int checkGrabAngle() {
    
   	int value=analogRead(POTENTIOMETER_2_PIN);
	value=map(value,0,684,NUM_POTENTIOMETER_2_MIN_ANGLE,NUM_POTENTIOMETER_2_MAX_ANGLE);
  	return value;
}

int checkSecondaryArmAngle(){
   	int value=analogRead(POTENTIOMETER_1_PIN);
   	value=map(value,0,684,NUM_POTENTIOMETER_1_MIN_ANGLE,NUM_POTENTIOMETER_1_MAX_ANGLE);
   	return value;
}

void openGrab(){
    
    sg.write(NUM_SERVO_GRAB_OPEN);
}

void closeGrab(){
    
    sg.write(NUM_SERVO_GRAB_CLOSE);
}

/*
 ##############################################################################################
 ##                                                                                          ##
 ##                                  General Functions                                       ##
 ##                                                                                          ##
 ##############################################################################################
 */

int BitShiftCombine( unsigned char x_high, unsigned char x_low)
{
    int combined;
    combined = x_high;              //send x_high to rightmost 8 bits
    combined = combined<<8;         //shift x_high over to leftmost 8 bits
    combined |= x_low;                 //logical OR keeps x_high intact in combined and fills in rightmost 8 bits
    return combined;
}

void SensorValue(){
	int grabAngle=checkGrabAngle();
  	int armAngle=checkSecondaryArmAngle();
  	int grabRaw=analogRead(POTENTIOMETER_2_PIN);
  	int armRaw=analogRead(POTENTIOMETER_1_PIN);
	int lightvalue=analogRead(LIGHT_SENSOR_PIN);
    
    Serial.println("\n\n##########################################");
	Serial.print("Light sensor:");
	Serial.println(lightvalue);
    
 	Serial.print("Grab\traw:");
  	Serial.print(grabRaw);
  	Serial.print("\tangle:");
  	Serial.println(grabAngle);
    
  	Serial.print("Arm\traw:");
	Serial.print(armRaw);
  	Serial.print("\tangle:");
  	Serial.println(armAngle);
    
	uint8_t buf[52];                                        // Packet 6 returns 52 bytes
  	bool ret = roomba.getSensors(6 , buf , 52);             // packetID, destination, leng
    
	if (ret)
 	{
		Serial.println("\niRobot Create Packet 6 (Full) Sensor Data \n");
    	Serial.print("* Wheeldrop- Caster: ");
    	Serial.println(bitRead(buf[0], 4));
    	Serial.print("* Wheeldrop- Left: ");
    	Serial.println(bitRead(buf[0], 3));
    	Serial.print("* Wheeldrop- Right: ");
    	Serial.println(bitRead(buf[0], 2));
    	Serial.print("* Bump Left: ");
    	Serial.println(bitRead(buf[0], 1));
    	Serial.print("* Bump Right: ");
    	Serial.println(bitRead(buf[0], 0));
    	Serial.print("Cliff Left Signal Strength (0-4095): ");
    	u = BitShiftCombine(buf[28], buf[29]);      // Value sent as 16 bit unsigned value high byte first.
    	Serial.println(u);
    	Serial.print("Cliff Front Left Signal Strength (0-4095): ");
    	u = BitShiftCombine(buf[30], buf[31]);      // Value sent as 16 bit unsigned value high byte first.
    	Serial.println(u);
    	Serial.print("Cliff Front Right Signal Strength (0-4095): ");
    	u = BitShiftCombine(buf[32], buf[33]);      // Value sent as 16 bit unsigned value high byte first.
    	Serial.println(u);
    	Serial.print("Cliff Right Signal Strength (0-4095): ");
    	u = BitShiftCombine(buf[34], buf[35]);      // Value sent as 16 bit unsigned value high byte first.
    	Serial.println(u);
	}
	else {
        Serial.println("Roomba Sensors Error");
	}
}

void disableEverything(){
    //sf.detach(4);
    //sb.detach(5);
    //sg.detach(6);
    //sd.detach(7);
    roomba.driveDirect(0,0);
}


/*
 ##############################################################################################
 ##                                                                                          ##
 ##                                  Create Functions                                        ##
 ##                                                                                          ##
 ##############################################################################################
 */

void turnAngle(int angle,int speed){
    if(speed<0){return;}
    if(angle>0){roomba.drive(speed, roomba.DriveInPlaceClockwise);}
    else if(angle<0){roomba.drive(speed,roomba.DriveInPlaceCounterClockwise);}
    else return;
    uint8_t buf[2];
    while(!roomba.getSensors(31 , buf , 2));
    roomba.drive(0, 0);

}

