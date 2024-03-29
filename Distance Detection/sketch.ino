#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define ECHO 12
#define TRIG 13

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int buzzer = 11;
bool is_beep = false;

void setup() {
  Serial.begin(115200);

  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(buzzer, OUTPUT);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Failed to start SSD1306 OLED"));
    while(true);
  }
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  int time = pulseIn(ECHO, HIGH);
  int distance = time * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  oled.clearDisplay();
  oled.setCursor(0, 2);

  oled.print("Distance: ");
  oled.print(distance);
  oled.println(" cm");
  oled.display();

  if (is_beep == true) {
    is_beep = false;
    noTone(buzzer);
  } else {
    is_beep = true;
    if (distance < 150) {
      tone(buzzer, 100, 1000);
    } else {
      tone(buzzer, 500, 1000);
    }
  }

  delay(distance);
}
