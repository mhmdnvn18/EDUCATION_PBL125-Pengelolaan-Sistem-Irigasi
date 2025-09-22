#include <Wire.h>
#include <LCD_I2C.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include "webpage.h"

LCD_I2C lcd(0x27, 16, 2);
Preferences preferences;

// ====== Konfigurasi Jaringan & IP Statis ======
const char* ssid = "ESP32";
const char* password = "12345678";
IPAddress local_IP(192, 168, 5, 1);
IPAddress gateway(192, 168, 5, 1);
IPAddress subnet(255, 255, 255, 0);

// ====== Pin assignment ======
#define sensor1 34
#define sensor2 35
#define relay1 4
#define relay2 5
#define relay3 18
#define relay4 19

// ====== Konstanta & Variabel ======
const int ADC_DISCONNECTED_THRESHOLD = 4000;
// --- PERUBAHAN 1: Mengubah konstanta menjadi true untuk logika active low ---
const bool RELAY_ACTIVE_LOW = true;
const int NUM_SENSORS = 2; // Menentukan jumlah sensor yang digunakan

float onThreshold = 40.0;
float offThreshold = 65.0;

bool pompaStatus = false;
bool lampu1Status = false;
bool lampu2Status = false;
bool autoModeAir = true;

WebServer server(80);
unsigned long lastLcdSwitch = 0;
int lcdPage = 0;

void setRelay(uint8_t pin, bool on) {
  // Fungsi ini sudah benar dan akan bekerja sesuai dengan flag RELAY_ACTIVE_LOW
  if (RELAY_ACTIVE_LOW) {
    digitalWrite(pin, on ? LOW : HIGH);
  } else {
    digitalWrite(pin, on ? HIGH : LOW);
  }
}

void setWaterSystem(bool on) {
  pompaStatus = on;
  // --- PERUBAHAN 2: Menyesuaikan logika Pompa (relay1) yang terhubung ke NC ---
  // Untuk relay ACTIVE LOW yang terpasang di NC:
  // - Untuk menyalakan pompa (memutus sirkuit relay), kirim HIGH.
  // - Untuk mematikan pompa (menyambungkan sirkuit relay), kirim LOW.
  digitalWrite(relay1, on ? HIGH : LOW);
  
  // Relay 2 (Valve) terhubung ke NO, jadi bisa pakai fungsi setRelay biasa
  setRelay(relay2, on);
}

float getMoisture(int pin) {
  int adc = analogRead(pin);
  if (adc > ADC_DISCONNECTED_THRESHOLD) return -1.0f;
  long pct = map(adc, 3000, 1000, 0, 100);
  if (pct < 0) pct = 0;
  if (pct > 100) pct = 100;
  return (float)pct;
}

// ====== Setup ======
void setup() {
  Serial.begin(115200);

  preferences.begin("settings", false);
  onThreshold = preferences.getFloat("on_thresh", 40.0);
  offThreshold = preferences.getFloat("off_thresh", 65.0);
  preferences.end();
  Serial.println("Pengaturan ambang batas dimuat.");

  pinMode(relay1, OUTPUT); pinMode(relay2, OUTPUT); pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  // Atur kondisi awal relay, pastikan semua mati
  // --- PERUBAHAN 3: Menyesuaikan kondisi awal Pompa (relay1) ---
  // Untuk mematikan pompa (NC), relay harus aktif. Sinyal LOW untuk active low.
  digitalWrite(relay1, LOW); 
  
  // Untuk mematikan perangkat lain (NO), relay harus non-aktif. Sinyal HIGH untuk active low.
  setRelay(relay2, false);  
  setRelay(relay3, false);
  setRelay(relay4, false);

  lcd.begin();
  lcd.backlight();
  lcd.print("Smart Control");
  lcd.setCursor(0, 1);
  lcd.print("Starting AP...");
  delay(2000);

  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("Konfigurasi AP Gagal!");
    return;
  }
  
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: "); Serial.println(IP);

  lcd.clear();
  // === Rute Web ===
  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html; charset=utf-8", PAGE_INDEX);
  });
  server.on("/status", HTTP_GET, []() {
    float m1 = getMoisture(sensor1), m2 = getMoisture(sensor2);
    String json = "{";
    json += "\"moist1\":" + String(m1, 1) + ",";
    json += "\"moist2\":" + String(m2, 1) + ",";
    json += "\"pump\":" + String(pompaStatus) + ",";
    json += "\"auto\":" + String(autoModeAir) + ",";
    json += "\"lamp1\":" + String(lampu1Status) + ",";
    json += "\"lamp2\":" + String(lampu2Status) + ",";
    json += "\"ip\":\"" + WiFi.softAPIP().toString() + "\",";
    json += "\"on_thresh\":" + String(onThreshold, 1) + ",";
    json += "\"off_thresh\":" + String(offThreshold, 1) + "";
    json += "}";
    server.send(200, "application/json", json);
  });
  server.on("/water", HTTP_POST, []() { autoModeAir = false; setWaterSystem(server.arg("state") == "on"); server.send(200); });
  server.on("/water-manual", HTTP_POST, []() { 
    autoModeAir = false; 
    setWaterSystem(server.arg("state") == "on"); 
    server.send(200); 
  });
  server.on("/auto",  HTTP_POST, []() { autoModeAir = (server.arg("state") == "on"); server.send(200); });
  server.on("/lamp1", HTTP_POST, []() { lampu1Status = (server.arg("state") == "on"); setRelay(relay3, lampu1Status); server.send(200); });
  server.on("/lamp2", HTTP_POST, []() { lampu2Status = (server.arg("state") == "on"); setRelay(relay4, lampu2Status); server.send(200); });
  server.on("/settings", HTTP_POST, []() {
    if (server.hasArg("on") && server.hasArg("off")) {
      onThreshold = server.arg("on").toFloat();
      offThreshold = server.arg("off").toFloat();
      preferences.begin("settings", false);
      preferences.putFloat("on_thresh", onThreshold);
      preferences.putFloat("off_thresh", offThreshold);
      preferences.end();
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Bad Request");
    }
  });

  server.begin();
}

