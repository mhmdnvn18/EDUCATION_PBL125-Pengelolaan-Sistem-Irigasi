#include <Wire.h>
#include <LCD_I2C.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h> // <-- Pustaka BARU untuk menyimpan pengaturan
#include "webpage.h"

LCD_I2C lcd(0x27, 16, 2);
Preferences preferences; // <-- Objek BARU untuk mengakses memori

// ====== Konfigurasi Jaringan & IP Statis ======
const char* ssid = "KontrolPompaESP32";
const char* password = "12345678";
IPAddress local_IP(192, 168, 5, 1);
IPAddress gateway(192, 168, 5, 1);
IPAddress subnet(255, 255, 255, 0);

// ====== Pin assignment ======
#define sensor1 34
#define sensor2 35
#define sensor3 32
#define sensor4 33
#define relay1 4
#define relay2 5
#define relay3 18
#define relay4 19

// ====== Konstanta & Variabel ======
const int ADC_DISCONNECTED_THRESHOLD = 4000;
const bool RELAY_ACTIVE_LOW = false;

// Histeresis sekarang menjadi variabel, bukan konstanta
float onThreshold = 40.0;  // <-- Diperbarui
float offThreshold = 65.0; // <-- Diperbarui

// Variabel status
bool pompaStatus = false;
bool lampu1Status = false;
bool lampu2Status = false;
bool autoModeAir = true;

// Variabel lainnya
WebServer server(80);
unsigned long lastLcdSwitch = 0;
int lcdPage = 0; // Ganti dari bool ke int untuk siklus > 2

void setRelay(uint8_t pin, bool on) {
  if (RELAY_ACTIVE_LOW) {
    digitalWrite(pin, on ? LOW : HIGH);
  } else {
    digitalWrite(pin, on ? HIGH : LOW);
  }
}

void setWaterSystem(bool on) {
  pompaStatus = on;
  setRelay(relay1, on);
  setRelay(relay2, on);
}

// ====== FUNGSI KALIBRASI DIPERBARUI ======
float getMoisture(int pin) {
  int adc = analogRead(pin);
  if (adc > ADC_DISCONNECTED_THRESHOLD) return -1.0f;
  // Kalibrasi diubah sesuai permintaan
  long pct = map(adc, 3000, 1000, 0, 100); 
  if (pct < 0) pct = 0;
  if (pct > 100) pct = 100;
  return (float)pct;
}

// ====== Setup ======
void setup() {
  Serial.begin(115200);

  // --- Memuat pengaturan dari memori ---
  preferences.begin("settings", false); // Buka namespace "settings"
  // Nilai default diperbarui di sini juga
  onThreshold = preferences.getFloat("on_thresh", 40.0); 
  offThreshold = preferences.getFloat("off_thresh", 65.0);
  preferences.end();
  Serial.println("Pengaturan ambang batas dimuat.");

  pinMode(relay1, OUTPUT); pinMode(relay2, OUTPUT); pinMode(relay3, OUTPUT); pinMode(relay4, OUTPUT);
  setRelay(relay1, false); setRelay(relay2, false); setRelay(relay3, false); setRelay(relay4, false);

  lcd.begin();
  lcd.backlight();
  lcd.print("Smart Control");
  lcd.setCursor(0, 1); lcd.print("Starting AP...");
  delay(2000);
  
  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("Konfigurasi AP Gagal!");
    return;
  }
  
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: "); Serial.println(IP);

  lcd.clear(); // Cukup bersihkan layar sekali, loop akan mengambil alih

  // === Rute Web ===
  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html; charset=utf-8", PAGE_INDEX);
  });

  server.on("/status", HTTP_GET, []() {
    float m1 = getMoisture(sensor1), m2 = getMoisture(sensor2), m3 = getMoisture(sensor3), m4 = getMoisture(sensor4);
    String json = "{";
    json += "\"moist1\":" + String(m1, 1) + ",";
    json += "\"pump\":" + String(pompaStatus) + ",";
    json += "\"auto\":" + String(autoModeAir) + ",";
    json += "\"moist2\":" + String(m2, 1) + ",";
    json += "\"lamp1\":" + String(lampu1Status) + ",";
    json += "\"lamp2\":" + String(lampu2Status) + ",";
    json += "\"moist3\":" + String(m3, 1) + ",";
    json += "\"moist4\":" + String(m4, 1) + ",";
    json += "\"ip\":\"" + WiFi.softAPIP().toString() + "\",";
    json += "\"on_thresh\":" + String(onThreshold, 1) + ",";
    json += "\"off_thresh\":" + String(offThreshold, 1) + "";
    json += "}";
    server.send(200, "application/json", json);
  });

  // Rute kontrol
  server.on("/water", HTTP_POST, []() { autoModeAir = false; setWaterSystem(server.arg("state") == "on"); server.send(200); });
  server.on("/auto",  HTTP_POST, []() { autoModeAir = (server.arg("state") == "on"); server.send(200); });
  server.on("/lamp1", HTTP_POST, []() { lampu1Status = (server.arg("state") == "on"); setRelay(relay3, lampu1Status); server.send(200); });
  server.on("/lamp2", HTTP_POST, []() { lampu2Status = (server.arg("state") == "on"); setRelay(relay4, lampu2Status); server.send(200); });

  // Rute untuk menyimpan pengaturan
  server.on("/settings", HTTP_POST, []() {
    if (server.hasArg("on") && server.hasArg("off")) {
      onThreshold = server.arg("on").toFloat();
      offThreshold = server.arg("off").toFloat();

      preferences.begin("settings", false);
      preferences.putFloat("on_thresh", onThreshold);
      preferences.putFloat("off_thresh", offThreshold);
      preferences.end();
      
      Serial.println("Pengaturan baru disimpan!");
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Bad Request");
    }
  });

  server.begin();
}

