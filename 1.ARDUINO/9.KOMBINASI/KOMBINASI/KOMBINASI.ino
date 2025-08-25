#define tombol1Pin 4
#define tombol2Pin 7
#define ledPin 2

void setup() {
  pinMode(tombol1Pin, INPUT);
  pinMode(tombol2Pin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int kondisiTombol1 = digitalRead(tombol1Pin);
  int kondisiTombol2 = digitalRead(tombol2Pin);

  if (kondisiTombol1 == HIGH) {
    digitalWrite(ledPin, HIGH);
    while(digitalRead(tombol1Pin) == HIGH) {}
  } 
  if (kondisiTombol2 == LOW) {
    digitalWrite(ledPin, LOW);
    while(digitalRead(tombol2Pin) == LOW) {}
  }
}