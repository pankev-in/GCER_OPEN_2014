Robot::Robot(int grabbler, int grabblerTurn[], int grabblerTurnPosition, int armJoint[], int armJointPosition, int armBase[]) {

	_grabbler = grabbler;
	
	_grabblerTurn = new Motor(grabblerTurn);
	_grabblerTurnPosition = grabblerTurnPosition;
	
	_armJoint = new Motor(armJoint);
	_armJointPosition = armJointPosition;
	
	_armBase = armBase;
	
	pinMode(_grabbler, OUTPUT);
	
	pinMode(_grabblerTurnPosition, INPUT);	

	pinMode(_armJointPosition, INPUT);
	
	pinMode(_armBase[0], OUTPUT);
	pinMode(_armBase[1], OUTPUT);
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
