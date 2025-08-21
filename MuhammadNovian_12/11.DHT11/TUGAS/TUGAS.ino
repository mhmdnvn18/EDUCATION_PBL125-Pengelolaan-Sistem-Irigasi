#include <LCD_I2C.h>
#include "DHT.h"

#define DHTPIN 5  // Digital pin connected to the DHT sensor
#define led_1 8
#define led_2 7
#define led_3 6
#define Buzzer 4
#define DHTTYPE DHT11  // DHT 22  (AM2302), AM2321

#define relayPin 2

LCD_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();

  pinMode(Buzzer, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);

  pinMode(relayPin, OUTPUT);

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
  // Wait a few seconds between measurements.
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

  if (t < 25) {
    digitalWrite(led_1, 1);
    digitalWrite(led_2, 0);
    digitalWrite(led_3, 0);

  } else if (t >= 25 && t <= 30) {
    digitalWrite(led_1, 0);
    digitalWrite(led_2, 1);
    digitalWrite(led_3, 0);

  } else {
    (t > 30);
    digitalWrite(led_1, 0);
    digitalWrite(led_2, 0);
    digitalWrite(led_3, 1);
  }
  if (h < 60) {
    lcd.setCursor(0, 1);           // Or setting the cursor in the desired position.
    lcd.print("   POMPA ON    ");  // You can make spaces using well... spaces
    digitalWrite(Buzzer, 1);
    delay(500);

  } else if (h > 60) {
    lcd.setCursor(0, 1);           // Or setting the cursor in the desired position.
    lcd.print("   POMPA OFF   ");  // You can make spaces using well... spaces
    digitalWrite(Buzzer, 0);
    digitalWrite(relayPin, 1);
    delay(500);
  }
}
