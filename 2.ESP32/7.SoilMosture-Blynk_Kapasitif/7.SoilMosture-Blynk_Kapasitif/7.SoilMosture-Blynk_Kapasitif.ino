#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6muPlMtcI"
#define BLYNK_TEMPLATE_NAME "BVPV Surakarta"
#define BLYNK_AUTH_TOKEN "HEW65ui7sY0LkCDSX7G6s50JJ9NeJ9Vx"

#include <LCD_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define relayPin 4
#define sensorPin 34

LCD_I2C lcd(0x27, 16, 2);
bool pompaStatus = false;

char ssid[] = "A33";
char pass[] = "12345678";
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Pompa awal OFF

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SoilMoisture TES");
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
  Serial.print("Kelembaban: ");
  Serial.print(kelembaban);
  Serial.println(" %");
  // Logika otomatisasi
  if (kelembaban < 50) {  // Jika <50% ³ Nyalakan pompa
    digitalWrite(relayPin, HIGH);
    pompaStatus = true;
  } else if (kelembaban >= 65) {  // Jika sudah >=65% ³ Matikan pompa
    digitalWrite(relayPin, LOW);
    pompaStatus = false;
  }
  Serial.print("Pompa: ");
  Serial.println(pompaStatus ? "ON" : "OFF");
  delay(2000);

  Serial.print("Nilai ADC: ");
  Serial.print(sensorPin);
  Serial.print(" | Kelembaban: ");
  Serial.print(kelembaban);
  Serial.println(" %");

  lcd.setCursor(2, 0);
  lcd.print("KELEMBABAN:   ");
  lcd.setCursor(5, 1);
  lcd.print(kelembaban, 1);
  lcd.print("%   ");

  Blynk.virtualWrite(V0, kelembaban);
  Blynk.run();
}