// ====== Loop ======
void loop() {
  float readings[4] = { getMoisture(sensor1), getMoisture(sensor2), getMoisture(sensor3), getMoisture(sensor4) };

  bool anySensorDry = false;
  bool allSensorsWet = true;
  int connectedSensors = 0;

  for (int i = 0; i < 4; i++) {
    if (readings[i] >= 0) {
      connectedSensors++;
      if (readings[i] < onThreshold) {
        anySensorDry = true;
      }
      if (readings[i] < offThreshold) {
        allSensorsWet = false;
      }
    }
  }

  if (autoModeAir && connectedSensors > 0) {
    if (!pompaStatus && anySensorDry) {
      setWaterSystem(true);
    } 
    else if (pompaStatus && allSensorsWet) {
      setWaterSystem(false);
    }
  }

  // ====== Bagian Update LCD (Logika Baru) ======
  if (millis() - lastLcdSwitch > 2500) { // Ganti ke 2.5 detik per tampilan
    lcdPage = (lcdPage + 1) % 4; // Siklus 0, 1, 2, 3 untuk 4 tampilan berbeda
    lastLcdSwitch = millis();
  }

  char line1_buffer[17];
  char tempStr[17];

  switch (lcdPage) {
    case 0: // Tampilan Sistem Air
      if(readings[0] >= 0) sprintf(tempStr, "S1:%d%% P:%s", (int)readings[0], pompaStatus ? "ON" : "OFF");
      else sprintf(tempStr, "Air: Tdk Aktif");
      break;
    case 1: // Tampilan Sensor 2
      if(readings[1] >= 0) sprintf(tempStr, "Sensor 2: %d%%", (int)readings[1]);
      else sprintf(tempStr, "Sensor 2: --");
      break;
    case 2: // Tampilan Lampu 1
      sprintf(tempStr, "Lampu 1: %s", lampu1Status ? "ON" : "OFF");
      break;
    case 3: // Tampilan Lampu 2
      sprintf(tempStr, "Lampu 2: %s", lampu2Status ? "ON" : "OFF");
      break;
  }
  
  // Format baris pertama agar pas 16 karakter
  sprintf(line1_buffer, "%-16s", tempStr);

  // Format baris kedua (Alamat IP) agar pas 16 karakter
  char line2_buffer[17];
  String ipString = "IP: " + WiFi.softAPIP().toString();
  sprintf(line2_buffer, "%-16s", ipString.c_str());

  // Tampilkan ke LCD
  lcd.setCursor(0, 0); 
  lcd.print(line1_buffer);
  lcd.setCursor(0, 1); 
  lcd.print(line2_buffer);

  server.handleClient();
  delay(100);
}

