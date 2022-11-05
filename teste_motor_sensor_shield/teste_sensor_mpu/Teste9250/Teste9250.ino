#include <MPU9250_asukiaaa.h>

MPU9250_asukiaaa mySensor;
// aceleração, giroscópio
float aX, aY, aZ, gX, gY, gZ;
//médias
float maX, maY, maZ, mgX, mgY, mgZ;
//bases
float baX, baY, baZ, bgX, bgY, bgZ;


//calcula to tempo para chegar em 90 graus ou pi radianos


// lê o sensor
void lerSensor(){
  if(mySensor.accelUpdate() == 0){
    if(mySensor.gyroUpdate() == 0){
      aX = mySensor.accelX();
      aY = mySensor.accelY();
      aZ = mySensor.accelZ();
      gX = mySensor.gyroX();
      gY = mySensor.gyroY();
      gZ = mySensor.gyroZ(); 
    }
  }
}

//calcula a média
void mediaSensor(){
   maX = 0;
   maY = 0;
   maZ = 0;
   for (int i = 0; i < 10; i++){
    lerSensor();
    maX += aX;
    maY += aY;
    maZ += aZ;
    mgX += gX;
    mgY += gY;
    mgZ += gZ;
   }
   maX = maX / 10;
   maY = maY / 10;
   maZ = maZ / 10;
   mgX = mgX / 10;
   mgY = mgY / 10;
   mgZ = mgZ / 10;
}

// usa a média inicial como base para cálculos
void estabilizaSensor(){
  mediaSensor();
  baX = maX;
  baY = maY;
  baZ = maZ;
  bgX = mgX;
  bgY = mgY;
  bgZ = mgZ;
}


void setup() {
  
  Serial.begin(9600);


  mySensor.beginAccel();
  mySensor.beginGyro();
  mySensor.beginMag();
  estabilizaSensor();

 

}

void loop() {
  float tempox, tempoy;
  float accelx, accely;


  mediaSensor();

  Serial.println(String(maX));
  Serial.println(String(maY));
  Serial.println(String(maZ));
  Serial.println(String(mgX));
  Serial.println(String(mgY));
  Serial.println(String(mgZ));
  delay(1000);
 
 

}
