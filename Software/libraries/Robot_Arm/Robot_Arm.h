/*
  Robot_Arm.h - Library to control Robot Arm using by Team PRIA Allstars Open Game
  2014 July
*/

#ifndef Robot_Arm_h
#define Robot_Arm_h
#include "Arduino.h"
#include "Motor.h"
#include "Servo.h"

#define Servo1_StartValue 100
#define Servo2_StartValue 110
#define GrabCloseValue 20
#define GrabOpenValue 100


class Robot_Arm {

	public:
		Robot_Arm(int M1Pins[3],int M2Pins[3],int SFrontPin, int SBackPin,int SGrabPin, int Pot1,int Pot2);
		void MainArmPosition(int Angle);	//Between 45 to -45 degree
		void RightArmPosition(int Angle);	//Between 135 to -135 degree
		void GrabBasePosition(int Angle);	//Between 135 to -135 degree
		int CheckRightArm();			//Return Right Arm position in degree
		int CheckGrabBase();			//Return Grab Base position in degree
		void CloseGrab();			//Closes the Grabber
		void OpenGrab();			//Open the Grabber

	private:
		Motor _MotorRightArm1;
		Motor _MotorRightArm2;
		Servo _ServoFront;
		Servo _ServoBack;
		Servo _ServoGrab;
		int _Potentiometer1Pin;
		int _Potentiometer2Pin;
		int _Pot1Value;
		int _Pot2Value;
		

};

#endif
