#include "Arduino.h"
#include "Motor.h"

Motor::Motor() {
}

void Motor::attach(int en,int in1,int in2){
	_EN = en;
	_IN1 = in1;
	_IN2 = in2;

    pinMode(en, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
    
}

void Motor::forward(int speed) {
	if(speed < 0 || speed > 255) {
		return;
	}

	digitalWrite(_IN1, HIGH);
	digitalWrite(_IN2, LOW);
	analogWrite(_EN, speed);
}

void Motor::backward(int speed) {
	if(speed < 0 || speed > 255) {
		return;
	}
	digitalWrite(_IN1, LOW);
	digitalWrite(_IN2, HIGH);
	analogWrite(_EN, speed);
}

void Motor::floating(){
	digitalWrite(_IN1,LOW);
	digitalWrite(_IN2,LOW);
	digitalWrite(_EN, HIGH);
}


void Motor::brake(){
	digitalWrite(_IN1, HIGH);
	digitalWrite(_IN2, HIGH);
	digitalWrite(_EN, HIGH);
}
