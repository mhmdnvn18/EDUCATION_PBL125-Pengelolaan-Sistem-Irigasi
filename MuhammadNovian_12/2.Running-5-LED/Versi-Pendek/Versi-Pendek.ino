#define jumlahled 5  //Jumlah LED

int ledPin[jumlahled] = { 2, 3, 4, 5, 6 };  //pin LED Dari kiri ke kanan

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 5; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
}

void loop() {
  // Menyalakan LED secara berurutan dari kiri ke kanan (maju)
  for (int i = 0; i < jumlahled; i++) {
    digitalWrite(ledPin[i], HIGH);
    delay(500);
    digitalWrite(ledPin[i], LOW);
  };

  // Menyalakan LED secara berurutan dari kanan ke kiri (mundur)
  for (int i = jumlahled - 2; i > 0; i--) {
    digitalWrite(ledPin[i], HIGH);
    delay(500);
    digitalWrite(ledPin[i], LOW);
  }
}