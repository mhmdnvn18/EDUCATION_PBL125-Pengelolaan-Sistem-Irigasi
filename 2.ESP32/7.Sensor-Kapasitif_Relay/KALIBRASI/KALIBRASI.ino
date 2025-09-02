#define sensorPin 34  // ADC pin untuk sensor
void setup() {
  Serial.begin(115200);
}
void loop() {
  int adcValue = analogRead(sensorPin);  // 0 - 4095
  float kelembaban = map(adcValue, 3500, 1600, 0, 100);
  // 3900 = kering, 1500 = basah (butuh kalibrasi nyata)
  if (kelembaban < 0) kelembaban = 0;
  if (kelembaban > 100) kelembaban = 100;
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Kelembaban: ");
  Serial.print(kelembaban);
  Serial.println(" %");
  delay(1000);
}
