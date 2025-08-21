#include <LCD_I2C.h>

#define Buzzer 4

LCD_I2C lcd(0x27, 16, 2);  // Default address of most PCF8574 modules, change according

void setup() {
  lcd.begin();  // If you are using more I2C devices using the Wire library use lcd.begin(false)
  lcd.backlight();
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  lcd.setCursor(1, 0);           // Or setting the cursor in the desired position.
  lcd.print("MUHAMMAD NOVIAN");  // You can make spaces using well... spaces
  lcd.setCursor(1, 1);           // Or setting the cursor in the desired position.
  lcd.print("No. Absen 12");
  delay(1000);
  lcd.backlight();
  lcd.clear();
  delay(500);

  lcd.setCursor(3, 0);           // Or setting the cursor in the desired position.
  lcd.print("Auto-Matic");  // You can make spaces using well... spaces
  lcd.setCursor(3, 1);           // Or setting the cursor in the desired position.
  lcd.print("Irrigation");
  delay(1000);
  lcd.backlight();
  lcd.clear();
  delay(500);

  lcd.setCursor(1, 0);         // Or setting the cursor in the desired position.
  lcd.print("Smart Farming");  // You can make spaces using well... spaces
  lcd.setCursor(1, 1);         // Or setting the cursor in the desired position.
  lcd.print("BPVP Surakarta");
  delay(1000);
  lcd.backlight();
  lcd.clear();
  delay(500);
}
