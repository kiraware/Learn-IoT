#include <DHT.h>

DHT dht(14, DHT22);

int ledRed = 18;
int ledBlue = 5;
int ledGreen = 16;

int pinBuz = 4;

void setup() {
  Serial.begin(2000);

  dht.begin();

  pinMode(ledRed, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  ledcAttachPin(pinBuz, 0);
}

void loop() {
  float temperature = dht.readTemperature();

  if (temperature > 40 || temperature < 10) {
    // critical
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledGreen, LOW);

    noTone(pinBuz);
    delay(100);
    tone(pinBuz, 1200);
  } else if (temperature > 35) {
    // high
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledGreen, LOW);

    tone(pinBuz, 800);
  } else if (temperature > 14) {
    // normal
    digitalWrite(ledRed, LOW);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledGreen, HIGH);

    tone(pinBuz, 0);
  } else {
    // low
    digitalWrite(ledRed, LOW);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledGreen, LOW);

    tone(pinBuz, 800);
  }

  delay(500); 
}
