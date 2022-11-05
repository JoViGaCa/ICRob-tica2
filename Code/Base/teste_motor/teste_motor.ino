#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;
Servo myservo7;
Servo myservo8;// create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo1.attach(0);
  myservo2.attach(1);
  myservo3.attach(2);
  myservo4.attach(3);
  myservo5.attach(4);
  myservo6.attach(5);
  myservo7.attach(6);
  myservo8.attach(7);// attaches the servo on pin 9 to the servo object
}

void loop() {
  for(int i = 0; i < 180; i++){
    myservo1.write(i);  
    delay(100);
  }
  myservo1.write(150);

  for(int i = 0; i < 180; i++){
    myservo2.write(i);  
    delay(100);
  }
  myservo2.write(30);

  for(int i = 0; i < 180; i++){
    myservo3.write(i);  
    delay(100);
  }
  myservo3.write(60);

  for(int i = 0; i < 180; i++){
    myservo4.write(i);  
    delay(100);
  }
  myservo4.write(120);

  for(int i = 0; i < 180; i++){
    myservo5.write(i);  
    delay(100);
  }
  myservo5.write(130);

  for(int i = 0; i < 180; i++){
    myservo6.write(i);  
    delay(100);
  }
  myservo6.write(50);


  myservo7.write(90);

  myservo8.write(90);
}
