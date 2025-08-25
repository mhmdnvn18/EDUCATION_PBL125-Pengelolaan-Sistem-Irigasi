#define potensioPin A0
#define LedM 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LedM, OUTPUT);
}

void loop() {
  //float nilaiPotensio = analogRead(potensioPin);
  //int nilaiPWM = map(nilaiPotensio, 0, 1023, 0, 255); //Alternatif menggunakan map

  float nilaiPotensio = analogRead(potensioPin);  
  float nilaiPWM = (nilaiPotensio * 255) / 1023;

  Serial.print("Nilai ADC Potensio: ");
  Serial.println(nilaiPotensio);

  Serial.print("nilaiPWM:  ");
  Serial.println(nilaiPWM);
  delay(1000);
}
