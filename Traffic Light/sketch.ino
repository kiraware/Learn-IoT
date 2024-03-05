int leftR = 25, leftY = 26, leftG = 27;
int rightR = 23, rightY = 22, rightG = 21;
int downR = 14, downY = 12, downG = 13;

void setup() {
  pinMode(leftR, OUTPUT);
  pinMode(leftY, OUTPUT);
  pinMode(leftG, OUTPUT);

  pinMode(rightR, OUTPUT);
  pinMode(rightY, OUTPUT);
  pinMode(rightG, OUTPUT);

  pinMode(downR, OUTPUT);
  pinMode(downY, OUTPUT);
  pinMode(downG, OUTPUT);
}

void setTrafficLight(int first, int second, int third) {
  digitalWrite(first, HIGH);
  digitalWrite(second, HIGH);
  digitalWrite(third, HIGH);
  delay(1000);
  digitalWrite(first, LOW);
  digitalWrite(second, LOW);
  digitalWrite(third, LOW);

}

void loop() {
  setTrafficLight(leftR, rightR, downG);
  setTrafficLight(leftR, rightY, downY);
  setTrafficLight(leftR, rightG, downR);
  setTrafficLight(leftY, rightY, downR);
  setTrafficLight(leftG, rightR, downR);
  setTrafficLight(leftY, rightR, downY);
}
