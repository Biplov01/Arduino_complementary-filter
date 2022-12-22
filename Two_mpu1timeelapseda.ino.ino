#include <Wire.h>

const int MPU_addrs[] = { 0x68, 0x69 };
int b;
float AcX[2], AcY[2], AcZ[2], Tmp[2]; // definition of variables
float elapsedTime, currentTime, previousTime;
float acelX, acelY, acelZ;
float dx, dy, dz;
float kalaccel;
void setup()
{
  for(byte b=0; b<2; b++)
  {
    Wire.begin();
    Wire.beginTransmission(MPU_addrs[b]);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
  }

  Serial.begin(9600);
}

void loop()
{
  for(byte b=0; b<2; b++)
  {
 
  
    Wire.beginTransmission(MPU_addrs[b]);
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);

    Wire.requestFrom(MPU_addrs[b], 8, true); // request a total of 8 registers
  }
   previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime);
  
    AcX[b] = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcY[b] = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ[b] = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp[b] = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    Serial.print(AcX[b] / 16384);
    Serial.print(" ");
    Serial.print(AcY[b] / 16384);
    Serial.print(" ");
    Serial.print(AcZ[b] / 16384);
    Serial.print(" ");
    Serial.println(Tmp[b] / 340.00 + 36.53);


      

  
  dx = (dx+((((AcX[b]-0.3) * (AcX[b]-0.3))/32768)/2.0)*elapsedTime);

         dy = (dy+((((AcY[b]-0.3)*(AcY[b]-0.3))/32768)/2.0)*elapsedTime);

         dz = (dz+((((AcZ[b]-0.3)*(AcZ[b]-0.3))/32768)/2.0)*elapsedTime);

           Serial.println(" displacement in X, Y, Z");

     Serial.print(dx);
    Serial.print(" ");
    Serial.print(dy);
    Serial.print(" ");
    Serial.print(dz);
    Serial.print(" ");
  




delay(1000);



  }
  
