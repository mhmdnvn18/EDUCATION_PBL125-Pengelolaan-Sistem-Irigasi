#include <LCD_I2C.h>
#define TRIG 9
#define ECHO 10

#define led_1 8
#define led_2 7
#define led_3 6
#define led_4 5

#define Buzzer 4


LCD_I2C lcd(0x27, 16, 2);
long durasi;
int jarak;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(Buzzer, OUTPUT);

  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);


  lcd.begin();
  lcd.backlight();
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

  lcd.setCursor(2, 0);   // Or setting the cursor in the desired position.
  lcd.print("Jarak: ");  // You can make spaces using well... spaces
  lcd.setCursor(8, 0);   // Or setting the cursor in the desired position.
  lcd.print(jarak);      // You can make spaces using well... spaces

  if (jarak > 50) {
    digitalWrite(led_1, 1);
    digitalWrite(led_2, 0);
    digitalWrite(led_3, 0);
    digitalWrite(led_4, 0);

    lcd.setCursor(5, 1);  // Or setting the cursor in the desired position.
    lcd.print("AMAN");    // You can make spaces using well... spaces
    delay(500);

    lcd.backlight();
    lcd.clear();
    delay(100);

  } else if (jarak >= 10 && jarak <= 30) {
    digitalWrite(led_1, 1);
    digitalWrite(led_2, 1);
    digitalWrite(led_3, 0);
    digitalWrite(led_4, 0);

    lcd.setCursor(1, 1);  // Or setting the cursor in the desired position.
    lcd.print("Hati - Hati");
    delay(500);

    lcd.backlight();
    lcd.clear();
    delay(100);

  } else if (jarak < 10) {
    digitalWrite(led_1, 1);
    digitalWrite(led_2, 1);
    digitalWrite(led_3, 1);
    digitalWrite(led_4, 1);

    lcd.setCursor(4, 1);   // Or setting the cursor in the desired position.
    lcd.print("STOP !!");  // You can make spaces using well... spaces
    digitalWrite(Buzzer, 1);
    delay(500);
    digitalWrite(Buzzer, 0);

    lcd.backlight();
    lcd.clear();
    delay(100);
  }
}