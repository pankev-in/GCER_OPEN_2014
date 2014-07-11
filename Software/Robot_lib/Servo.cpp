#include Alduino.h

Servo::Servo(int pin) {

	_pin = pin;
	_position = 0;

	pinMode(_pin, OUTPUT);
}

void enable() {

	analogWrite(_pin, _position);
}

void disable() {

	analogWrite(_pin, 0);
}
void setPosition(int position) {

	if(position < 0 || position > 255) {

		prinf("illegal servo position");
		return;
	}

	_position = position;
	*this.enable();
}

int getPosition() {
	
	return _position;
}
