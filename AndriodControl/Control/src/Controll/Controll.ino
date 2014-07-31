/*
 Program: GCER 2014 OPEN GAME: Andriod Control Mode
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
#define LIGHT_SENSOR_PIN A0
#define POTENTIOMETER_1_PIN  A1
#define POTENTIOMETER_2_PIN  A2

//Constants:
#define NUM_SERVO_FRONT_ZERO_DEGREE 80
#define NUM_SERVO_BACK_ZERO_DEGREE 95
#define NUM_SERVO_GRAB_CLOSE 180
#define NUM_SERVO_GRAB_OPEN 55
#define NUM_SERVO_DEFENCE_MAX 150
#define NUM_SERVO_DEFENCE_MIN 30

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
Servo sf;
Servo sb;
Servo sg;
Servo sd;
Motor m1;
Motor m2;

int x;
unsigned int u;
int go;
int back;
int left;
int right;
int primary_arm_angle;
int secondary_arm_angle;
int defence_arm_angle;
int grab_base_angle;
int grab_angle;
String inputString = "";   // Holding incomming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
    Serial.begin(9600);
    Serial.println("Serial communication established,waiting for commands");
    
    m1.attach(M1_EN_PIN, M1_INA_PIN, M1_INB_PIN);
    m2.attach(M2_EN_PIN, M2_INA_PIN, M2_INB_PIN);
    sf.attach(4);
    sf.write(NUM_SERVO_FRONT_ZERO_DEGREE);
    sb.attach(5);
    sb.write(NUM_SERVO_BACK_ZERO_DEGREE);
    sg.attach(6);
    sg.write(NUM_SERVO_GRAB_OPEN);
    sd.attach(7);
    sd.write(NUM_SERVO_DEFENCE_MIN);
    Serial.println("Robot position initalised");
    
    roomba.start();
    roomba.fullMode();
}

void loop() {
    
    //wait until the data completly comes:
    if (stringComplete) {
        inputString=inputString.substring(1,inputString.length());
        int index[9];
        index[0]=inputString.indexOf(";");
        for(int i=1;i<=7;i++){
            index[i]=inputString.indexOf(";",index[i-1]+1);
        }
        
        go=inputString.substring(0,index[0]).toInt();
        back=inputString.substring(index[0]+1,index[1]).toInt();
        left=inputString.substring(index[1]+1,index[2]).toInt();
        right=inputString.substring(index[2]+1,index[3]).toInt();
        primary_arm_angle=inputString.substring(index[3]+1,index[4]).toInt();
        secondary_arm_angle=inputString.substring(index[4]+1,index[5]).toInt();
        defence_arm_angle=inputString.substring(index[5]+1,index[6]).toInt();
        grab_base_angle=inputString.substring(index[6]+1,index[7]).toInt();
        grab_angle=inputString.substring(index[7]+1,index[8]).toInt();
        
        
        if(back==0&&go==1&&left==0&&right==0){
            roomba.driveDirect(200,200);
        }
        else if(back==1&&go==0&&left==0&&right==0){
            roomba.driveDirect(-200,-200);
        }
        else if(back==0&&go==0&&left==1&&right==0){
            roomba.drive(NUM_ROOMBA_TURN_SPEED, roomba.DriveInPlaceCounterClockwise);
        }
        else if(back==0&&go==0&&left==0&&right==1){
            roomba.drive(NUM_ROOMBA_TURN_SPEED, roomba.DriveInPlaceClockwise);
        }
        else{
            roomba.driveDirect(0,0);
        }

		//SERVO_DEFENCE.write(defence_arm_angle);
		//primaryArmPosition(primary_arm_angle);

		Serial.println("\n\n");
		Serial.println(inputString);
		Serial.print("Go:");Serial.print(go);Serial.print("Back:");Serial.print(back);Serial.print("Left:");Serial.print(left);Serial.print("Right");Serial.println(right);
		// clear the string:
        inputString = "";
        stringComplete = false;
    }
}

void serialEvent(){
	while (Serial.available()) {
    	// get the new byte:
    	char inChar = (char)Serial.read(); 
    	// add it to the inputString:
    	inputString += inChar;
    	// if the incoming character is a newline, set a flag
    	// so the main loop can do something about it:
    	if (inChar == '\n') {
            if(inputString[0]=='#'){
				stringComplete = true;
			}
            else{
				inputString="";
			}
    } 
  }
}

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length()-1;
    
    for(int i=0; i<=maxIndex && found<=index; i++){
        if(data.charAt(i)==separator || i==maxIndex){
            found++;
            strIndex[0] = strIndex[1]+1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    
    return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void robotPos(int primaryArmPos, int secondaryArmPos, int grabBasePos, int grabPos, int defensePos) {
    if(primaryArmPos > 45|| primaryArmPos < -45){
        return;
    }
    if(secondaryArmPos > NUM_POTENTIOMETER_1_MAX_ANGLE || secondaryArmPos < NUM_POTENTIOMETER_1_MIN_ANGLE){
        return;
    }
    if(grabBasePos > NUM_POTENTIOMETER_2_MAX_ANGLE || grabBasePos < NUM_POTENTIOMETER_2_MIN_ANGLE){
        return;
    }
    if(grabPos > NUM_SERVO_GRAB_CLOSE || grabPos < NUM_SERVO_GRAB_OPEN){
        return;
    }
    if(defensePos > NUM_SERVO_DEFENCE_MAX || NUM_SERVO_DEFENCE_MIN < 0){
        return;
    }
    
    sf.write(NUM_SERVO_FRONT_ZERO_DEGREE - primaryArmPos);
    sb.write(NUM_SERVO_BACK_ZERO_DEGREE - primaryArmPos);
    sd.write(defensePos);
    sg.write(grabPos);
    
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
    
	while((grabDiff > 5 || grabDiff < -5) || (secondaryDiff > 5 || secondaryDiff < -5)){
        grabDiff = grabBasePos - checkGrabAngle();
        secondaryDiff = secondaryArmPos - checkSecondaryArmAngle();
        if(secondaryDiff < 5 && secondaryDiff > -5){
            m1.brake();
        }
        if(grabDiff < 5 && grabDiff > -5){
            m2.brake();
        }
	}
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

void turnRight() {
    roomba.drive(NUM_ROOMBA_TURN_SPEED, roomba.DriveInPlaceClockwise);
    delay(1000);
    roomba.driveDirect(0, 0);
}

void turnLeft() {
    roomba.drive(NUM_ROOMBA_TURN_SPEED, roomba.DriveInPlaceCounterClockwise);
    delay(1000);
    roomba.driveDirect(0, 0);
}

void turnAround() {
    roomba.drive(NUM_ROOMBA_TURN_SPEED, roomba.DriveInPlaceClockwise);
    delay(2000);
    roomba.driveDirect(0, 0);
}

