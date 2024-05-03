#define BLYNK_TEMPLATE_ID "TMPLxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "IoT Monitoring System"
#define BLYNK_AUTH_TOKEN "AUTH_TOKEN"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

int pinledR = 26;
int pinledB = 27;
DHT dht(19, DHT22);

void sendSensor() {
  float temp = dht.readTemperature();

  if (temp >= 35) {
    digitalWrite(pinledR, HIGH);
    digitalWrite(pinledB, LOW);
    Serial.println("Getting red");
    Blynk.virtualWrite(V0, 1);
    Blynk.virtualWrite(V1, "HOT");
    Blynk.virtualWrite(V2, 0);
  } else if (temp >= 10 && temp < 35) {
    digitalWrite(pinledR, LOW);
    digitalWrite(pinledB, LOW);
    Serial.println("Temperature is safe");
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, "SAFE");
    Blynk.virtualWrite(V2, 0);
  } else {
    digitalWrite(pinledR, LOW);
    digitalWrite(pinledB, HIGH);
    Serial.println("Getting blue");
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, "COOL");
    Blynk.virtualWrite(V2, 1);
  }

  Blynk.virtualWrite(V3, temp);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(pinledR, OUTPUT);
  pinMode(pinledB, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000); // this speeds up the simulation
  Blynk.run();
  sendSensor();
}