// ====== Loop ======
void loop() {
  float readings[NUM_SENSORS];
  readings[0] = getMoisture(sensor1); delay(10);
  readings[1] = getMoisture(sensor2); delay(10);

  bool anySensorDry = false;
  bool allSensorsWet = true;
  int connectedSensors = 0;
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (readings[i] >= 0) {
      connectedSensors++;
      if (readings[i] < onThreshold) anySensorDry = true;
      if (readings[i] < offThreshold) allSensorsWet = false;
    }
  }

  if (autoModeAir && connectedSensors > 0) {
    if (!pompaStatus && anySensorDry) setWaterSystem(true);
    else if (pompaStatus && allSensorsWet) setWaterSystem(false);
  }

  // ====== BAGIAN UPDATE LCD BARU ======
  if (millis() - lastLcdSwitch > 3000) {
    lcdPage = (lcdPage + 1) % 3;
    lastLcdSwitch = millis();
  }

  char line1_buffer[17];
  char tempStr[17];

  switch (lcdPage) {
    case 0: // Tampilan Sistem Air
      if (connectedSensors > 0) {
        sprintf(tempStr, "Air:%s | %s", pompaStatus ? "ON " : "OFF", autoModeAir ? "Auto" : "Manu");
      } else {
        sprintf(tempStr, "Air: Tdk Aktif");
      }
      break;
    case 1: // Tampilan Lampu
      sprintf(tempStr, "L1:%s   L2:%s",
              lampu1Status ? "ON " : "OFF",
              lampu2Status ? "ON " : "OFF");
      break;
    case 2: // Tampilan Sensor 1 & 2
      char s1_val[4], s2_val[4];
      (readings[0] >= 0) ? sprintf(s1_val, "%3d", (int)readings[0]) : sprintf(s1_val, " --");
      (readings[1] >= 0) ?
      sprintf(s2_val, "%3d", (int)readings[1]) : sprintf(s2_val, " --");
      sprintf(tempStr, "S1:%s%% S2:%s%%", s1_val, s2_val);
      break;
  }

  sprintf(line1_buffer, "%-16s", tempStr);

  char line2_buffer[17];
  // Menampilkan info jaringan secara bergantian di baris kedua
  switch (lcdPage) {
    case 1: { // Tampilkan SSID
      String ssidString = "SSID:" + String(ssid);
      sprintf(line2_buffer, "%-16s", ssidString.c_str());
      break;
    }
    case 2: { // Tampilkan Password
      String passString = "Pass:" + String(password);
      sprintf(line2_buffer, "%-16s", passString.c_str());
      break;
    }
    case 0: // Tampilkan IP
    default: {
      String ipString = "IP:" + WiFi.softAPIP().toString();
      sprintf(line2_buffer, "%-16s", ipString.c_str());
      break;
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(line1_buffer);
  lcd.setCursor(0, 1);
  lcd.print(line2_buffer);

  server.handleClient();
  delay(100);
}