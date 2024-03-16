#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dht(23, DHT22);

int redLed = 33;
int blueLed = 32;
int buzzPin = 25;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Failed to start SSD1306 OLED"));
    while (1);
  }

  dht.begin();

  pinMode(redLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  ledcAttachPin(buzzPin, 0);

  oled.setTextSize(1);
  oled.setTextColor(WHITE);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000); // this speeds up the simulation

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (t >= 50) {
    digitalWrite(redLed, HIGH);
    delay(500);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);

    oled.clearDisplay();
    oled.setCursor(0, 2);

    oled.print("Temperature: ");
    oled.println(t);
    oled.print("Humidity: ");
    oled.println(h);
    oled.display();

    ledcWriteNote(0, NOTE_F, 4);
    Serial.println("hot");
  } else if (t < 50) {
    digitalWrite(blueLed, HIGH);
    delay(500);
    digitalWrite(redLed, LOW);
    digitalWrite(blueLed, LOW);

    oled.clearDisplay();
    oled.setCursor(0, 2);

    oled.print("Temperature: ");
    oled.println(t);
    oled.print("Humidity: ");
    oled.println(h);
    oled.display();

    ledcWriteNote(0, NOTE_A, 4);
    Serial.println("cold");
  }
}
