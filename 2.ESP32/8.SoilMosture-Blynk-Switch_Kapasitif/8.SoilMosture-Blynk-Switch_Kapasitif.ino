#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL62_V3tfBN"
#define BLYNK_TEMPLATE_NAME "UJI COBA"
#define BLYNK_AUTH_TOKEN "PJHkhKaCOsoQMIF7X5oi_mZxzKw-DjYA"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Redmi 13C";
char pass[] = "30062007";

#define RELAY_PIN 13

int switchState = 0;  // variabel untuk simpan status dari Blynk

// Callback ini tetap diperlukan untuk update nilai switch
BLYNK_WRITE(V2) {
  switchState = param.asInt();  // simpan nilai (0/1) ke variabel
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  // logika kontrol relay ditaruh di loop
  if (switchState == 1) {
    digitalWrite(RELAY_PIN, LOW);   // relay ON
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // relay OFF
  }
}