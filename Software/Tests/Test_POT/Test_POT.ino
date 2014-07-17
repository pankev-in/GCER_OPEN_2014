#define NUM_POTENTIOMETER_1_ZERO_DEGREE 450
#define NUM_POTENTIOMETER_2_ZERO_DEGREE 450
#define POTENTIOMETER_1_PIN  1
#define POTENTIOMETER_2_PIN  2

void setup(){
  Serial.begin(9600);
}

void loop(){
  int i=CheckGrabAngle();
  int j=CheckSecondaryArmAngle();
  Serial.print("Grab:");
  Serial.println(i);
  Serial.print("Arm");
  Serial.println(j);
  delay(200);
}

int CheckGrabAngle(){
  int value=analogRead(POTENTIOMETER_2_PIN);
  value=map((value+511-NUM_POTENTIOMETER_2_ZERO_DEGREE),0,1023,-135,135);
  return value;
}

int CheckSecondaryArmAngle(){
  int value=analogRead(POTENTIOMETER_1_PIN);
  value=map((value+511-NUM_POTENTIOMETER_2_ZERO_DEGREE),0,1023,-135,135);
  return value;
}
