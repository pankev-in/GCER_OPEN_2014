/*
  Motor.h - Library to control motors with L298N Motor shield
  Created by Klaus Ableitinger & Kevin Pan, 2014 July
*/

#ifndef Motor_h
#define Motor_h
#include "Arduino.h"

class Motor {

	public:
		Motor();
		void attach(int en,int in1,int in2);
		void forward(int speed);
		void backward(int speed);
		void floating();
		void brake();

	private:
		int _EN;
		int _IN1;
		int _IN2;
};

#endif
