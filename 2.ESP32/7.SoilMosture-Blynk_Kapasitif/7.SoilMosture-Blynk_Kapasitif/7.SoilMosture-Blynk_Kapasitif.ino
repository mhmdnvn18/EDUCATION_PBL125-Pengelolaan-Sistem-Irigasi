#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6muPlMtcI"
#define BLYNK_TEMPLATE_NAME "BVPV Surakarta"
#define BLYNK_AUTH_TOKEN "HEW65ui7sY0LkCDSX7G6s50JJ9NeJ9Vx"

#include <LCD_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Definisi Pin
#define relayPin 4
#define sensorPin 34
#define pb 5 // Push button pin

// Inisialisasi komponen
LCD_I2C lcd(0x27, 16, 2);
BlynkTimer timer;

// Kredensial WiFi
char ssid[] = "A33";
char pass[] = "12345678";

// Variabel global untuk status
bool pompaStatus = false; // true = ON, false = OFF
bool modeManual = false;  // Menandakan apakah pompa dikontrol manual

// Variabel untuk debouncing tombol
long lastDebounceTime = 0;
long debounceDelay = 50;
int lastButtonState = LOW; // Kondisi awal tombol pull-down adalah LOW

// *** PERUBAHAN UTAMA 1: Logika Relay Active Low ***
#define POMPA_ON LOW
#define POMPA_OFF HIGH

// Fungsi ini akan dipanggil setiap 2 detik oleh BlynkTimer
void cekSensorDanKontrolPompa() {
  // 1. Baca dan konversi nilai sensor
  int adcValue = analogRead(sensorPin);
  float kelembaban = map(adcValue, 3500, 1600, 0, 100);

  if (kelembaban < 0) kelembaban = 0;
  if (kelembaban > 100) kelembaban = 100;

  // 2. Logika kontrol otomatis (HANYA JIKA TIDAK DALAM MODE MANUAL)
  if (!modeManual) {
    if (kelembaban < 50) {
      digitalWrite(relayPin, POMPA_ON);
      pompaStatus = true;
    } else if (kelembaban >= 65) {
      if (pompaStatus) {
        digitalWrite(relayPin, POMPA_OFF);
        pompaStatus = false;
      }
    }
  }

  // 3. Tampilkan informasi ke Serial Monitor
  Serial.print("Nilai ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Kelembaban: ");
  Serial.print(kelembaban);
  Serial.print("% | Pompa: ");
  Serial.print(pompaStatus ? "ON" : "OFF");
  Serial.print(" | Mode: ");
  Serial.println(modeManual ? "Manual" : "Otomatis");
  
  // 4. Tampilkan ke LCD
  lcd.setCursor(0, 0);
  lcd.print("Kelembaban:");
  lcd.setCursor(0, 1);
  lcd.print(kelembaban, 1);
  lcd.print("%    ");
  lcd.setCursor(8, 1);
  lcd.print(pompaStatus ? "ON " : "OFF");

  // 5. Kirim data ke Blynk
  Blynk.virtualWrite(V0, kelembaban);
  Blynk.virtualWrite(V1, pompaStatus ? 255 : 0);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(relayPin, OUTPUT);
  // *** PERUBAHAN UTAMA 2: Konfigurasi Tombol Pull-Down ***
  pinMode(pb, INPUT); 
  
  digitalWrite(relayPin, POMPA_OFF); // Pompa awal OFF

  // Koneksi WiFi & Blynk
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Inisialisasi LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SoilMoisture TES");
  lcd.setCursor(0, 1);
  lcd.print(" BPVP Surakarta ");
  delay(2000);
  lcd.clear();

  // Atur timer untuk menjalankan fungsi utama setiap 2 detik
  timer.setInterval(2000L, cekSensorDanKontrolPompa);
}

void cekTombol() {
  int reading = digitalRead(pb);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // *** PERUBAHAN UTAMA 3: Logika Tombol Pull-Down ***
    // Tombol ditekan jika nilainya HIGH
    if (reading == HIGH && lastButtonState == LOW) {
      modeManual = !modeManual; // Toggle mode Manual/Otomatis

      if(modeManual) {
        digitalWrite(relayPin, POMPA_ON);
        pompaStatus = true;
        Serial.println("Tombol ditekan: Mode MANUAL AKTIF, pompa ON");
      } else {
        digitalWrite(relayPin, POMPA_OFF);
        pompaStatus = false;
        Serial.println("Tombol ditekan: Mode OTOMATIS AKTIF");
      }
    }
  }
  lastButtonState = reading;
}

void loop() {
  Blynk.run();
  timer.run();
  cekTombol();
}