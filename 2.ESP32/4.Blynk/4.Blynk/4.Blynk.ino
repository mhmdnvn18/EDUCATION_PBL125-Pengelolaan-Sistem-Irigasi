#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6muPlMtcI"
#define BLYNK_TEMPLATE_NAME "BVPV Surakarta"
#define BLYNK_AUTH_TOKEN "HEW65ui7sY0LkCDSX7G6s50JJ9NeJ9Vx"


#define DHTTYPE DHT22  // Tipe DHT22

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LCD_I2C.h>
#include "DHT.h"
#define DHTPIN 4  // Digital pin connected to the DHT sensor

LCD_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

char ssid[] = "A33";
char pass[] = "12345678";

void setup() {
  // Debug console
  Serial.begin(115200);
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

  Serial.println(F("DHTxx test!"));
  dht.begin();

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   DHT11 TEST   ");
  lcd.setCursor(0, 1);
  lcd.print(" BPVP Surakarta ");
  delay(2000);
  lcd.clear();
}

void loop() {
  Blynk.run();

  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.setCursor(2, 0);
  lcd.print(h, 1);
  lcd.setCursor(6, 0);
  lcd.print((char)223);

  lcd.setCursor(9, 0);
  lcd.print("T:");
  lcd.setCursor(11, 0);
  lcd.print(t, 1);
  lcd.setCursor(15, 0);
  lcd.print("C");


  Blynk.virtualWrite(V1, Suhu);
  Blynk.virtualWrite(V0, Kelembaban);
}
