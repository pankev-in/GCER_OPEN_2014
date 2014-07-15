#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int pins[]) {
	pinMode(pins[0], OUTPUT);
	pinMode(pins[1], OUTPUT);
	pinMode(pins[2], OUTPUT);
    
	_EN = pins[0];
	_IN1 = pins[1];
	_IN2 = pins[2];
    
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
