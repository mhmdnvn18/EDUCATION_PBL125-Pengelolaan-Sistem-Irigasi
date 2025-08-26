#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6muPlMtcI"
#define BLYNK_TEMPLATE_NAME "BVPV Surakarta"
#define BLYNK_AUTH_TOKEN "HEW65ui7sY0LkCDSX7G6s50JJ9NeJ9Vx"

#include <LCD_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

LCD_I2C lcd(0x27, 16, 2);

char ssid[] = "A33";
char pass[] = "12345678";

#define relayPin 4
#define sensorPin 34

BlynkTimer timer;

void bacaSensor() {
  int sensorValue = analogRead(sensorPin);
  float kelembaban = map(sensorValue, 0, 4095, 100, 0);

  Blynk.virtualWrite(V0, kelembaban);

  Serial.print("Nilai ADC: ");
  Serial.print(sensorValue);
  Serial.print(" | Kelembaban: ");
  Serial.print(kelembaban);
  Serial.println(" %");

  lcd.setCursor(2, 0);
  lcd.print("KELEMBABAN:   ");
  lcd.setCursor(5, 1);
  lcd.print(kelembaban, 1);
  lcd.print("%   ");

  if (kelembaban < 50) {
    digitalWrite(relayPin, LOW);  // active LOW
    Serial.println("NYALA");
  }
  
  else(kelembaban > 65); {
      digitalWrite(relayPin, HIGH);
      Serial.println("MATI");
    }
}

void setup() {
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SoilMoisture TEs");
  lcd.setCursor(0, 1);
  lcd.print(" BPVP Surakarta ");
  delay(2000);
  lcd.clear();

  pinMode(relayPin, OUTPUT);

  timer.setInterval(1000L, bacaSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
