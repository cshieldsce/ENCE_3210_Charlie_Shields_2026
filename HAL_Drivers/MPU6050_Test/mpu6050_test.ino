#include "MPU6050.h"

MPU6050 gMPU;
int16_t gAx, gAy, gAz;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Init IMU
  gMPU.initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  gMPU.getAcceleration(&gAx, &gAy, &gAz);
  Serial.println(gAx);
}
