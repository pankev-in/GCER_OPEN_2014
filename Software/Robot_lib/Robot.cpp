Robot::Robot(int grabbler, int grabblerTurn[], int grabblerTurnPosition, int armJoint[], int armJointPosition, int armBase[]) {

	_grabbler = new Servo(grabbler);
	
	_grabblerTurn = new Motor(grabblerTurn);
	_grabblerTurnPosition = grabblerTurnPosition;
	
	_armJoint = new Motor(armJoint);
	_armJointPosition = armJointPosition;
	
	_armBase_left = new Servo(armBase[0]);
	_armBase_right = new Servo(armBase[1]);
	
	pinMode(_grabblerTurnPosition, INPUT);	

	pinMode(_armJointPosition, INPUT);
}

void Robot::gotoStartPosition() {

}

void Robot::gotoGrabblerTurnPosition(int position) {

}

void Robot::gotoArmJointPosition(int position) {

}

void Robot::gotoArmBasePosition(int position) {

}

void Robot::moveToPosition(int armJointPosition, int armBasePosition) {

}

void Robot::grab() {

}

void Robot::open() {

}
