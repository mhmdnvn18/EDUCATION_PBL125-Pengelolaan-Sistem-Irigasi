#define ledPin 6  //Jumlah LED


void setup() {
  // put your setup code here, to run once:
  //pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(ledPin, 0);
  delay(200);
  analogWrite(ledPin, 51);
  delay(200);
  analogWrite(ledPin, 102);
  delay(200);
  analogWrite(ledPin, 204);
  delay(200);
  analogWrite(ledPin, 255);
  delay(200);
}
