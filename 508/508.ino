#include <Arduino.h>
#include <SharpDistSensor.h>

// PWM 调速：HIGH 只是数值 1，占空比太低，电机往往看起来“完全不动”。全速用 255。
const uint8_t high = 240;
const uint8_t high1 = 255;
const uint8_t low = 0;
const byte medianFilterWindowSize = 5;
const byte LEFT_DIST_SENSOR_PIN = A0;
const byte RIGHT_DIST_SENSOR_PIN = A2;
const unsigned int TARGET_DISTANCE_MM = 400;
const int WHITE = HIGH;

SharpDistSensor leftDistSensor(LEFT_DIST_SENSOR_PIN, medianFilterWindowSize);
SharpDistSensor rightDistSensor(RIGHT_DIST_SENSOR_PIN, medianFilterWindowSize);

int LeftSensor=3;
int RightSensor=2;
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
  int leftLine = digitalRead(LeftSensor);
  int rightLine = digitalRead(RightSensor);
  int leftRaw = analogRead(LEFT_DIST_SENSOR_PIN);
  int rightRaw = analogRead(RIGHT_DIST_SENSOR_PIN);
  unsigned int leftDistance = leftDistSensor.getDist();
  unsigned int rightDistance = rightDistSensor.getDist();
  bool leftWhite = leftLine == WHITE;
  bool rightWhite = rightLine == WHITE;
  bool leftSeen = leftDistance < TARGET_DISTANCE_MM;
  bool rightSeen = rightDistance < TARGET_DISTANCE_MM;

  Serial.print("L:");
  Serial.print(leftLine);
  Serial.print(" R:");
  Serial.print(rightLine);
  Serial.print(" A0:");
  Serial.print(leftRaw);
  Serial.print(",");
  Serial.print(leftDistance);
  Serial.print("mm A2:");
  Serial.print(rightRaw);
  Serial.print(",");
  Serial.print(rightDistance);
  Serial.println("mm");

  if (leftWhite || rightWhite) {
    backward();
    delay(100);

    if (leftWhite && !rightWhite) {
      right();
    } else {
      left();
    }

    delay(500);
    return;
  }

  if (leftSeen && !rightSeen) {
    left();
  } else if (rightSeen && !leftSeen) {
    right();
  } else {
    forward();
  }

}

void forward() {
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, LOW);
  analogWrite(speed1, high);
  analogWrite(speed2, high);
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
