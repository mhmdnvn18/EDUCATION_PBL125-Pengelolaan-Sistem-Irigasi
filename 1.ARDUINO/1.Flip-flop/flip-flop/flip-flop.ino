#define ledM 5
#define ledH 3

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledM, OUTPUT);
  pinMode(ledH, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledM, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("LED MERAH NYALA");
  delay(500);               // wait for a second
  digitalWrite(ledM, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("LED MERAH MATI");
  delay(500);                // wait for a second
  digitalWrite(ledH, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("LED HIJAU NYALA");
  delay(500);               // wait for a second
  digitalWrite(ledH, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("LED HIJAU MATI");
  delay(500);  // wait for a second
}
