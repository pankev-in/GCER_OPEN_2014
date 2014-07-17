class Servo {
	
	public:
		Servo(int pin);
		
		void enable();
		void disable();

		void setPosition(int position);
		int getPosition();

	private:
		int _position;
		int _pin;
}
