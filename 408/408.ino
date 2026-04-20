#include <Arduino.h>

// PWM 调速：全速用 255。
const uint8_t kMotorPwm = 255;

int speed1 = 5;
int direction1 = 7;
int speed2 = 6;
int direction2 = 4;
const int LEFT_SENSOR  = 2;
const int RIGHT_SENSOR = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(direction1, OUTPUT);
  pinMode(direction2, OUTPUT);
  pinMode(speed1, OUTPUT);
  pinMode(speed2, OUTPUT);

  Serial.begin(9600);
  pinMode(LEFT_SENSOR,  INPUT_PULLUP);
  pinMode(RIGHT_SENSOR, INPUT_PULLUP);
  Serial.println("0=黑 1=白");
}

void loop() {
  // put your main code here, to run repeatedly:
  int L = digitalRead(LEFT_SENSOR);
  int R = digitalRead(RIGHT_SENSOR);
  
  Serial.print("L:");
  Serial.print(L);
  Serial.print(" R:");
  Serial.println(R);
  
  if (L == 0 && R == 0) {
    forward();

  } else if (L == 0 && R == 1) {
    backward();
    left();
    // delay(300);
    // left();
    // delay(300);
  } else if (L == 1 && R == 0) {
    backward();
    // delay(300);
    right();
    // delay(300);
    // delay(300);
    // right();
    // delay(300);

  } else if (L == 1 && R == 1) {
    backward();
    delay(500);
    right();
    delay(300);
  }
}

void forward() {
  digitalWrite(direction1, LOW);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, kMotorPwm); // left
  analogWrite(speed2, kMotorPwm); // right
}

void backward() {
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, kMotorPwm);
  analogWrite(speed2, kMotorPwm);

  // LOW = motor backward && full speed turning counterclockwise
}

void left() {

  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);
  analogWrite(speed1, kMotorPwm);
  analogWrite(speed2, 220);
}

void right() {

  digitalWrite(direction1, LOW);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, kMotorPwm);
  analogWrite(speed2, 220);
}

void stop() {
  digitalWrite(direction1, LOW);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, 0);
  analogWrite(speed2, 0);
}