#define NUM_POTENTIOMETER_1_ZERO_DEGREE 500
#define NUM_POTENTIOMETER_2_ZERO_DEGREE 450
#define POTENTIOMETER_1_PIN  1
#define POTENTIOMETER_2_PIN  2

void setup(){
  Serial.begin(9600);
}

void loop(){
  int i=CheckGrabAngle();
  int j=CheckSecondaryArmAngle();
  int v1=analogRead(POTENTIOMETER_2_PIN);
  int v2=analogRead(POTENTIOMETER_1_PIN);  
  
  Serial.print("Grab:");
  Serial.print(v1);
  Serial.print("/");
  Serial.println(i);
  /*
  Serial.print("Arm");
  Serial.print(v2);
  Serial.print("/");
  Serial.println(j);
  delay(500);
  */
}

int CheckGrabAngle(){
  int value=analogRead(POTENTIOMETER_2_PIN);
  value=int((value-NUM_POTENTIOMETER_2_ZERO_DEGREE)/(1023/230));
  return value;
}

int CheckSecondaryArmAngle(){
  int value=analogRead(POTENTIOMETER_1_PIN);
  value=int((value-NUM_POTENTIOMETER_1_ZERO_DEGREE)/(1023/230));
  return value;
}
