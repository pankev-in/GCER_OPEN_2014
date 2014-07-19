#include "Arduino.h"
#include "Motor.h"
#include "Servo.h"
#include "Robot_Arm.h"

Robot_Arm::Robot_Arm(int M1Pins[3],int M2Pins[3],int SFrontPin, int SBackPin,int SGrabPin, int Pot1,int Pot2)
{
	_MotorRightArm1.attach(M1Pins[0],M1Pins[1],M1Pins[2]);
	_MotorRightArm2.attach(M2Pins[0],M2Pins[1],M2Pins[2]);
	_ServoFront.attach(SFrontPin);
	_ServoBack.attach(SBackPin);
	_ServoGrab.attach(SGrabPin);
	_Potentiometer1Pin=Pot1;
	_Potentiometer1Pin=Pot2;
	_Pot1Value=CheckRightArm();
	_Pot2Value=CheckGrabBase();

}

void Robot_Arm::MainArmPosition(int Angle)	//Between 45 to -45 degree
{
	if(Angle>45||Angle<-45){return;}
	_ServoFront.write(Servo1_StartValue+Angle);
	_ServoBack.write(Servo2_StartValue-Angle);
}

void Robot_Arm::RightArmPosition(int Angle)	//Between 135 to -135 degree
{
	if(Angle>135||Angle<-135){return;}
	_Pot1Value=CheckRightArm();
	int diff=Angle-_Pot1Value;
	if(diff==0){return;}
	else if(diff>0){
		_MotorRightArm1.forward(200);
		while(_Pot1Value<Angle){
			_Pot1Value=CheckRightArm();
		}
		_MotorRightArm1.brake();
	}
	else if(diff<0){
		_MotorRightArm1.backward(200);
		while(_Pot1Value>Angle){
			_Pot1Value=CheckRightArm();
		}
		_MotorRightArm1.brake();
	}
}

void Robot_Arm::GrabBasePosition(int Angle)	//Between 135 to -135 degree
{
	if(Angle>135||Angle<-135){return;}
	_Pot2Value=CheckGrabBase();
	int diff=Angle-_Pot2Value;
	if(diff==0){return;}
	else if(diff>0){
		_MotorRightArm2.forward(200);
		while(_Pot2Value<Angle){
			_Pot2Value=CheckGrabBase();
		}
		_MotorRightArm2.brake();
	}
	else if(diff<0){
		_MotorRightArm2.backward(200);
		while(_Pot1Value>Angle){
			_Pot2Value=CheckGrabBase();
		}
		_MotorRightArm2.brake();
	}
}

int Robot_Arm::CheckRightArm()			//Return Right Arm position in degree
{
	int value=analogRead(_Potentiometer1Pin);
	value=map(value,0,1023,-135,135);
	return value;
}

int Robot_Arm::CheckGrabBase()			//Return Grab Base position in degree
{
	int value=analogRead(_Potentiometer2Pin);
	value=map(value,0,1023,-135,135);
	return value;
}

void Robot_Arm::CloseGrab()			//Closes the Grabber
{
	_ServoGrab.write(GrabCloseValue);
}

void Robot_Arm::OpenGrab()			//Open the Grabber
{
	_ServoGrab.write(GrabOpenValue);
}
