#define tombolPin 4
#define ledPin 2

void setup() {
  // put your setup code here, to run once:
  pinMode(tombolPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int kondisiTombol = digitalRead(tombolPin);
  if (kondisiTombol == HIGH) {
    digitalWrite(ledPin, 1);
    delay(50);
    digitalWrite(ledPin,0);
    delay(50);
  } else (kondisiTombol == LOW);
  digitalWrite(ledPin, 1);
}
