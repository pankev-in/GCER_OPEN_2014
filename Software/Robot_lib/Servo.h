class Servo {
	
	public:
		Servo(int pin);
		
		void enable();
		void disable();

		void setPosition();
		void getPosition();

	private:
		int _position;
		int _pin;
}
