#include Alduino.h

Motor::Motor(int pins[]) {
	
	_E = pins[0];
	_IN1 = pins[1];
	_IN2 = pins[2];

	pinMode(_E, OUTPUT);
	pinMode(_IN1, OUTPUT);
	pinMode(_IN2, OUTPUT);
}

void forward(int speed) {

	if(speed < 0 || speed > 255) {

		printf("Illegal forward speed");
		return;
	}

	printf("forward with speed %D", speed);

	digitalWrite(_IN1, HIGH);
	digitalWrite(_IN2, LOW);

	analogWrite(_E, speed);
}

void backward(int speed) {

	if(speed < 0 || speed > 255) {
	
		printf("Illegal backward speed");
		return;
	}
	printf("backward with speed %D", speed);

	digitalWrite(_IN1, LOW);
	digitalWrite(_IN2, HIGH);

	analogWrite(_E, speed);
}

void stop() {

	printf("stopping");

	digitalWrite(_IN1, LOW);
	digitalWrite(_IN2, LOW);

	analogWrite(_E, 0);
}

void breakk() {

	printf("braking");

	digitalWrite(_IN1, wHIGH);
	digitalWrite(_IN2, HIGH);

	analogWrite(_E, 0);
}
