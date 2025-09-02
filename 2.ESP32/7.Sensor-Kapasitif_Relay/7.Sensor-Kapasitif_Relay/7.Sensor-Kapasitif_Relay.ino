#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6muPlMtcI"
#define BLYNK_TEMPLATE_NAME "BVPV Surakarta"
#define BLYNK_AUTH_TOKEN "HEW65ui7sY0LkCDSX7G6s50JJ9NeJ9Vx"

#include <LCD_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;
LCD_I2C lcd(0x27, 16, 2);

char ssid[] = "A33";
char pass[] = "12345678";

#define sensorPin 34  // ADC pin
#define relayPin 4    // GPIO relay
bool pompaStatus = false;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Pompa awal OFF

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SoilMoisture TEs");
  lcd.setCursor(0, 1);
  lcd.print(" BPVP Surakarta ");
  delay(2000);
  lcd.clear();
}
void loop() {
  int adcValue = analogRead(sensorPin);
  float kelembaban = map(adcValue, 3500, 1600, 0, 100);
  if (kelembaban < 0) kelembaban = 0;
  if (kelembaban > 100) kelembaban = 100;

  Blynk.virtualWrite(V0, kelembaban);
  Blynk.virtualWrite(V1, pompaStatus ? "ON" : "OFF");

  // Logika otomatisasi
  if (kelembaban < 45) {
    digitalWrite(relayPin, 0);
    pompaStatus = true;

  } else if (kelembaban >= 65) {
    digitalWrite(relayPin, 1);
    pompaStatus = false;
  }

// Dari file yang sudah diperbaiki:
  lcd.setCursor(0, 0);
  lcd.print("Soil: ");
  lcd.print(kelembaban);
  lcd.print("%   "); // Beri spasi untuk membersihkan karakter sisa

  lcd.setCursor(0, 1);
  lcd.print("Pump:           ");
  lcd.setCursor(6, 1);
  lcd.print(pompaStatus ? "ON" : "OFF");


  Serial.print("Kelembaban: ");
  Serial.print(kelembaban);
  Serial.println(" %");
  Serial.print("Pompa: ");
  Serial.println(pompaStatus ? "ON" : "OFF");
  delay(2000);
}