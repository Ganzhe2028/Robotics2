// =============================================
// Sensor Diagnostic Test - 传感器诊断测试
// 左传感器: Pin 2 | 右传感器: Pin 3
// 打开 Serial Monitor (波特率 9600)
// =============================================

#include <Arduino.h>

const int LEFT_SENSOR  = 2;  // 左传感器
const int RIGHT_SENSOR = 3;  // 右传感器

void setup() {
  Serial.begin(9600);
  // INPUT_PULLUP: 内部启用上拉电阻，悬空时读 HIGH
  // 如果传感器信号线是开漏输出(open-drain)，需要用这个模式
  pinMode(LEFT_SENSOR,  INPUT_PULLUP);
  pinMode(RIGHT_SENSOR, INPUT_PULLUP);

  Serial.println("=== 传感器诊断测试 ===");
  Serial.println("模式: INPUT_PULLUP");
  Serial.println("格式: 左[数字/模拟] | 右[数字/模拟]");
  Serial.println("用手或黑色物体遮住传感器，观察读值变化");
  Serial.println("-------------------------------------------");
}

void loop() {
  int leftDigital  = digitalRead(LEFT_SENSOR);
  int rightDigital = digitalRead(RIGHT_SENSOR);
  int leftAnalog   = analogRead(LEFT_SENSOR);   // A2 对应 Pin 2（Uno）
  int rightAnalog  = analogRead(RIGHT_SENSOR);  // A3 对应 Pin 3

  // 打印数字读值
  Serial.print("左 Pin ");
  Serial.print(LEFT_SENSOR);
  Serial.print(": 数字=");
  Serial.print(leftDigital);
  Serial.print("  |  右 Pin ");
  Serial.print(RIGHT_SENSOR);
  Serial.print(": 数字=");
  Serial.println(rightDigital);

  // 打印模拟读值（检查是否有信号变化）
  Serial.print("   模拟左=");
  Serial.print(leftAnalog);
  Serial.print("  模拟右=");
  Serial.println(rightAnalog);
  Serial.println("-------------------------------------------");

  delay(500);
}
