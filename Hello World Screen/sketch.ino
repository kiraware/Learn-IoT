#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// lebar_layar, tinggi_layar, objek_scl pin_reset
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000); // atur kecepatan transfer data ISC menjadi 400 kHz

  // inisialisasi Oled display dengan alamat ISC 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Failed to start SSD1306 OLED"));
    while (1);
  }

  delay(1000);
  oled.clearDisplay(); // membersihkan tampilan

  oled.setTextSize(1); // ukuran teks
  oled.setTextColor(WHITE); // warna teks
  oled.setCursor(0, 2); // posisi tampilan (x, y)

  // print text
  oled.println("Hello World!");
  oled.display(); // memunculkan tampilan
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}
