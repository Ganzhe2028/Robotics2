#include <Arduino.h>

const uint8_t LEFT_SENSOR = 2;
const uint8_t RIGHT_SENSOR = 3;

const uint8_t SPEED1 = 5;
const uint8_t DIRECTION1 = 4;
const uint8_t SPEED2 = 6;
const uint8_t DIRECTION2 = 7;

const uint8_t WHITE = HIGH;  // sensor reads 1 on the white border

const uint8_t ATTACK_PWM = 255;
const uint8_t TURN_PWM = 220;

const unsigned long BACK_OFF_MS = 550;
const unsigned long TURN_BACK_MS = 320;
const unsigned long BOTH_EDGE_TURN_MS = 420;
const unsigned long LOG_INTERVAL_MS = 200;

bool turnRightNext = true;
unsigned long lastLogMs = 0;

void setup() {
  Serial.begin(9600);

  pinMode(LEFT_SENSOR, INPUT_PULLUP);
  pinMode(RIGHT_SENSOR, INPUT_PULLUP);

  pinMode(SPEED1, OUTPUT);
  pinMode(DIRECTION1, OUTPUT);
  pinMode(SPEED2, OUTPUT);
  pinMode(DIRECTION2, OUTPUT);

  Serial.println("sumo mode: 0=black arena, 1=white border");
}

void loop() {
  int left = digitalRead(LEFT_SENSOR);
  int right = digitalRead(RIGHT_SENSOR);

  logSensors(left, right);

  if (left == WHITE && right == WHITE) {
    escapeBothSensors();
  } else if (left == WHITE) {
    escapeLeftSensor();
  } else if (right == WHITE) {
    escapeRightSensor();
  } else {
    attackForward();
  }
}

void logSensors(int left, int right) {
  unsigned long now = millis();
  if (now - lastLogMs < LOG_INTERVAL_MS) {
    return;
  }

  lastLogMs = now;
  Serial.print("L:");
  Serial.print(left);
  Serial.print(" R:");
  Serial.println(right);
}

void escapeLeftSensor() {
  backOff();
  turnRight();
  delay(TURN_BACK_MS);
}

void escapeRightSensor() {
  backOff();
  turnLeft();
  delay(TURN_BACK_MS);
}

void escapeBothSensors() {
  backOff();

  if (turnRightNext) {
    turnRight();
  } else {
    turnLeft();
  }

  turnRightNext = !turnRightNext;
  delay(BOTH_EDGE_TURN_MS);
}

void backOff() {
  backward();
  delay(BACK_OFF_MS);
}

void attackForward() {
  forward();
}

void forward() {
  digitalWrite(DIRECTION1, HIGH);
  digitalWrite(DIRECTION2, LOW);
  analogWrite(SPEED1, ATTACK_PWM);
  analogWrite(SPEED2, ATTACK_PWM);
}

void backward() {
  digitalWrite(DIRECTION1, LOW);
  digitalWrite(DIRECTION2, HIGH);
  analogWrite(SPEED1, ATTACK_PWM);
  analogWrite(SPEED2, ATTACK_PWM);
}

void turnLeft() {
  digitalWrite(DIRECTION1, HIGH);
  digitalWrite(DIRECTION2, HIGH);
  analogWrite(SPEED1, ATTACK_PWM);
  analogWrite(SPEED2, TURN_PWM);
}

void turnRight() {
  digitalWrite(DIRECTION1, LOW);
  digitalWrite(DIRECTION2, LOW);
  analogWrite(SPEED1, ATTACK_PWM);
  analogWrite(SPEED2, TURN_PWM);
}
