#include <Arduino.h>
#include <Roomba.h>
void setup();
void loop();
int BitShiftCombine( unsigned char x_high, unsigned char x_low);
int CheckGrabAngle();
int CheckSecondaryArmAngle();
#line 1 "src/sketch.ino"
//#include <Roomba.h>

#define NUM_POTENTIOMETER_1_ZERO_DEGREE 330
#define NUM_POTENTIOMETER_2_ZERO_DEGREE 310
#define LIGHT_SENSOR_PIN  0
#define POTENTIOMETER_1_PIN  1
#define POTENTIOMETER_2_PIN  2

Roomba roomba(&Serial1);

int x;                   // 16 bit signed variable
unsigned int u;          // 16 bit unsigned variable

void setup()
{
  Serial.begin(9600);          // baud rate of serial monitor

  roomba.start();
  roomba.safeMode();
}

void loop()
{
	int grabAngle=CheckGrabAngle();
  	int armAngle=CheckSecondaryArmAngle();
  	int grabRaw=analogRead(POTENTIOMETER_2_PIN);
  	int armRaw=analogRead(POTENTIOMETER_1_PIN);
	int lightvalue=analogRead(LIGHT_SENSOR_PIN);  

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
	    Serial.print("Bumps and Wheel Drops: ");
	   	Serial.println(buf[0], BIN);
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
    	Serial.print("Cliff Left: ");
   		Serial.println(buf[2], BIN);  
    	Serial.print("Cliff Front Left: ");  
    	Serial.println(buf[3], BIN);   
    	Serial.print("Cliff Front Right: ");  
    	Serial.println(buf[4], BIN);  
    	Serial.print("Cliff Right: ");    
    	Serial.println(buf[5], BIN);
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
	delay(5000);

}

int BitShiftCombine( unsigned char x_high, unsigned char x_low)
{
  int combined;  
  combined = x_high;              //send x_high to rightmost 8 bits
  combined = combined<<8;         //shift x_high over to leftmost 8 bits
  combined |= x_low;                 //logical OR keeps x_high intact in combined and fills in rightmost 8 bits 
  return combined;
}

int CheckGrabAngle(){
  int value=analogRead(POTENTIOMETER_2_PIN);
	value=map(value,0,697,-93,115);
  return value;
}

int CheckSecondaryArmAngle(){
  int value=analogRead(POTENTIOMETER_1_PIN);
  value=map(value,0,697,-98,108);
  return value;
}
