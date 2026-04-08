// =============================================
// Minimal Sensor Test - 最小化传感器测试
// 左: Pin 2 | 右: Pin 3
// Serial Monitor (9600)
// =============================================

const int LEFT_SENSOR  = 2;
const int RIGHT_SENSOR = 3;

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_SENSOR,  INPUT_PULLUP);
  pinMode(RIGHT_SENSOR, INPUT_PULLUP);
  Serial.println("L:左 R:右 (0=遮住 1=光亮)");
}

void loop() {
  int L = digitalRead(LEFT_SENSOR);
  int R = digitalRead(RIGHT_SENSOR);
  
  Serial.print("L:");
  Serial.print(L);
  Serial.print(" R:");
  Serial.println(R);
  
  delay(200);
}