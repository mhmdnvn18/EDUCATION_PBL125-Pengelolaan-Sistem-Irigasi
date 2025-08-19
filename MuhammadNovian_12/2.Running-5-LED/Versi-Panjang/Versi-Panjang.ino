#define ledM 2
#define ledK 3
#define ledH 4
#define ledB 5
#define ledP 6

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledM, OUTPUT);
  pinMode(ledK, OUTPUT);
  pinMode(ledH, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledP, OUTPUT);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledM, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("LED MERAH NYALA");
  delay(500);
  digitalWrite(ledM, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("LED MERAH MATI");
  digitalWrite(ledK, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("LED KUNING NYALA");
  delay(500);
  digitalWrite(ledK, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("LED KUNING MATI");
  digitalWrite(ledH, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("LED HIJAU NYALA");
  delay(500);
  digitalWrite(ledH, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("LED HIJAU MATI");
  digitalWrite(ledB, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("LED BIRU NYALA");
  delay(500);
  digitalWrite(ledB, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("LED BIRU MATI");
  digitalWrite(ledP, HIGH);  // turn the LED on (HIGH is the voltage level)
  Serial.println("LED PUTIH NYALA");
  delay(500);
  digitalWrite(ledP, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("LED PUTIH MATI");
}
