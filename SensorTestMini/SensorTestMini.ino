// =============================================
// Minimal Sensor Test - 最小化传感器测试
// 左: Pin 2 | 右: Pin 3
// 距离: A0 | A2
// Serial Monitor (9600)
// =============================================

#include <SharpDistSensor.h>

// Window size of the median filter (odd number, 1 = no filtering)
const byte medianFilterWindowSize = 5;

const byte DIST_SENSOR_A0_PIN = A0; //Left sensor is on A0 to avoid conflict with Left sensor on Pin 2 
const byte DIST_SENSOR_A2_PIN = A2; //Right sensor is on A2 to avoid conflict with Left sensor on Pin 2

SharpDistSensor distSensorA0(DIST_SENSOR_A0_PIN, medianFilterWindowSize);
SharpDistSensor distSensorA2(DIST_SENSOR_A2_PIN, medianFilterWindowSize);

const int LEFT_SENSOR  = 3;
const int RIGHT_SENSOR = 2;

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_SENSOR,  INPUT_PULLUP);
  pinMode(RIGHT_SENSOR, INPUT_PULLUP);
  Serial.println("L/R:数字sensor (0=遮住 1=光亮) | A0/A2:raw,mm");
}

void loop() {
  int L = digitalRead(LEFT_SENSOR);
  int R = digitalRead(RIGHT_SENSOR);
  int rawA0 = analogRead(DIST_SENSOR_A0_PIN); //left
  int rawA2 = analogRead(DIST_SENSOR_A2_PIN); //right
  unsigned int distA0 = distSensorA0.getDist();
  unsigned int distA2 = distSensorA2.getDist();
  
  Serial.print("L:");
  Serial.print(L);
  Serial.print(" R:");
  Serial.print(R);
  Serial.print(" A0:");
  Serial.print(rawA0);
  Serial.print(",");
  Serial.print(distA0);
  Serial.print("mm A2:");
  Serial.print(rawA2);
  Serial.print(",");
  Serial.print(distA2);
  Serial.println("mm");
  
  delay(200);
}
