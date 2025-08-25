#define LedK 2
#define LedK 3
#define LedK 4
#define LedB 5
#define LedP 6

#define potensioPin A0

void setup() {
  // put your setup code here, to run once:
  pinMode(potensioPin, INPUT);
  pinMode(LedK, OUTPUT);
  pinMode(LedB, OUTPUT);
  pinMode(LedP, OUTPUT);
}

void loop() {
  int nilaiPotensio = analogRead(potensioPin);

  Serial.print("Nilai ADC Potensio =  ");
  Serial.print(nilaiPotensio);

  digitalWrite(LedK, HIGH);
  delay(nilaiPotensio);
  digitalWrite(LedK, LOW);
  delay(nilaiPotensio);

  digitalWrite(LedB, HIGH);
  delay(nilaiPotensio);
  digitalWrite(LedB, LOW);
  delay(nilaiPotensio);

  digitalWrite(LedP, HIGH);
  delay(nilaiPotensio);
  digitalWrite(LedP, LOW);
  delay(nilaiPotensio);
}
