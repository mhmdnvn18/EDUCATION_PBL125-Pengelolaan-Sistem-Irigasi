#include <LCD_I2C.h>
#define TRIG 9
#define ECHO 10
LCD_I2C lcd(0x27, 16, 2);
long durasi;
int jarak;
void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  lcd.setCursor(0, 0);
  lcd.print(" Ultrasonik Tes ");
  lcd.setCursor(0, 1);
  lcd.print(" BPVP Surakarta ");
  delay(2000);
  lcd.clear();
}
void loop() {
  // Kirim sinyal trigger
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  // Baca durasi pantulan
  durasi = pulseIn(ECHO, HIGH);
  // Hitung jarak (cm)
  jarak = durasi * 0.034 / 2;
  // Tampilkan di LCD
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(jarak);
  lcd.print(" cm ");
  delay(500);
}
