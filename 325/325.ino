#include <Arduino.h>

// PWM 调速：HIGH 只是数值 1，占空比太低，电机往往看起来“完全不动”。全速用 255。
const uint8_t kMotorPwm = 255;

int speed1 = 5;
int direction1 = 4;
int speed2 = 6;
int direction2 = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(direction1, OUTPUT);
  pinMode(direction2, OUTPUT);
  pinMode(speed1, OUTPUT);
  pinMode(speed2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  forward();
  delay(3000);
  backward();
  delay(3000);
  left();
  delay(500);
  right();
  delay(500);
  stop();
  delay(5000);
}

void forward() {
  digitalWrite(direction1, LOW);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, kMotorPwm);
  analogWrite(speed2, kMotorPwm);
}

void backward() {
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, kMotorPwm);
  analogWrite(speed2, kMotorPwm);

  // LOW = motor backward && full speed turning counterclockwise
}

void left() {

  digitalWrite(direction1, LOW);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, kMotorPwm);
  analogWrite(speed2, kMotorPwm);
}

void right() {

  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, kMotorPwm);
  analogWrite(speed2, kMotorPwm);
}

void stop() {
  digitalWrite(direction1, LOW);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, 0);
  analogWrite(speed2, 0);
}