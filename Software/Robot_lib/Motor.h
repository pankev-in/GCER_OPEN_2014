class Motor {

	public:
		Motor(int pins[]);

		void forward(int speed);
		void backward(int speed);
		void stop();
		void breakk();

	private:
		int _E;
		int _IN1;
		int _IN2;
}	
