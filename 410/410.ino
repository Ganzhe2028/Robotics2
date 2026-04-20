#include <Arduino.h>
// #include <SharpDistSensor>

// PWM 调速：HIGH 只是数值 1，占空比太低，电机往往看起来“完全不动”。全速用 255。
const uint8_t high = 238;
const uint8_t high1 = 245;
const uint8_t low = 0;

int LeftSensor=2;
int RightSensor=3;
int speed1 = 5;
int direction1 = 4;
int speed2 = 6;
int direction2 = 7;

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
  }else if(((digitalRead(LeftSensor))==1)&&((digitalRead(RightSensor))==0)){
    backward();
    // delay(200); 
    // right();
    // delay(200);
    // forward();
    // delay(100);
  }else if(((digitalRead(LeftSensor))==0)&&((digitalRead(RightSensor))==1)){
    backward();
    // delay(200); 
    // left();
    // delay(200);
    // forward();
    // delay(100);
  }else{
    backward();
    // delay(200); 
    // left();
    // delay(400);
    // forward();
    // delay(100);
  }
}

void forward() {
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, high1);
  analogWrite(speed2, high);
}

void backward() {
  digitalWrite(direction1, LOW);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, high1);
  analogWrite(speed2, high);

  // LOW = motor backward && full speed turning counterclockwise
}

void left() {

  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, high1);
  analogWrite(speed2, high);
}

void right() {

  digitalWrite(direction1, LOW);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, high1);
  analogWrite(speed2, high);
}

void stop() {

  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, low);
  analogWrite(speed2, low);
}