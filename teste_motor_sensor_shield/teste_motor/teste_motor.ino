#include <Servo.h>
/* Cria os objetos para controlar os servos */
Servo servo1;

int Pino_Servo1 = 0;

void setup() {

  servo1.attach(Pino_Servo1);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < 360; i++){
    servo1.write(i);
    delay(10);
  }
}
