const int potensioPin = A0;
const int ledPin5 = 5;
const int ledPin2 = 2;
const int ledPin3 = 3;
const int ledPin4 = 4;

void setup() {
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int nilaiADC = analogRead(potensioPin);

  int brightness = map(nilaiADC, 0, 1023, 0, 255);
  analogWrite(ledPin5, brightness);

  Serial.print("Nilai ADC Potensio: ");
  Serial.println(nilaiADC);

  if (nilaiADC < 255) {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    Serial.println("Semua LED mati.");
  } else if (nilaiADC >= 255 && nilaiADC <= 511) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    Serial.println("LED Pin 2 menyala.");
  } else if (nilaiADC >= 512 && nilaiADC <= 767) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, LOW);
    Serial.println("LED Pin 2 & 3 menyala.");
  } else if (nilaiADC > 767) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    Serial.println("Semua LED menyala.");
  }
  
  delay(100);
}