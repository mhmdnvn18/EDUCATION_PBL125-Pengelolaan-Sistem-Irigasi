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
  if (kondisiTombol == LOW) {
    digitalWrite(ledPin, HIGH);
  } else (digitalWrite(ledPin, LOW));
}
