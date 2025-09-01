#include <Wire.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27, 16, 2);

// ====== Pin assignment ======
#define sensor1 32
#define sensor2 33
#define relay1 18
#define relay2 19

// Relay aktif-LOW? (umum pada modul relay)
const bool RELAY_ACTIVE_LOW = false;

// ====== Histeresis ======
const float ON_THRESHOLD  = 50.0;
const float OFF_THRESHOLD = 65.0;

// ====== Status ======
bool pompa1Status = false;
bool pompa2Status = false;
bool autoMode1 = true;
bool autoMode2 = true;

// ====== KONFIGURASI KONTROL SERIAL ======
const uint16_t PULSE_MS = 800;  // durasi pulse relay saat perintah "pulse"

// ---------- Helper Relay ----------
void setRelay(uint8_t pin, bool on) {
  if (RELAY_ACTIVE_LOW) digitalWrite(pin, on ? LOW : HIGH);
  else                  digitalWrite(pin, on ? HIGH : LOW);
}

// ====== Fungsi konversi ADC -> % kelembaban ======
float adcToMoistPct(int adc) {
  long pct = map(adc, 3500, 1600, 0, 100);
  if (pct < 0) pct = 0;
  if (pct > 100) pct = 100;
  return (float)pct;
}

// ===================== KONTROL SERIAL =====================
void printHelp() {
  Serial.println();
  Serial.println(F("=== MENU SERIAL ==="));
  Serial.println(F("help / ?         -> bantuan ini"));
  Serial.println(F("status           -> nilai sensor & status"));
  Serial.println(F("r1 on | r1 off   -> Pompa1 ON/OFF (auto1=OFF)"));
  Serial.println(F("r1 pulse         -> Pompa1 ON sebentar"));
  Serial.println(F("r2 on | r2 off   -> Pompa2 ON/OFF (auto2=OFF)"));
  Serial.println(F("r2 pulse         -> Pompa2 ON sebentar"));
  Serial.println(F("auto1 on|off     -> Mode AUTO ch1 ON/OFF"));
  Serial.println(F("auto2 on|off     -> Mode AUTO ch2 ON/OFF"));
  Serial.println();
}

void doStatusOnce() {
  int adc1 = analogRead(sensor1);
  int adc2 = analogRead(sensor2);
  float m1 = adcToMoistPct(adc1);
  float m2 = adcToMoistPct(adc2);
  Serial.println(F("--- STATUS ---"));
  Serial.printf("SENSOR1 PIN %d -> ADC=%d (%.1f%%)\n", sensor1, adc1, m1);
  Serial.printf("SENSOR2 PIN %d -> ADC=%d (%.1f%%)\n", sensor2, adc2, m2);
  Serial.printf("POMPA1: %s | MODE1: %s\n", pompa1Status?"ON":"OFF", autoMode1?"AUTO":"MANUAL");
  Serial.printf("POMPA2: %s | MODE2: %s\n", pompa2Status?"ON":"OFF", autoMode2?"AUTO":"MANUAL");
}

void handleSerial() {
  if (!Serial.available()) return;
  String cmd = Serial.readStringUntil('\n');
  cmd.trim();
  cmd.toLowerCase();

  if (cmd == "help" || cmd == "?") { printHelp(); return; }
  if (cmd == "status") { doStatusOnce(); return; }

  if (cmd == "r1 on")  { pompa1Status = true;  setRelay(relay1, true);  autoMode1 = false; Serial.println(F("Pompa1 ON (manual)")); return; }
  if (cmd == "r1 off") { pompa1Status = false; setRelay(relay1, false); autoMode1 = false; Serial.println(F("Pompa1 OFF (manual)")); return; }
  if (cmd == "r1 pulse") {
    autoMode1 = false; pompa1Status = true; setRelay(relay1, true);
    delay(PULSE_MS);
    pompa1Status = false; setRelay(relay1, false);
    Serial.println(F("Pompa1 PULSE selesai"));
    return;
  }

  if (cmd == "r2 on")  { pompa2Status = true;  setRelay(relay2, true);  autoMode2 = false; Serial.println(F("Pompa2 ON (manual)")); return; }
  if (cmd == "r2 off") { pompa2Status = false; setRelay(relay2, false); autoMode2 = false; Serial.println(F("Pompa2 OFF (manual)")); return; }
  if (cmd == "r2 pulse") {
    autoMode2 = false; pompa2Status = true; setRelay(relay2, true);
    delay(PULSE_MS);
    pompa2Status = false; setRelay(relay2, false);
    Serial.println(F("Pompa2 PULSE selesai"));
    return;
  }

  if (cmd == "auto1 on")  { autoMode1 = true;  Serial.println(F("AUTO1 ON")); return; }
  if (cmd == "auto1 off") { autoMode1 = false; Serial.println(F("AUTO1 OFF")); return; }
  if (cmd == "auto2 on")  { autoMode2 = true;  Serial.println(F("AUTO2 ON")); return; }
  if (cmd == "auto2 off") { autoMode2 = false; Serial.println(F("AUTO2 OFF")); return; }

  Serial.println(F("Perintah tidak dikenali. Ketik 'help' untuk bantuan."));
}

// ====== Setup ======
void setup() {
  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  setRelay(relay1, false);
  setRelay(relay2, false);

  Wire.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SoilMoisture");
  lcd.setCursor(0, 1);
  lcd.print("BPVP Surakarta");
  delay(1500);
  lcd.clear();

#if defined(ESP32)
  // Stabilkan pembacaan ADC (range 0..3.3V)
  analogSetPinAttenuation(sensor1, ADC_11db);
  analogSetPinAttenuation(sensor2, ADC_11db);
#endif

  printHelp();
}

// ====== Loop ======
void loop() {
  int adc1 = analogRead(sensor1);
  int adc2 = analogRead(sensor2);

  float kelembaban1 = adcToMoistPct(adc1);
  float kelembaban2 = adcToMoistPct(adc2);

  // Mode AUTO (histeresis)
  if (autoMode1) {
    if (!pompa1Status && kelembaban1 < ON_THRESHOLD) {
      pompa1Status = true; setRelay(relay1, true);
    } else if (pompa1Status && kelembaban1 >= OFF_THRESHOLD) {
      pompa1Status = false; setRelay(relay1, false);
    }
  }
  if (autoMode2) {
    if (!pompa2Status && kelembaban2 < ON_THRESHOLD) {
      pompa2Status = true; setRelay(relay2, true);
    } else if (pompa2Status && kelembaban2 >= OFF_THRESHOLD) {
      pompa2Status = false; setRelay(relay2, false);
    }
  }

  // LCD sederhana
  lcd.setCursor(0, 0);
  lcd.print("K1:");
  lcd.print((int)kelembaban1);
  lcd.print("% ");
  lcd.print(pompa1Status ? "ON " : "OFF");

  lcd.setCursor(0, 1);
  lcd.print("K2:");
  lcd.print((int)kelembaban2);
  lcd.print("% ");
  lcd.print(pompa2Status ? "ON " : "OFF");

  // Tangani perintah dari Serial Monitor
  handleSerial();

  delay(200);
}
