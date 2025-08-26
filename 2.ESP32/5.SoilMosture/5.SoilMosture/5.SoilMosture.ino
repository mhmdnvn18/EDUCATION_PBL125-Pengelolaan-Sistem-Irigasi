#include <LCD_I2C.h>
LCD_I2C lcd(0x27, 16, 2);


#define sensorPin 34  // Pin analog ESP32 (misalnya GPIO 34)
void setup() {
  Serial.begin(115200);  // Inisialisasi komunikasi serial

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
  int sensorValue = analogRead(sensorPin);  // Baca nilai analog dari sensor (0 - 4095)
  // Konversi nilai ADC ke persentase kelembaban (0% = kering, 100% = basah)
  // Nilai 0-4095 adalah rentang ADC pada ESP32.
  // Kalibrasi mungkin diperlukan untuk akurasi yang lebih baik pada jenis tanah berbeda.
  float kelembaban = map(sensorValue, 0, 4095, 100, 0);
  // Tampilkan nilai di Serial Monitor
  Serial.print("Nilai ADC: ");
  Serial.print(sensorValue);
  Serial.print(" | Kelembaban: ");
  Serial.print(kelembaban);
  Serial.println(" %");
  delay(1000);  // Tunggu 1 detik sebelum pembacaan berikutnya

  lcd.setCursor(0, 0);
  lcd.print("KELEMBABAN:");
  lcd.setCursor(5, 1);
  lcd.print(kelembaban, 1);
}