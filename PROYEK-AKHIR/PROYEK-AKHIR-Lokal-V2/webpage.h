// File ini berisi variabel untuk menyimpan kode HTML halaman web.

const char PAGE_INDEX[] PROGMEM = R"HTML(
<!doctype html>
<html lang="id">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>Smart Control</title>
<style>
  :root{
    --bg:#0f172a;--panel:#111827;--card:#1f2937;--text:#e5e7eb;--muted:#9ca3af;--brand:#22c55e;
    --brand-weak:#86efac;--warn:#f59e0b;--danger:#ef4444;--border:#334155;--info:#3b82f6;
    --primary-blue:#4F8FE8;--primary-teal:#26D0CE;--orange:#FF7A5A;--green:#05C168;
  }
  *{box-sizing:border-box}
  body{
    margin:0; font-family:system-ui,-apple-system,Segoe UI,Roboto,Ubuntu,Cantarell,"Helvetica Neue",Arial;
    color:var(--text); background:radial-gradient(1200px 600px at 10% -10%, #111827 20%, transparent 60%), var(--bg);
  }
  .container{max-width:980px;margin:32px auto;padding:0 16px}
  header{
    background:linear-gradient(135deg, #4F8FE8 0%, #26D0CE 100%);
    border:none; border-radius:20px; padding:32px 28px; margin-bottom:24px;
    color:white; position:relative; overflow:hidden;
  }
  header::before {
    content: '';
    position: absolute;
    top: 0; left: 0; right: 0; bottom: 0;
    background: url('data:image/svg+xml,<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 100 100"><defs><radialGradient id="g"><stop offset="20%" stop-color="white" stop-opacity="0.1"/><stop offset="80%" stop-color="white" stop-opacity="0"/></radialGradient></defs><circle cx="20" cy="20" r="30" fill="url(%23g)"/><circle cx="80" cy="60" r="25" fill="url(%23g)"/></svg>');
    pointer-events: none;
  }
  .header-content{position:relative;z-index:1;display:flex;justify-content:space-between;align-items:flex-start;flex-wrap:wrap;gap:20px;}
  .title-section h1{margin:0;font-size:32px;font-weight:700;text-shadow:0 2px 4px rgba(0,0,0,0.1);}
  .title-section .subtitle{font-size:16px;margin-top:8px;opacity:0.9;font-weight:400;}
  .title-section .features{display:flex;gap:24px;margin-top:16px;font-size:14px;opacity:0.8;}
  .feature-item{display:flex;align-items:center;gap:6px;}
  .status-section{text-align:right;}
  .esp-status{background:rgba(255,255,255,0.15);padding:8px 16px;border-radius:20px;font-size:14px;font-weight:600;margin-bottom:8px;}
  .esp-status.offline{background:rgba(255,122,90,0.8);}
  .esp-status.online{background:rgba(5,193,104,0.8);}
  .last-update{font-size:12px;opacity:0.8;}
  .grid{display:grid; gap:20px; grid-template-columns:repeat(auto-fit,minmax(320px,1fr))}
  @media(min-width:768px){
    .grid{grid-template-columns:2fr 1fr;}
    .sensor-grid{grid-template-columns:1fr 1fr;}
  }
  @media(max-width:767px){
    .sensor-grid{grid-template-columns:1fr;}
    .header-content{text-align:center;}
    .status-section{text-align:center;margin-top:16px;}
    .title-section .features{justify-content:center;}
  }
  .card{
    background:linear-gradient(180deg, rgba(255,255,255,.02), transparent), var(--card);
    border:1px solid var(--border); border-radius:16px; padding:16px;
    box-shadow:0 10px 24px rgba(0,0,0,.25); transition: opacity .3s ease;
  }
  .card h2{margin:0 0 8px; font-size:18px}
  .metric,.setting-row{font-size:14px; color:var(--muted); margin:8px 0} /* Penambahan margin */
  .metric b{color:var(--text); font-size: 1.1em;} /* Sedikit diperbesar */
  .row{display:flex; gap:8px; flex-wrap:wrap; margin-top:16px}
  button{
    appearance:none; border:1px solid var(--border); background:#0b1220; color:var(--text);
    padding:10px 12px; border-radius:12px; cursor:pointer; font-weight:600; font-size:13px;
    transition:transform .04s ease, background .2s ease, border-color .2s ease, color .2s ease;
  }
  button:hover{transform:translateY(-1px); border-color:#4b5563}
  .primary{background:rgba(34,197,94,.12); border-color:#14532d}
  .danger{background:rgba(239,68,68,.12); border-color:#7f1d1d}
  .info{background:rgba(59,130,246,.12); border-color:#1e40af;}
  .ghost{background:transparent}
  .badge{display:inline-block; font-size:12px; padding:2px 10px; border-radius:999px; border:1px solid var(--border); color:var(--muted)}
  .ok{color:var(--brand-weak); border-color:#166534}
  .warn{color:#fde68a; border-color:#92400e}
  footer{color:var(--muted); font-size:12px; text-align:center; margin:18px 0}
  button:disabled{cursor:not-allowed;transform:none;}
  .card.disabled{opacity:0.4;}
  /* Gaya untuk slider */
  .setting-row{display:flex;align-items:center;gap:10px;margin:12px 0;}
  .setting-row label{flex-shrink:0}
  .setting-row input[type=range]{width:100%;}
  .setting-row span{font-weight:bold;color:var(--text);width:45px}

  /* Progress bars untuk sensor */
  .sensor-grid{display:grid;grid-template-columns:1fr 1fr;gap:16px;margin-bottom:24px;}
  .sensor-card{
    background:rgba(255,255,255,0.05);
    border:1px solid rgba(255,255,255,0.1);
    border-radius:16px;
    padding:20px;
    text-align:center;
  }
  .sensor-card.channel1{border-left:4px solid var(--primary-blue);}
  .sensor-card.channel2{border-left:4px solid var(--primary-teal);}
  .sensor-title{display:flex;align-items:center;justify-content:center;gap:8px;margin-bottom:12px;}
  .sensor-title h3{margin:0;font-size:16px;font-weight:600;}
  .sensor-status{
    display:inline-block;
    padding:4px 12px;
    border-radius:12px;
    font-size:11px;
    font-weight:600;
    text-transform:uppercase;
    background:rgba(255,122,90,0.2);
    color:#FF7A5A;
    border:1px solid rgba(255,122,90,0.3);
  }
  .sensor-value{
    font-size:48px;
    font-weight:700;
    margin:16px 0 8px;
    background:linear-gradient(135deg, var(--primary-blue), var(--primary-teal));
    -webkit-background-clip:text;
    -webkit-text-fill-color:transparent;
    background-clip:text;
  }
  .sensor-label{
    color:var(--muted);
    font-size:14px;
    margin-bottom:16px;
  }
  .progress-container{
    background:rgba(255,255,255,0.1);
    border-radius:10px;
    height:8px;
    overflow:hidden;
    position:relative;
  }
  .progress-bar{
    height:100%;
    border-radius:10px;
    transition:width 0.5s ease;
  }
  .progress-bar.channel1{background:linear-gradient(90deg, #4F8FE8, #7BA7F7);}
  .progress-bar.channel2{background:linear-gradient(90deg, #26D0CE, #4DDADB);}

  /* Weather panel */
  .weather-panel{
    background:linear-gradient(135deg, #1F2937 0%, #111827 100%);
    border:1px solid var(--border);
    border-radius:20px;
    padding:24px;
    text-align:center;
    position:relative;
  }
  .weather-location{
    display:flex;
    align-items:center;
    justify-content:center;
    gap:8px;
    margin-bottom:16px;
    color:var(--text);
    font-weight:600;
  }
  .weather-temp{
    font-size:64px;
    font-weight:300;
    color:#F59E0B;
    margin:12px 0;
  }
  .weather-desc{
    color:var(--muted);
    font-size:14px;
    margin-bottom:20px;
  }
  .weather-stats{
    display:grid;
    grid-template-columns:repeat(3,1fr);
    gap:16px;
    margin-top:20px;
  }
  .weather-stat{
    text-align:center;
  }
  .weather-stat-icon{
    font-size:20px;
    margin-bottom:4px;
  }
  .weather-stat-label{
    font-size:10px;
    color:var(--muted);
    text-transform:uppercase;
    margin-bottom:4px;
  }
  .weather-stat-value{
    font-weight:600;
    color:var(--text);
  }
</style>
</head>
<body>
  <div class="container">
    <header>
      <div class="header-content">
        <div class="title-section">
          <h1>🌱 Smart Irrigation<br>Control System</h1>
          <div class="subtitle">Sistem monitoring dan kontrol kelembaban tanah berbasis IoT dengan analisis cuaca real-time untuk optimasi irigasi pertanian</div>
          <div class="features">
            <div class="feature-item">📡 Sensor ESP32</div>
            <div class="feature-item">📊 Data Cuaca Real-time</div>
            <div class="feature-item">⚙️ Kontrol Otomatis</div>
          </div>
        </div>
        <div class="status-section">
          <div class="esp-status offline" id="espStatus">● ESP32 Offline</div>
          <div class="last-update" id="lastUpdate">Last: 12.12</div>
        </div>
      </div>
    </header>

    <!-- Pembacaan Sensor Terkini -->
    <section style="margin-bottom:24px;">
      <h2 style="margin:0 0 16px;color:var(--text);font-size:20px;display:flex;align-items:center;gap:8px;">
        📊 Pembacaan Sensor Terkini
      </h2>
      <div class="sensor-grid">
        <div class="sensor-card channel1">
          <div class="sensor-title">
            <h3>Channel 1</h3>
            <div class="sensor-status" id="status1">Tidak Aktif</div>
          </div>
          <div class="sensor-value" id="s_m1">65.0</div>
          <div class="sensor-label">Kelembaban Tanah</div>
          <div class="progress-container">
            <div class="progress-bar channel1" id="progress1" style="width:65%"></div>
          </div>
        </div>
        <div class="sensor-card channel2">
          <div class="sensor-title">
            <h3>Channel 2</h3>
            <div class="sensor-status" id="status2">Tidak Aktif</div>
          </div>
          <div class="sensor-value" id="s_m2">80.1</div>
          <div class="sensor-label">Kelembaban Tanah</div>
          <div class="progress-container">
            <div class="progress-bar channel2" id="progress2" style="width:80%"></div>
          </div>
        </div>
      </div>
    </section>

    <section class="grid">
      <!-- Panel Cuaca -->
      <div class="weather-panel">
        <div class="weather-location">
          📍 Colomadu
        </div>
        <div class="weather-temp">30°C</div>
        <div class="weather-desc">Awan Tersebar</div>
        <div class="weather-stats">
          <div class="weather-stat">
            <div class="weather-stat-icon">🌡️</div>
            <div class="weather-stat-label">Min/Max</div>
            <div class="weather-stat-value">30°/30°</div>
          </div>
          <div class="weather-stat">
            <div class="weather-stat-icon">💧</div>
            <div class="weather-stat-label">Kelembaban</div>
            <div class="weather-stat-value">65%</div>
          </div>
          <div class="weather-stat">
            <div class="weather-stat-icon">💨</div>
            <div class="weather-stat-label">Angin</div>
            <div class="weather-stat-value">4 m/s</div>
          </div>
        </div>
      </div>
    </section>

    <!-- Pengaturan Sistem -->
    <section style="margin-top:24px;">
      <div class="card">
        <h2 style="display:flex;align-items:center;gap:8px;">⚙️ Pengaturan Histeresis</h2>
        <div class="setting-row">
          <label for="onSlider">Batas ON:</label>
          <input type="range" min="0" max="100" value="40" id="onSlider" oninput="this.nextElementSibling.textContent=this.value+'%'">
          <span id="onValue">40%</span>
        </div>
        <div class="setting-row">
          <label for="offSlider">Batas OFF:</label>
          <input type="range" min="0" max="100" value="65" id="offSlider" oninput="this.nextElementSibling.textContent=this.value+'%'">
          <span id="offValue">65%</span>
        </div>
        <div class="row">
          <button class="primary" style="width:100%" onclick="saveSettings(this)">Simpan Pengaturan</button>
        </div>
      </div>
      
      <div class="card" id="card1">
        <h2 style="display:flex;align-items:center;gap:8px;color:#4F8FE8;">💧 Kontrol Sistem Irigasi Otomatis</h2>
        <div style="background:rgba(79,143,232,0.05);padding:16px;border-radius:12px;margin:12px 0;">
          <div style="display:flex;align-items:center;gap:8px;margin-bottom:12px;">
            <span style="font-size:20px;">💧</span>
            <div>
              <div style="font-weight:600;font-size:16px;">Sistem Irigasi Utama</div>
              <div style="font-size:13px;color:var(--muted);">Relay 1 (Pompa) + Relay 2 (Valve) bekerja bersamaan</div>
            </div>
          </div>
          
          <div style="display:flex;align-items:center;gap:12px;margin:12px 0;">
            <span style="font-size:16px;">⚡</span>
            <span style="font-size:14px;color:var(--muted);">Status Sistem Irigasi</span>
            <span style="flex:1;text-align:right;font-weight:600;color:#ef4444;" id="p1">MATI</span>
          </div>

          <div style="background:rgba(255,255,255,0.05);padding:12px;border-radius:10px;margin:12px 0;">
            <div style="display:flex;align-items:center;gap:12px;">
              <span style="font-size:16px;">⚙️</span>
              <span style="font-size:14px;color:var(--muted);">Mode Kontrol</span>
              <span style="flex:1;text-align:right;">
                <span class="badge ok" id="a1" style="background:#05C168;color:white;border:none;">OTOMATIS</span>
              </span>
            </div>
            <div style="font-size:12px;color:var(--muted);margin-top:4px;text-align:center;" id="thresholdInfo">
              Nyalakan <40% | Matikan >65%
            </div>
          </div>

          <div style="display:grid;grid-template-columns:1fr 1fr;gap:8px;margin-top:16px;">
            <button class="primary" style="background:#05C168;border-color:#059669;" onclick="manualWaterControl('on')">🟢 Manual ON</button>
            <button class="danger" style="background:#EF4444;border-color:#DC2626;" onclick="manualWaterControl('off')">🔴 Manual OFF</button>
          </div>
          <div style="display:grid;grid-template-columns:1fr;gap:8px;margin-top:8px;">
            <button class="info" style="background:#3B82F6;border-color:#1D4ED8;" onclick="toggleAutoMode()">🔄 Aktifkan Mode Otomatis</button>
          </div>
        </div>

        <div style="font-size:12px;color:var(--info);background:rgba(59,130,246,0.1);padding:8px;border-radius:8px;margin-top:8px;">
          ℹ️ <strong>Kontrol:</strong> Sistem terpadu Pompa (R1-NC) + Valve (R2-NO)<br>
          • <strong>Manual ON/OFF:</strong> Kontrol langsung sistem irigasi<br>
          • <strong>Mode Otomatis:</strong> Berdasarkan sensor kelembaban tanah
        </div>
      </div>
      
      <div class="card">
        <h2 style="display:flex;align-items:center;gap:8px;color:#26D0CE;">🔧 Kontrol Relay Individual</h2>
        
        <div style="display:grid;gap:12px;">
          <div style="background:rgba(255,122,90,0.05);padding:16px;border-radius:12px;border-left:4px solid #FF7A5A;">
            <div style="display:flex;justify-content:space-between;align-items:center;margin-bottom:8px;">
              <span style="font-weight:600;"><span style="background:#FF7A5A;color:white;padding:2px 6px;border-radius:4px;font-size:12px;">R3</span> Relay 3 (Lampu 1)</span>
              <span style="background:rgba(239,68,68,0.2);color:#EF4444;padding:4px 8px;border-radius:8px;font-size:12px;font-weight:600;" id="l1">MATI</span>
            </div>
            <div style="display:grid;grid-template-columns:1fr 1fr;gap:8px;">
              <button class="primary" style="background:#05C168;border-color:#059669;" onclick="action('/lamp1','on')">🟢 Hidupkan</button>
              <button class="danger" style="background:#EF4444;border-color:#DC2626;" onclick="action('/lamp1','off')">🔴 Matikan</button>
            </div>
          </div>

          <div style="background:rgba(38,208,206,0.05);padding:16px;border-radius:12px;border-left:4px solid #26D0CE;">
            <div style="display:flex;justify-content:space-between;align-items:center;margin-bottom:8px;">
              <span style="font-weight:600;"><span style="background:#26D0CE;color:white;padding:2px 6px;border-radius:4px;font-size:12px;">R4</span> Relay 4 (Lampu 2)</span>
              <span style="background:rgba(239,68,68,0.2);color:#EF4444;padding:4px 8px;border-radius:8px;font-size:12px;font-weight:600;" id="l2">MATI</span>
            </div>
            <div style="display:grid;grid-template-columns:1fr 1fr;gap:8px;">
              <button class="primary" style="background:#05C168;border-color:#059669;" onclick="action('/lamp2','on')">🟢 Hidupkan</button>
              <button class="danger" style="background:#EF4444;border-color:#DC2626;" onclick="action('/lamp2','off')">🔴 Matikan</button>
            </div>
          </div>
        </div>

        <div style="font-size:12px;color:var(--info);background:rgba(139,92,246,0.1);padding:8px;border-radius:8px;margin-top:12px;">
          ℹ️ <strong>Info:</strong> Relay 3 & 4 dikontrol secara independen, tidak terkait dengan sistem irigasi
        </div>
      </div>
    </section>
  </div>

  <footer style="color:var(--muted);font-size:12px;text-align:center;margin:24px 0;padding:16px;">
    <div style="margin-bottom:8px;">Smart Irrigation Control System</div>
    <div>🌱 Optimizing agriculture through IoT technology</div>
  </footer>

<script>
async function refresh(){
  try{
    const r = await fetch('/status');
    const j = await r.json();
    
    // Update sensor values dan progress bars
    const m1 = (j.moist1 < 0) ? 0 : j.moist1;
    const m2 = (j.moist2 < 0) ? 0 : j.moist2;
    
    document.getElementById('s_m1').textContent = (j.moist1 < 0) ? '--' : j.moist1.toFixed(1);
    document.getElementById('s_m2').textContent = (j.moist2 < 0) ? '--' : j.moist2.toFixed(1);
    
    // Update progress bars
    document.getElementById('progress1').style.width = (j.moist1 < 0) ? '0%' : j.moist1.toFixed(1) + '%';
    document.getElementById('progress2').style.width = (j.moist2 < 0) ? '0%' : j.moist2.toFixed(1) + '%';
    
    // Update status sensor based on connection and moisture level
    const status1 = document.getElementById('status1');
    const status2 = document.getElementById('status2');
    
    if (j.moist1 < 0) {
      status1.textContent = 'Terputus';
      status1.style.background = 'rgba(239,68,68,0.2)';
      status1.style.color = '#EF4444';
    } else {
      if (j.moist1 < 40) {
        status1.textContent = 'Kering';
        status1.style.background = 'rgba(255,122,90,0.2)';
        status1.style.color = '#FF7A5A';
      } else if (j.moist1 >= 65) {
        status1.textContent = 'Basah';
        status1.style.background = 'rgba(5,193,104,0.2)';
        status1.style.color = '#05C168';
      } else {
        status1.textContent = 'Sedang';
        status1.style.background = 'rgba(245,158,11,0.2)';
        status1.style.color = '#F59E0B';
      }
    }
    
    if (j.moist2 < 0) {
      status2.textContent = 'Terputus';
      status2.style.background = 'rgba(239,68,68,0.2)';
      status2.style.color = '#EF4444';
    } else {
      if (j.moist2 < 40) {
        status2.textContent = 'Kering';
        status2.style.background = 'rgba(255,122,90,0.2)';
        status2.style.color = '#FF7A5A';
      } else if (j.moist2 >= 65) {
        status2.textContent = 'Basah';
        status2.style.background = 'rgba(5,193,104,0.2)';
        status2.style.color = '#05C168';
      } else {
        status2.textContent = 'Sedang';
        status2.style.background = 'rgba(245,158,11,0.2)';
        status2.style.color = '#F59E0B';
      }
    }

    // Update Card 1: Sistem Air
    const card1 = document.getElementById('card1');
    const p1 = document.getElementById('p1');
    const a1 = document.getElementById('a1');
    
    const noSensors = j.moist1 < 0 && j.moist2 < 0;

    if (noSensors) {
      p1.textContent = 'DISABLE';
      a1.textContent = 'DISABLE';
      card1.classList.add('disabled');
      card1.querySelectorAll('button').forEach(b => b.disabled = true);
    } else {
      p1.textContent = j.pump ? 'HIDUP' : 'MATI';
      p1.style.color = j.pump ? '#05C168' : '#ef4444';
      a1.textContent = j.auto ? 'OTOMATIS' : 'MANUAL';
      a1.className = 'badge ' + (j.auto ? 'ok' : 'warn');
      a1.style.background = j.auto ? '#05C168' : '#F59E0B';
      a1.style.color = 'white';
      a1.style.border = 'none';
      card1.classList.remove('disabled');
      card1.querySelectorAll('button').forEach(b => b.disabled = false);
      
      // Update tombol mode otomatis berdasarkan status current
      const autoButton = card1.querySelector('button[onclick*="toggleAutoMode"]');
      if (autoButton) {
        if (j.auto) {
          autoButton.textContent = '⏸️ Mode Manual';
          autoButton.style.background = '#F59E0B';
          autoButton.style.borderColor = '#D97706';
        } else {
          autoButton.textContent = '🔄 Mode Otomatis';
          autoButton.style.background = '#3B82F6';
          autoButton.style.borderColor = '#1D4ED8';
        }
      }
    }

    // Update Relay individual
    const l1Status = document.getElementById('l1');
    const l2Status = document.getElementById('l2');
    l1Status.textContent = j.lamp1 ? 'HIDUP' : 'MATI';
    l1Status.style.background = j.lamp1 ? 'rgba(5,193,104,0.2)' : 'rgba(239,68,68,0.2)';
    l1Status.style.color = j.lamp1 ? '#05C168' : '#EF4444';
    
    l2Status.textContent = j.lamp2 ? 'HIDUP' : 'MATI';
    l2Status.style.background = j.lamp2 ? 'rgba(5,193,104,0.2)' : 'rgba(239,68,68,0.2)';
    l2Status.style.color = j.lamp2 ? '#05C168' : '#EF4444';

    // Update ESP32 status
    const espStatus = document.getElementById('espStatus');
    const lastUpdate = document.getElementById('lastUpdate');
    espStatus.textContent = '● ESP32 Online';
    espStatus.className = 'esp-status online';
    lastUpdate.textContent = 'Last: ' + new Date().toLocaleTimeString('id-ID', {hour: '2-digit', minute: '2-digit'});

    // ==========================================================
    // BAGIAN PENTING: SINKRONISASI TAMPILAN SLIDER & INFO THRESHOLD
    // ==========================================================
    // Perbarui nilai slider agar sesuai dengan data dari ESP32
    document.getElementById('onSlider').value = j.on_thresh;
    // Perbarui teks persentase agar sesuai juga
    document.getElementById('onValue').textContent = j.on_thresh.toFixed(0) + '%';
    
    document.getElementById('offSlider').value = j.off_thresh;
    document.getElementById('offValue').textContent = j.off_thresh.toFixed(0) + '%';
    
    // Update info threshold pada sistem irigasi
    const thresholdInfo = document.getElementById('thresholdInfo');
    if (thresholdInfo) {
      thresholdInfo.textContent = `Nyalakan <${j.on_thresh.toFixed(0)}% | Matikan >${j.off_thresh.toFixed(0)}%`;
    }
    // ==========================================================

  }catch(e){ 
    console.log(e);
    // Update ESP32 status sebagai offline jika gagal fetch
    const espStatus = document.getElementById('espStatus');
    if (espStatus) {
      espStatus.textContent = '● ESP32 Offline';
      espStatus.className = 'esp-status offline';
    }
  }
}

async function action(path, state){
  await fetch(path + '?state=' + state, {method:'POST'});
  setTimeout(refresh, 250);
}

async function manualWaterControl(state){
  // Kontrol manual sistem irigasi - ON atau OFF
  await fetch('/water-manual?state=' + state, {method:'POST'});
  setTimeout(refresh, 250);
}

async function toggleWaterSystem(forceOn = false){
  if (forceOn) {
    // Aktifkan manual mode dan hidupkan sistem
    await fetch('/auto?state=off', {method:'POST'});
    await fetch('/water?state=on', {method:'POST'});
  } else {
    // Toggle sistem air
    const currentStatus = document.getElementById('p1').textContent === 'HIDUP';
    await fetch('/water?state=' + (currentStatus ? 'off' : 'on'), {method:'POST'});
  }
  setTimeout(refresh, 250);
}

async function toggleAutoMode(){
  const currentAuto = document.getElementById('a1').textContent === 'OTOMATIS';
  await fetch('/auto?state=' + (currentAuto ? 'off' : 'on'), {method:'POST'});
  setTimeout(refresh, 250);
}

async function saveSettings(btn){
  const onVal = document.getElementById('onSlider').value;
  const offVal = document.getElementById('offSlider').value;
  btn.textContent = 'Menyimpan...';
  await fetch(`/settings?on=${onVal}&off=${offVal}`, {method:'POST'});
  btn.textContent = 'Tersimpan!';
  setTimeout(() => { btn.textContent = 'Simpan Pengaturan'; }, 2000);
}

refresh(); setInterval(refresh, 2000);
</script>
</body>
</html>
)HTML";