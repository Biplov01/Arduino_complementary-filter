#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "MegunoLink.h"
#include "Filter.h"
Adafruit_MPU6050 mpu;
float dx, dy, dz;
float acelx, acely, acelz;

float countz, countx, county = 0;
int second, disp = 0;
float elapsedTime, currentTime;
unsigned long previousTime = 0;

byte seconds ;
ExponentialFilter<long> Filter1(5, 0);
ExponentialFilter<long> Filter2(10, 0);
void setup(void) {
  Serial.begin(115200);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {
  /* previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime);*/
   Filter1.Filter(analogRead(4));
  Filter2.Filter(analogRead(5));

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
 
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");
  countz = a.acceleration.z;
  county = a.acceleration.y;
  countx = a.acceleration.x;
  
/* dx = (dx+((((a.acceleration.x-0.3) * (a.acceleration.x-0.3))/32768)/2.0)*elapsedTime);

         dy = (dy+((((a.acceleration.y-0.3)*(a.acceleration.y-0.3))/32768)/2.0)*elapsedTime);

         dz = (dz+((((a.acceleration.z-0.3)*(a.acceleration.z-0.3))/32768)/2.0)*elapsedTime);
*/ 
if(county < -1 || county > 1)
  {
     second = second + 1;
       disp = disp + 1;

  }

  
  Serial.println("supposed displacement");
     Serial.print(disp);

    Serial.print(" ");
     Serial.println("secondsa");
     Serial.print(second);

    Serial.print(" ");
dx =  a.acceleration.x/2 * second * second;
dy =  a.acceleration.y/2 * second * second;
dz =  a.acceleration.z/2 * second * second;
         acelx = (0.04167) * (a.acceleration.x * a.acceleration.x * a.acceleration.x) * (second) * (second) * (second) * (second);

         acely = (0.04167) * (a.acceleration.y * a.acceleration.y * a.acceleration.y) * (second) * (second) * (second) * (second);

         acelz = (0.04167) * (a.acceleration.z * a.acceleration.z * a.acceleration.z) * (second) * (second) * (second) * (second);
/* dy = ((1/2) * ((a.acceleration.x)*(elapsedTime * elapsedTime)));

dz = ((1/2) * ((a.acceleration.x)*(elapsedTime * elapsedTime))); */

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");
    Serial.println(" displacement in X, Y, Z");

     Serial.print(dx);
    Serial.print(" ");
    Serial.print(dy);
    Serial.print(" ");
    Serial.print(dz);
    Serial.print(" ");
    
  Serial.println("linear accelerations in X, Y, Z");

     Serial.print(acelx);
    Serial.print(" ");
    Serial.print(acely);
    Serial.print(" ");
    Serial.print(acelz);
    Serial.print(" ");
     Serial.print(seconds);
    Serial.print(" ");
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
  delay(500);
}
