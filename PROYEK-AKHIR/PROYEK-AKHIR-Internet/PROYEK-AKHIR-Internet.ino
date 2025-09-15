#include <Wire.h>
#include <LCD_I2C.h>
#include <WiFi.h>
#include <WebServer.h>

LCD_I2C lcd(0x27, 16, 2);

// ====== Konfigurasi WiFi ======
const char* ssid = "A33";
const char* password = "12345678";

// ====== Pin assignment ======
#define sensor1 32
#define sensor2 33
#define relay1 18
#define relay2 19

// Relay aktif-LOW? (umum pada modul relay)
const bool RELAY_ACTIVE_LOW = false;

// ====== Histeresis ======
const float ON_THRESHOLD = 50.0;
const float OFF_THRESHOLD = 65.0;

// ====== Status ======
bool pompa1Status = false;
bool pompa2Status = false;
bool autoMode1 = true;
bool autoMode2 = true;

// ====== Web server ======
WebServer server(80);

void setRelay(uint8_t pin, bool on) {
  if (RELAY_ACTIVE_LOW) {
    digitalWrite(pin, on ? LOW : HIGH);
  } else {
    digitalWrite(pin, on ? HIGH : LOW);
  }
}

// ====== Fungsi konversi ADC -> % kelembaban ======
float adcToMoistPct(int adc) {
  long pct = map(adc, 3500, 1600, 0, 100);
  if (pct < 0) pct = 0;
  if (pct > 100) pct = 100;
  return (float)pct;
}

