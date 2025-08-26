#define sensorPin 34  // ADC pin
#define relayPin 4    // GPIO relay
bool pompaStatus = false;
void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);  // Pompa awal OFF
}
void loop() {
  int adcValue = analogRead(sensorPin);
  float kelembaban = map(adcValue, 3500, 1600, 0, 100);
  if (kelembaban < 0) kelembaban = 0;
  if (kelembaban > 100) kelembaban = 100;
  Serial.print("Kelembaban: ");
  Serial.print(kelembaban);
  Serial.println(" %");
  // Logika otomatisasi
  if (kelembaban < 50) {  // Jika <50% ³ Nyalakan pompa
    digitalWrite(relayPin, HIGH);
    pompaStatus = true;
  } else if (kelembaban >= 65) {  // Jika sudah >=65% ³ Matikan pompa
    digitalWrite(relayPin, LOW);
    pompaStatus = false;
  }
  Serial.print("Pompa: ");
  Serial.println(pompaStatus ? "ON" : "OFF");
  delay(2000);
}