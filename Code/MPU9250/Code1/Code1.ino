#include <Wire.h>

#include <Servo.h>

#include <MPU9250_asukiaaa.h>


MPU9250_asukiaaa mySensor= MPU9250_asukiaaa(0x68);
MPU9250_asukiaaa mySensor2 = MPU9250_asukiaaa(0x69);

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;



void setup(){
  Serial.begin(115200);
  myservo1.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);
  myservo5.attach(6);
  myservo6.attach(7);
  myservo7.attach(8);
  myservo8.attach(9);
  
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  mySensor.beginAccel();
  mySensor.beginGyro();

  mySensor2.beginAccel();
  mySensor2.beginGyro();
  
  
}

void loop(){
  digitalWrite(12, HIGH);
  float angle1, angle2, trueAngle;
  angle1 = getAngleSensor1();
  angle2 = getAngleSensor2();

  Serial.print("Angle1 = ");
  Serial.print(angle1);
  Serial.print("\n");
  Serial.print("Angle2 = ");
  Serial.print(angle2);
  Serial.print("\n");
  
  trueAngle = (angle1 + angle2)/2;
  setAngle(trueAngle);  
  delay(1000);
}

void setAngle(float trueAngle){
  Serial.print("\n True Angle = ");
  Serial.print(trueAngle);
  Serial.print("\n");
  int pos1 = 140- trueAngle, pos2 = 30 + trueAngle;
  Serial.print("\n Pos1 - 2  = ");
  Serial.print(pos1);
  Serial.print(" ");
  Serial.print(pos2);
  Serial.print("\n");
  myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(60);
  myservo4.write(120);
  myservo5.write(130);
  myservo6.write(60);
  myservo7.write(90);
  myservo8.write(90);
  
}

float getAngleSensor1(){
  float ax, az;
  if(mySensor.accelUpdate() == 0){
    ax = mySensor.accelX();
    az = mySensor.accelZ();
  }

  float angle = atan(ax/az);
  angle = angle*180/3.14159;
  return angle;
}

float getAngleSensor2(){
  float ax, az;
  if(mySensor2.accelUpdate() == 0){
    ax = mySensor2.accelX();
    az = mySensor2.accelZ();
  }

  float angle = atan(ax/az);
  angle = angle*180/3.14159;
  return angle;
}
