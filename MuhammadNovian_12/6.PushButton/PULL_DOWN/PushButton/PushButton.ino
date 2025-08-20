#define tombolPin 4  //PullDown
#define tombolPin 6  //PullUp
#define ledPin 2

void setup() {
  // put your setup code here, to run once:
  pinMode(tombolPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int kondisiTombol = digitalRead(tombolPin);
  if (kondisiTombol == LOW) {
    digitalWrite(ledPin, LOW);
  } else (digitalWrite(ledPin, HIGH));
}