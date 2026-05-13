#include <Arduino.h>
#include <SharpDistSensor.h>

// PWM 调速：HIGH 只是数值 1，占空比太低，电机往往看起来“完全不动”。全速用 255。
const uint8_t high = 240;
const uint8_t high1 = 255;
const uint8_t low = 0;
const byte medianFilterWindowSize = 5;
const byte LEFT_DIST_SENSOR_PIN = A0;
const byte RIGHT_DIST_SENSOR_PIN = A2;
const unsigned int TARGET_DISTANCE_MM = 600;
SharpDistSensor leftDistSensor(LEFT_DIST_SENSOR_PIN, medianFilterWindowSize);
SharpDistSensor rightDistSensor(RIGHT_DIST_SENSOR_PIN, medianFilterWindowSize);

int LeftSensor = 3;
int RightSensor = 2;
int speed1 = 5;
int direction1 = 7;
int speed2 = 6;
int direction2 = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LeftSensor, INPUT_PULLUP);
  pinMode(RightSensor, INPUT_PULLUP);
  pinMode(direction1, OUTPUT);
  pinMode(direction2, OUTPUT);
  pinMode(speed1, OUTPUT);
  pinMode(speed2, OUTPUT);
  
}

void loop() {
  int leftRaw = analogRead(LEFT_DIST_SENSOR_PIN);
  int rightRaw = analogRead(RIGHT_DIST_SENSOR_PIN);
  unsigned int leftDistance = leftDistSensor.getDist();
  unsigned int rightDistance = rightDistSensor.getDist();
  Serial.print("L:");
  Serial.print(digitalRead(LeftSensor));
  Serial.print(" R:");
  Serial.println(digitalRead(RightSensor));
  Serial.print(" Left Distance:");
  Serial.print(leftRaw);
  Serial.print(",");
  Serial.print(leftDistance);
  Serial.print("mm Right Distance:");
  Serial.print(rightRaw);
  Serial.print(",");
  Serial.print(rightDistance);
  Serial.println("mm");

  if(((digitalRead(LeftSensor))==0)&&((digitalRead(RightSensor))==0)){
    forward();
  }else if(((digitalRead(LeftSensor))==1) && ((digitalRead(RightSensor))==0)){
    backward();
    delay(300);
    left();
    delay(350);
  }else if(((digitalRead(LeftSensor))==0)&&((digitalRead(RightSensor))==1)){
    backward();
    delay(300);
    right();
    delay(350);
  }else if(((digitalRead(LeftSensor))==1)&&((digitalRead(RightSensor))==1)){
    backward();
    delay(500); 
    left();
    delay(350);
  // }else{
  //   stop();
  //   delay(300);
  }
  if(leftDistance < TARGET_DISTANCE_MM){
    left_only();
    delay(20);
  }else if(rightDistance < TARGET_DISTANCE_MM){
    right_only();
    delay(20);
  // }else{
  //   forward();
  // }
  }
} 

void forward() {
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, high1);
  analogWrite(speed2, high1);
}

void backward() {
  digitalWrite(direction1, LOW);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, high1);
  analogWrite(speed2, high1);

  // LOW = motor backward && full speed turning counterclockwise
}

void left() {

  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, high1);
  analogWrite(speed2, high1);
}

void left_only() {

  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, high1);
  analogWrite(speed2, 0);
}

void right() {

  digitalWrite(direction1, LOW);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, high1);
  analogWrite(speed2, high1);
}

void right_only() {
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, 0);
  analogWrite(speed2, high1);
}

void stop() {

  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, low);
  analogWrite(speed2, low);
}