// ====== HTML halaman web (dengan CSS profesional) ======
const char PAGE_INDEX[] PROGMEM = R"HTML(
<!doctype html>
<html lang="id">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Soil Moisture Web</title>
<style>
  :root{
    --bg:#0f172a;        /* slate-900 */
    --panel:#111827;     /* gray-900 */
    --card:#1f2937;      /* gray-800 */
    --text:#e5e7eb;      /* gray-200 */
    --muted:#9ca3af;     /* gray-400 */
    --brand:#22c55e;     /* green-500 */
    --brand-weak:#86efac;/* green-300 */
    --warn:#f59e0b;      /* amber-500 */
    --danger:#ef4444;    /* red-500 */
    --border:#334155;    /* slate-700 */
  }
  *{box-sizing:border-box}
  body{
    margin:0; font-family:system-ui,-apple-system,Segoe UI,Roboto,Ubuntu,Cantarell,"Helvetica Neue",Arial;
    color:var(--text); background:radial-gradient(1200px 600px at 10% -10%, #111827 20%, transparent 60%), var(--bg);
  }
  .container{max-width:980px;margin:32px auto;padding:0 16px}
  header{
    background:linear-gradient(135deg, rgba(34,197,94,.25), rgba(15,23,42,.2));
    border:1px solid var(--border); border-radius:16px; padding:20px 18px; margin-bottom:18px;
    display:flex; gap:12px; align-items:center; justify-content:space-between;
  }
  .title{display:flex; gap:12px; align-items:center}
  .logo{
    inline-size:42px; block-size:42px; border-radius:12px;
    display:grid; place-items:center; background:rgba(34,197,94,.15); border:1px solid var(--border);
    font-weight:700; color:var(--brand);
  }
  h1{margin:0; font-size:20px}
  .subtitle{color:var(--muted); font-size:13px; margin-top:2px}
  .ip{font-size:13px; color:var(--brand-weak); padding:6px 10px; border:1px dashed var(--border); border-radius:10px}

  .grid{display:grid; gap:16px; grid-template-columns:repeat(auto-fit,minmax(260px,1fr))}
  .card{
    background:linear-gradient(180deg, rgba(255,255,255,.02), transparent), var(--card);
    border:1px solid var(--border); border-radius:16px; padding:16px;
    box-shadow:0 10px 24px rgba(0,0,0,.25);
  }
  .card h2{margin:0 0 8px; font-size:18px}
  .metric{font-size:14px; color:var(--muted); margin:2px 0}
  .metric b{color:var(--text)}
  .row{display:flex; gap:8px; flex-wrap:wrap; margin-top:8px}

  button{
    appearance:none; border:1px solid var(--border); background:#0b1220; color:var(--text);
    padding:10px 12px; border-radius:12px; cursor:pointer; font-weight:600; font-size:13px;
    transition:transform .04s ease, background .2s ease, border-color .2s ease, color .2s ease;
  }
  button:hover{transform:translateY(-1px); border-color:#4b5563}
  .primary{background:rgba(34,197,94,.12); border-color:#14532d}
  .danger{background:rgba(239,68,68,.12); border-color:#7f1d1d}
  .ghost{background:transparent}
  .badge{
    display:inline-block; font-size:12px; padding:2px 10px; border-radius:999px; border:1px solid var(--border); color:var(--muted);
  }
  .ok{color:var(--brand-weak); border-color:#166534}
  .warn{color:#fde68a; border-color:#92400e}
  .split{display:flex; gap:16px; flex-wrap:wrap}
  .split .card{flex:1 1 260px}

  footer{color:var(--muted); font-size:12px; text-align:center; margin:18px 0}
  hr{border:none; border-top:1px solid var(--border); margin:14px 0}
</style>
</head>
<body>
  <div class="container">
    <header>
      <div class="title">
        <div class="logo">SM</div>
        <div>
          <h1>Soil Moisture Monitor</h1>
          <div class="subtitle">Histeresis: &lt;50% → ON, &ge;65% → OFF (per channel)</div>
        </div>
      </div>
      <div class="ip" id="ipBox">ESP32 • IP: memuat…</div>
    </header>

    <section class="grid">
      <div class="card">
        <h2>Channel 1</h2>
        <div class="metric">Kelembaban: <b id="m1">-</b>%</div>
        <div class="metric">Pompa: <b id="p1">-</b></div>
        <div class="metric">Mode: <span class="badge ok" id="a1">AUTO</span></div>
        <div class="row">
          <button class="primary" onclick="action('/relay1','on')">Pompa1 ON</button>
          <button class="danger"  onclick="action('/relay1','off')">Pompa1 OFF</button>
        </div>
        <div class="row">
          <button class="ghost"   onclick="action('/auto1','on')">AUTO1 ON</button>
          <button class="ghost"   onclick="action('/auto1','off')">AUTO1 OFF</button>
        </div>
      </div>

      <div class="card">
        <h2>Channel 2</h2>
        <div class="metric">Kelembaban: <b id="m2">-</b>%</div>
        <div class="metric">Pompa: <b id="p2">-</b></div>
        <div class="metric">Mode: <span class="badge ok" id="a2">AUTO</span></div>
        <div class="row">
          <button class="primary" onclick="action('/relay2','on')">Pompa2 ON</button>
          <button class="danger"  onclick="action('/relay2','off')">Pompa2 OFF</button>
        </div>
        <div class="row">
          <button class="ghost"   onclick="action('/auto2','on')">AUTO2 ON</button>
          <button class="ghost"   onclick="action('/auto2','off')">AUTO2 OFF</button>
        </div>
      </div>
    </section>

    <footer>BPVP Surakarta • ESP32 Web Server</footer>
  </div>

<script>
async function refresh(){
  try{
    const r = await fetch('/status'); const j = await r.json();
    m1.textContent = j.moist1.toFixed(1);
    m2.textContent = j.moist2.toFixed(1);
    p1.textContent = j.pump1 ? 'ON' : 'OFF';
    p2.textContent = j.pump2 ? 'ON' : 'OFF';
    a1.textContent = j.auto1 ? 'AUTO' : 'MANUAL';
    a2.textContent = j.auto2 ? 'AUTO' : 'MANUAL';
    a1.className = 'badge ' + (j.auto1 ? 'ok' : 'warn');
    a2.className = 'badge ' + (j.auto2 ? 'ok' : 'warn');
    // tampilkan IP jika dikirim balik
    if (j.ip) document.getElementById('ipBox').textContent = 'ESP32 • IP: ' + j.ip;
  }catch(e){ console.log(e); }
}
async function action(path, state){
  await fetch(path + '?state=' + state, {method:'POST'});
  refresh();
}
refresh(); setInterval(refresh, 2000);
</script>
</body>
</html>
)HTML";

// ====== Setup ======
void setup() {
  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  setRelay(relay1, false);
  setRelay(relay2, false);

  // LCD sederhana
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("SoilMoisture Web");
  lcd.setCursor(0, 1);
  lcd.print(" BPVP Surakarta ");
  delay(2000);
  lcd.clear();

  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Menghubungkan WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nTerhubung!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Web routes
  server.on("/", HTTP_GET, []() {
    server.send_P(200, "text/html; charset=utf-8", PAGE_INDEX);
  });
  server.on("/status", HTTP_GET, []() {
    int adc1 = analogRead(sensor1);
    int adc2 = analogRead(sensor2);
    float m1 = adcToMoistPct(adc1);
    float m2 = adcToMoistPct(adc2);
    // kirim juga IP untuk ditampilkan di header
    String json = "{";
    json += "\"moist1\":" + String(m1, 1) + ",";
    json += "\"moist2\":" + String(m2, 1) + ",";
    json += "\"pump1\":" + String(pompa1Status ? "true" : "false") + ",";
    json += "\"pump2\":" + String(pompa2Status ? "true" : "false") + ",";
    json += "\"auto1\":" + String(autoMode1 ? "true" : "false") + ",";
    json += "\"auto2\":" + String(autoMode2 ? "true" : "false") + ",";
    json += "\"ip\":\"" + WiFi.localIP().toString() + "\"";
    json += "}";
    server.send(200, "application/json", json);
  });
  server.on("/relay1", HTTP_POST, []() {
    String st = server.arg("state");
    pompa1Status = (st == "on");
    setRelay(relay1, pompa1Status);
    autoMode1 = false;
    server.send(200);
  });
  server.on("/relay2", HTTP_POST, []() {
    String st = server.arg("state");
    pompa2Status = (st == "on");
    setRelay(relay2, pompa2Status);
    autoMode2 = false;
    server.send(200);
  });
  server.on("/auto1", HTTP_POST, []() {
    autoMode1 = (server.arg("state") == "on");
    server.send(200);
  });
  server.on("/auto2", HTTP_POST, []() {
    autoMode2 = (server.arg("state") == "on");
    server.send(200);
  });

  server.begin();
}

// ====== Loop ======
void loop() {
  int adc1 = analogRead(sensor1);
  int adc2 = analogRead(sensor2);

  float kelembaban1 = adcToMoistPct(adc1);
  float kelembaban2 = adcToMoistPct(adc2);

  // Mode AUTO
  if (autoMode1) {
    if (!pompa1Status && kelembaban1 < ON_THRESHOLD) {
      pompa1Status = true;
      setRelay(relay1, true);
    } else if (pompa1Status && kelembaban1 >= OFF_THRESHOLD) {
      pompa1Status = false;
      setRelay(relay1, false);
    }
  }
  if (autoMode2) {
    if (!pompa2Status && kelembaban2 < ON_THRESHOLD) {
      pompa2Status = true;
      setRelay(relay2, true);
    } else if (pompa2Status && kelembaban2 >= OFF_THRESHOLD) {
      pompa2Status = false;
      setRelay(relay2, false);
    }
  }

  // LCD sederhana: baris 0 kelembaban1, baris 1 kelembaban2
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

  server.handleClient();
  delay(500);

  // Tampilkan IP berkala di Serial Monitor
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}
