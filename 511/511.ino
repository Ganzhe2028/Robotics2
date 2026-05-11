#include <Arduino.h>
// #include <SharpDistSensor>

// PWM 调速：HIGH 只是数值 1，占空比太低，电机往往看起来“完全不动”。全速用 255。
const uint8_t high = 240;
const uint8_t high1 = 255;
const uint8_t low = 0;

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
  if(((digitalRead(LeftSensor))==0)&&((digitalRead(RightSensor))==0)){
    forward();
  // }else if(((digitalRead(LeftSensor))==1)&&((digitalRead(RightSensor))==0)){
  //   // backward();
  //   // delay(100);
  //   right();
  //   delay(550);
  // }else if(((digitalRead(LeftSensor))==0)&&((digitalRead(RightSensor))==1)){
  //   // backward();
  //   // delay(100);
  //   left();
  //   delay(550);
  // }else if(((digitalRead(LeftSensor))==1)&&((digitalRead(RightSensor))==1)){
  //   // backward();
  //   // delay(100); 
  //   left();
  //   delay(550);
  }else{
    stop();
    delay(300);
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

void right() {

  digitalWrite(direction1, LOW);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, high1);
  analogWrite(speed2, high1);
}

void stop() {

  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, low);
  analogWrite(speed2, low);
}