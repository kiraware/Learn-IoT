#define BLYNK_TEMPLATE_ID "TMPLxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "Pest Detector"
#define BLYNK_AUTH_TOKEN "AUTH_TOKEN"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define ECHO 12
#define TRIG 13

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

int buzzer = 23;
bool is_beep = true;
bool is_notify = true;

BLYNK_WRITE(V1) 
{
  is_beep = param.asInt();
}

BLYNK_WRITE(V2) 
{
  is_notify = param.asInt();
}

void setup() {
  Serial.begin(115200);

  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Blynk.begin(auth, ssid, pass);
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

  if (distance <= 200) {
    if (is_beep) {
      tone(buzzer, 500, 1000);
    } else {
      noTone(buzzer);
    }

    if (is_notify) {
      Blynk.virtualWrite(V0, "There are Pests!");
    } else {
      Blynk.virtualWrite(V0, " ");
    }
  } else {
    noTone(buzzer);
    Blynk.virtualWrite(V0, " ");
  }

  delay(500);
}