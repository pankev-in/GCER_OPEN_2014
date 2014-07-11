#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Robot {

	public:
		Robot(int grabbler, int grabblerTurn[], int grabblerTurnPosition, int armJoint[], int armJointPosition, int armBase[]);
		
		void gotoStartPosition();
		
		void gotoGrabblerTurnPosition(int position);
		
		void gotoArmJointPosition(int position);
		
		void gotoArmBasePosition(int position);

		void moveToPosition(int armJointPosition, int armBasePosition);
		
		void grab();
		void open();
	
	private:
		int _grabbler;
		
		Motor _grabblerTurn;
		int _grabblerTurnPosition;

		Motor _armJoint;
		int _armJointPosition;	
		
		int _armBase[];

}

#endif
