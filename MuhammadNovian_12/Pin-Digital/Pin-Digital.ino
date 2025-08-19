#define ledPin 3

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("LED NYALA");
  delay(500);            // wait for a second
  digitalWrite(ledPin, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("LED MATI");
  delay(500);  // wait for a second
}
