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
    
    /* Consistent spacing system */
    --section-spacing: 24px;
    --card-padding: 20px;
    --grid-gap: 20px;
    --border-radius: 16px;
    --inner-spacing: 16px;
    --small-spacing: 12px;
  }
  
  /* Mobile spacing overrides */
  @media(max-width:480px){
    :root{
      --section-spacing: 20px;
      --card-padding: 16px;
      --grid-gap: 16px;
      --border-radius: 12px;
      --inner-spacing: 12px;
      --small-spacing: 8px;
    }
  }
  *{box-sizing:border-box}
  body{
    margin:0; font-family:system-ui,-apple-system,Segoe UI,Roboto,Ubuntu,Cantarell,"Helvetica Neue",Arial;
    color:var(--text); background:radial-gradient(1200px 600px at 10% -10%, #111827 20%, transparent 60%), var(--bg);
  }
  .container{max-width:980px;margin:32px auto;padding:0 16px}
  @media(max-width:480px){
    .container{margin:16px auto;padding:0 12px}
  }
  header{
    background:linear-gradient(135deg, #4F8FE8 0%, #26D0CE 100%);
    border:none; border-radius:var(--border-radius); padding:var(--card-padding); margin-bottom:var(--section-spacing);
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
  @media(max-width:480px){
    .title-section h1{font-size:24px;line-height:1.2;}
  }
  .title-section .subtitle{font-size:16px;margin-top:8px;opacity:0.9;font-weight:400;}
  @media(max-width:480px){
    .title-section .subtitle{font-size:14px;line-height:1.4;}
  }
  .title-section .features{display:flex;gap:24px;margin-top:16px;font-size:14px;opacity:0.8;}
  @media(max-width:480px){
    .title-section .features{gap:16px;font-size:12px;flex-wrap:wrap;}
  }
  .feature-item{display:flex;align-items:center;gap:6px;}
  @media(max-width:480px){
    .feature-item{gap:4px;}
  }
  .status-section{text-align:right;}
  .esp-status{background:rgba(255,255,255,0.15);padding:8px 16px;border-radius:20px;font-size:14px;font-weight:600;margin-bottom:8px;}
  .esp-status.offline{background:rgba(255,122,90,0.8);}
  .esp-status.online{background:rgba(5,193,104,0.8);}
  .last-update{font-size:12px;opacity:0.8;}
  .grid{display:grid; gap:var(--grid-gap); grid-template-columns:repeat(auto-fit,minmax(320px,1fr))}
  @media(min-width:768px){
    .grid{grid-template-columns:2fr 1fr;}
    .sensor-grid{grid-template-columns:1fr 1fr;}
  }
  @media(max-width:767px){
    .sensor-grid{grid-template-columns:1fr;}
    .header-content{text-align:center;}
    .status-section{text-align:center;margin-top:var(--inner-spacing);}
    .title-section .features{justify-content:center;}
  }
  @media(max-width:480px){
    .grid{grid-template-columns:1fr;}
  }
  .card{
    background:linear-gradient(180deg, rgba(255,255,255,.02), transparent), var(--card);
    border:1px solid var(--border); border-radius:var(--border-radius); padding:var(--card-padding);
    box-shadow:0 10px 24px rgba(0,0,0,.25); transition: opacity .3s ease;
  }
  .card h2{margin:0 0 var(--small-spacing); font-size:18px}
  @media(max-width:480px){
    .card h2{font-size:16px;}
  }
  .metric,.setting-row{font-size:14px; color:var(--muted); margin:8px 0} /* Penambahan margin */
  @media(max-width:480px){
    .metric,.setting-row{font-size:13px;margin:6px 0;}
  }
  .metric b{color:var(--text); font-size: 1.1em;} /* Sedikit diperbesar */
  .row{display:flex; gap:8px; flex-wrap:wrap; margin-top:16px}
  @media(max-width:480px){
    .row{gap:12px; margin-top:12px;}
  }
  button{
    appearance:none; border:1px solid var(--border); background:#0b1220; color:var(--text);
    padding:var(--small-spacing) var(--inner-spacing); border-radius:var(--border-radius); cursor:pointer; font-weight:600; font-size:13px;
    transition:transform .04s ease, background .2s ease, border-color .2s ease, color .2s ease;
    min-height:44px; /* Minimum touch target size */
    display:flex; align-items:center; justify-content:center;
  }
  @media(max-width:480px){
    button{
      min-height:48px; /* Larger touch targets on mobile */
      padding:var(--inner-spacing) var(--card-padding); font-size:14px;
    }
  }
  button:hover{transform:translateY(-1px); border-color:#4b5563}
  @media(hover:none){
    button:hover{transform:none;} /* Disable hover effects on touch devices */
  }
  .primary{background:rgba(34,197,94,.12); border-color:#14532d}
  .danger{background:rgba(239,68,68,.12); border-color:#7f1d1d}
  .info{background:rgba(59,130,246,.12); border-color:#1e40af;}
  .ghost{background:transparent}
  .badge{display:inline-block; font-size:12px; padding:2px var(--small-spacing); border-radius:999px; border:1px solid var(--border); color:var(--muted)}
  .ok{color:var(--brand-weak); border-color:#166534}
  .warn{color:#fde68a; border-color:#92400e}
  footer{color:var(--muted); font-size:12px; text-align:center; margin:var(--section-spacing) 0}
  @media(max-width:480px){
    footer{font-size:11px;margin:var(--inner-spacing) 0;padding:0 var(--inner-spacing);}
  }
  /* Button loading state */
  .button-loading {
    opacity: 0.7;
    pointer-events: none;
  }
  .button-loading::after {
    content: '';
    display: inline-block;
    width: 12px;
    height: 12px;
    margin-left: var(--small-spacing);
    border: 2px solid transparent;
    border-top: 2px solid currentColor;
    border-radius: 50%;
    animation: spin 1s linear infinite;
  }
  @keyframes spin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
  }
  @keyframes slideIn {
    from { transform: translateX(100%); opacity: 0; }
    to { transform: translateX(0); opacity: 1; }
  }
  
  /* Mobile-specific optimizations */
  @media(max-width: 480px) {
    /* Better spacing for mobile */
    section {
      margin-bottom: 16px !important;
    }
    
    /* Improve notification positioning for mobile */
    #notification {
      top: 10px !important;
      right: 10px !important;
      left: 10px !important;
      max-width: none !important;
    }
    
    /* Better progress bar visibility */
    .progress-container {
      height: 10px !important;
    }
    
    /* Improve badge readability */
    .badge {
      font-size: 11px !important;
      padding: 3px 8px !important;
    }
    
    /* Stack sections title better */
    h2[style*="display:flex"] {
      flex-wrap: wrap !important;
      gap: 8px !important;
    }
  }
  /* Gaya untuk slider */
  .setting-row{display:flex;align-items:center;gap:10px;margin:12px 0;}
  @media(max-width:480px){
    .setting-row{gap:8px;margin:10px 0;}
  }
  .setting-row label{flex-shrink:0}
  @media(max-width:480px){
    .setting-row label{font-size:13px;}
  }
  .setting-row input[type=range]{width:100%;}
  .setting-row span{font-weight:bold;color:var(--text);width:45px}
  @media(max-width:480px){
    .setting-row span{width:40px;font-size:13px;}
  }

  /* Progress bars untuk sensor */
  .sensor-grid{display:grid;grid-template-columns:1fr 1fr;gap:var(--grid-gap);margin-bottom:var(--section-spacing);}
  @media(max-width:480px){
    .sensor-grid{grid-template-columns:1fr;}
  }
  .sensor-card{
    background:rgba(255,255,255,0.05);
    border:1px solid rgba(255,255,255,0.1);
    border-radius:var(--border-radius);
    padding:var(--card-padding);
    text-align:center;
  }
  .sensor-card.channel1{border-left:4px solid var(--primary-blue);}
  .sensor-card.channel2{border-left:4px solid var(--primary-teal);}
  .sensor-title{display:flex;align-items:center;justify-content:center;gap:var(--small-spacing);margin-bottom:var(--small-spacing);}
  .sensor-title h3{margin:0;font-size:16px;font-weight:600;}
  @media(max-width:480px){
    .sensor-title h3{font-size:14px;}
  }
  .sensor-status{
    display:inline-block;
    padding:4px var(--small-spacing);
    border-radius:var(--small-spacing);
    font-size:11px;
    font-weight:600;
    text-transform:uppercase;
    background:rgba(255,122,90,0.2);
    color:#FF7A5A;
    border:1px solid rgba(255,122,90,0.3);
  }
  @media(max-width:480px){
    .sensor-status{font-size:10px;}
  }
  .sensor-value{
    font-size:48px;
    font-weight:700;
    margin:var(--inner-spacing) 0 var(--small-spacing);
    background:linear-gradient(135deg, var(--primary-blue), var(--primary-teal));
    -webkit-background-clip:text;
    -webkit-text-fill-color:transparent;
    background-clip:text;
  }
  @media(max-width:480px){
    .sensor-value{font-size:36px;}
  }
  .sensor-label{
    color:var(--muted);
    font-size:14px;
    margin-bottom:var(--inner-spacing);
  }
  @media(max-width:480px){
    .sensor-label{font-size:12px;}
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
    border-radius:var(--border-radius);
    padding:var(--card-padding);
    text-align:center;
    position:relative;
  }
  .weather-location{
    display:flex;
    align-items:center;
    justify-content:center;
    gap:var(--small-spacing);
    margin-bottom:var(--inner-spacing);
    color:var(--text);
    font-weight:600;
  }
  @media(max-width:480px){
    .weather-location{font-size:14px;}
  }
  .weather-temp{
    font-size:64px;
    font-weight:300;
    color:#F59E0B;
    margin:var(--small-spacing) 0;
  }
  @media(max-width:480px){
    .weather-temp{font-size:48px;}
  }
  .weather-desc{
    color:var(--muted);
    font-size:14px;
    margin-bottom:var(--card-padding);
  }
  @media(max-width:480px){
    .weather-desc{font-size:13px;}
  }
  .weather-stats{
    display:grid;
    grid-template-columns:repeat(3,1fr);
    gap:var(--inner-spacing);
    margin-top:var(--card-padding);
  }
  .weather-stat{
    text-align:center;
  }
  .weather-stat-icon{
    font-size:20px;
    margin-bottom:4px;
  }
  @media(max-width:480px){
    .weather-stat-icon{font-size:18px;margin-bottom:3px;}
  }
  .weather-stat-label{
    font-size:10px;
    color:var(--muted);
    text-transform:uppercase;
    margin-bottom:4px;
  }
  @media(max-width:480px){
    .weather-stat-label{font-size:9px;margin-bottom:3px;}
  }
  .weather-stat-value{
    font-weight:600;
    color:var(--text);
  }
  @media(max-width:480px){
    .weather-stat-value{font-size:14px;}
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
    <section style="margin-bottom:var(--section-spacing);">
      <h2 style="margin:0 0 var(--inner-spacing);color:var(--text);font-size:20px;display:flex;align-items:center;gap:var(--small-spacing);">
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
    <section style="margin-top:var(--section-spacing);">
      <div class="card">
        <h2 style="display:flex;align-items:center;gap:var(--small-spacing);">⚙️ Pengaturan Histeresis</h2>
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
      
      <div class="card" id="card1" style="margin-top:var(--section-spacing);">
        <h2 style="display:flex;align-items:center;gap:var(--small-spacing);color:#4F8FE8;">💧 Kontrol Sistem Irigasi Otomatis</h2>
        <div style="background:rgba(79,143,232,0.05);padding:var(--inner-spacing);border-radius:var(--border-radius);margin:var(--inner-spacing) 0;">
          <div style="display:flex;align-items:center;gap:var(--small-spacing);margin-bottom:var(--inner-spacing);">
            <span style="font-size:20px;">💧</span>
            <div>
              <div style="font-weight:600;font-size:16px;">Sistem Irigasi Utama</div>
              <div style="font-size:13px;color:var(--muted);">Relay 1 (Pompa) + Relay 2 (Valve) bekerja bersamaan</div>
            </div>
          </div>
          
          <div style="display:flex;align-items:center;gap:var(--inner-spacing);margin:var(--inner-spacing) 0;">
            <span style="font-size:16px;">⚡</span>
            <span style="font-size:14px;color:var(--muted);">Status Sistem Irigasi</span>
            <span style="flex:1;text-align:right;font-weight:600;color:#ef4444;" id="p1">MATI</span>
          </div>

          <div style="background:rgba(255,255,255,0.05);padding:var(--inner-spacing);border-radius:var(--small-spacing);margin:var(--inner-spacing) 0;">
            <div style="display:flex;align-items:center;gap:var(--inner-spacing);">
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

          <div style="display:grid;grid-template-columns:1fr 1fr;gap:var(--small-spacing);margin-top:var(--inner-spacing);">
            <button class="primary" style="background:#05C168;border-color:#059669;" onclick="manualWaterControl('on')">🟢 Manual ON</button>
            <button class="danger" style="background:#EF4444;border-color:#DC2626;" onclick="manualWaterControl('off')">🔴 Manual OFF</button>
          </div>
          <div style="display:grid;grid-template-columns:1fr;gap:var(--small-spacing);margin-top:var(--small-spacing);">
            <button class="info" style="background:#3B82F6;border-color:#1D4ED8;" onclick="toggleAutoMode()">🔄 Aktifkan Mode Otomatis</button>
          </div>
        </div>

        <div style="font-size:12px;color:var(--info);background:rgba(59,130,246,0.1);padding:var(--small-spacing);border-radius:var(--small-spacing);margin-top:var(--small-spacing);">
          ℹ️ <strong>Kontrol:</strong> Sistem terpadu Pompa (R1-NC) + Valve (R2-NO)<br>
          • <strong>Manual ON/OFF:</strong> Kontrol langsung sistem irigasi<br>
          • <strong>Mode Otomatis:</strong> Berdasarkan sensor kelembaban tanah
        </div>

        <!-- Mobile-specific responsive layout for control buttons -->
        <style>
          @media(max-width: 480px) {
            .card [style*="display:grid;grid-template-columns:1fr 1fr"] {
              grid-template-columns: 1fr !important;
              gap: 10px !important;
            }
            .card [style*="grid-template-columns:1fr"] {
              gap: 10px !important;
            }
          }
        </style>
      </div>
      
      <div class="card" style="margin-top:var(--section-spacing);">
        <h2 style="display:flex;align-items:center;gap:var(--small-spacing);color:#26D0CE;">🔧 Kontrol Relay </h2>
        
        <div style="display:grid;gap:var(--inner-spacing);">
          <div style="background:rgba(255,122,90,0.05);padding:var(--inner-spacing);border-radius:var(--border-radius);border-left:4px solid #FF7A5A;">
            <div style="display:flex;justify-content:space-between;align-items:center;margin-bottom:var(--small-spacing);flex-wrap:wrap;gap:var(--small-spacing);">
              <span style="font-weight:600;"><span style="background:#FF7A5A;color:white;padding:2px 6px;border-radius:4px;font-size:12px;">R3</span> Relay 3 (Lampu 1)</span>
              <span style="background:rgba(239,68,68,0.2);color:#EF4444;padding:4px var(--small-spacing);border-radius:var(--small-spacing);font-size:12px;font-weight:600;" id="l1">MATI</span>
            </div>
            <div style="display:grid;grid-template-columns:1fr 1fr;gap:var(--small-spacing);" class="mobile-stack">
              <button class="primary" style="background:#05C168;border-color:#059669;" onclick="action('/lamp1','on')">🟢 Hidupkan</button>
              <button class="danger" style="background:#EF4444;border-color:#DC2626;" onclick="action('/lamp1','off')">🔴 Matikan</button>
            </div>
          </div>

          <div style="background:rgba(38,208,206,0.05);padding:var(--inner-spacing);border-radius:var(--border-radius);border-left:4px solid #26D0CE;">
            <div style="display:flex;justify-content:space-between;align-items:center;margin-bottom:var(--small-spacing);flex-wrap:wrap;gap:var(--small-spacing);">
              <span style="font-weight:600;"><span style="background:#26D0CE;color:white;padding:2px 6px;border-radius:4px;font-size:12px;">R4</span> Relay 4 (Lampu 2)</span>
              <span style="background:rgba(239,68,68,0.2);color:#EF4444;padding:4px var(--small-spacing);border-radius:var(--small-spacing);font-size:12px;font-weight:600;" id="l2">MATI</span>
            </div>
            <div style="display:grid;grid-template-columns:1fr 1fr;gap:var(--small-spacing);" class="mobile-stack">
              <button class="primary" style="background:#05C168;border-color:#059669;" onclick="action('/lamp2','on')">🟢 Hidupkan</button>
              <button class="danger" style="background:#EF4444;border-color:#DC2626;" onclick="action('/lamp2','off')">🔴 Matikan</button>
            </div>
          </div>
        </div>

        <!-- Mobile responsive styles for better touch interaction -->
        <style>
          @media(max-width: 480px) {
            .mobile-stack {
              grid-template-columns: 1fr !important;
              gap: 10px !important;
            }
          }
        </style>

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
  const activeButton = event ? event.target : null;
  if (activeButton) {
    activeButton.classList.add('button-loading');
    activeButton.disabled = true;
  }
  
  try {
    const response = await fetch(path + '?state=' + state, {method:'POST'});
    if (!response.ok) throw new Error('Network error');
    setTimeout(refresh, 250);
  } catch (error) {
    console.error('Error:', error);
    showNotification('Gagal mengontrol perangkat', 'error');
  } finally {
    if (activeButton) {
      activeButton.classList.remove('button-loading');
      activeButton.disabled = false;
    }
  }
}

async function manualWaterControl(state){
  // Kontrol manual sistem irigasi - ON atau OFF
  try {
    const response = await fetch('/water?state=' + state, {
      method: 'POST',
      timeout: 5000
    });
    if (!response.ok) {
      throw new Error('Network response was not ok');
    }
    setTimeout(refresh, 250);
  } catch (error) {
    console.error('Error controlling water system:', error);
    showNotification('Gagal mengontrol sistem irigasi', 'error');
  }
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
  
  // Validasi di frontend
  if (parseInt(onVal) >= parseInt(offVal)) {
    showNotification('Error: Batas ON harus lebih kecil dari batas OFF', 'error');
    return;
  }
  
  btn.textContent = 'Menyimpan...';
  btn.disabled = true;
  
  try {
    const response = await fetch(`/settings?on=${onVal}&off=${offVal}`, {method:'POST'});
    if (!response.ok) {
      const errorText = await response.text();
      throw new Error(errorText);
    }
    btn.textContent = 'Tersimpan!';
    showNotification('Pengaturan berhasil disimpan', 'success');
    setTimeout(refresh, 500);
  } catch (error) {
    console.error('Error saving settings:', error);
    btn.textContent = 'Gagal!';
    showNotification(error.message || 'Gagal menyimpan pengaturan', 'error');
  } finally {
    btn.disabled = false;
    setTimeout(() => { btn.textContent = 'Simpan Pengaturan'; }, 3000);
  }
}

// Fungsi untuk menampilkan notifikasi
function showNotification(message, type = 'info') {
  // Hapus notifikasi sebelumnya
  const existingNotif = document.getElementById('notification');
  if (existingNotif) existingNotif.remove();
  
  const notification = document.createElement('div');
  notification.id = 'notification';
  notification.style.cssText = `
    position: fixed; top: 20px; right: 20px; z-index: 1000;
    padding: 12px 20px; border-radius: 8px; font-weight: 600;
    max-width: 300px; box-shadow: 0 4px 12px rgba(0,0,0,0.3);
    animation: slideIn 0.3s ease;
  `;
  
  if (type === 'error') {
    notification.style.background = '#EF4444';
    notification.style.color = 'white';
  } else if (type === 'success') {
    notification.style.background = '#05C168';
    notification.style.color = 'white';
  } else {
    notification.style.background = '#3B82F6';
    notification.style.color = 'white';
  }
  
  notification.textContent = message;
  document.body.appendChild(notification);
  
  // Auto remove setelah 4 detik
  setTimeout(() => {
    if (notification.parentNode) {
      notification.remove();
    }
  }, 4000);
}

refresh(); setInterval(refresh, 2000);
</script>
</body>
</html>
)HTML";