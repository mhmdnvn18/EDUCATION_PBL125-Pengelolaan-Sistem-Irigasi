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
    display:flex; gap:12px; align-items:center; justify-content:space-between; flex-wrap:wrap;
  }
  .title{display:flex; gap:12px; align-items:center}
  h1{margin:0; font-size:20px}
  .subtitle{color:var(--muted); font-size:13px; margin-top:2px}
  .ip{font-size:13px; color:var(--brand-weak); padding:6px 10px; border:1px dashed var(--border); border-radius:10px}
  .grid{display:grid; gap:16px; grid-template-columns:repeat(auto-fit,minmax(260px,1fr))}
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
</style>
</head>
<body>
  <div class="container">
    <header>
      <div class="title">
        <h1>Smart Controller</h1>
        <div class="subtitle">Sistem Air & Lampu Manual</div>
      </div>
      <div class="ip" id="ipBox">IP: memuat…</div>
    </header>

    <section class="grid">
      <!-- KARTU BARU: PEMBACAAN SENSOR -->
      <div class="card">
        <h2>Pembacaan Sensor</h2>
        <div class="metric">Sensor 1: <b id="s_m1">-</b>%</div> <!-- Label (Air) dihapus -->
        <div class="metric">Sensor 2: <b id="s_m2">-</b>%</div>
        <div class="metric">Sensor 3: <b id="s_m3">-</b>%</div>
        <div class="metric">Sensor 4: <b id="s_m4">-</b>%</div>
      </div>
      
      <!-- KARTU PENGATURAN -->
      <div class="card">
        <h2>Pengaturan Histeresis</h2>
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
      
      <!-- KARTU KONTROL -->
      <div class="card" id="card1">
        <h2>Sistem Air (Pompa+Valve)</h2>
        <div class="metric">Status: <b id="p1">-</b></div>
        <div class="metric">Mode: <span class="badge ok" id="a1">AUTO</span></div>
        <div class="row">
          <button class="primary" onclick="action('/water','on')">Sistem ON</button>
          <button class="danger"  onclick="action('/water','off')">Sistem OFF</button>
        </div>
        <div class="row">
          <button class="ghost" onclick="action('/auto','on')">Mode AUTO</button>
          <button class="ghost" onclick="action('/auto','off')">Mode MANUAL</button>
        </div>
      </div>
      <div class="card" id="card3">
        <h2>Lampu 1</h2>
        <div class="metric">Status: <b id="l1">-</b></div>
        <div class="row">
          <button class="info" onclick="action('/lamp1','on')">NYALAKAN</button>
          <button class="danger"  onclick="action('/lamp1','off')">MATIKAN</button>
        </div>
      </div>
      <div class="card" id="card4">
        <h2>Lampu 2</h2>
        <div class="metric">Status: <b id="l2">-</b></div>
        <div class="row">
          <button class="info" onclick="action('/lamp2','on')">NYALAKAN</button>
          <button class="danger"  onclick="action('/lamp2','off')">MATIKAN</button>
        </div>
      </div>
    </section>
  </div>

<script>
async function refresh(){
  try{
    const r = await fetch('/status');
    const j = await r.json();
    
    // BARU: Update kartu pembacaan sensor
    document.getElementById('s_m1').textContent = (j.moist1 < 0) ? '--' : j.moist1.toFixed(1);
    document.getElementById('s_m2').textContent = (j.moist2 < 0) ? '--' : j.moist2.toFixed(1);
    document.getElementById('s_m3').textContent = (j.moist3 < 0) ? '--' : j.moist3.toFixed(1);
    document.getElementById('s_m4').textContent = (j.moist4 < 0) ? '--' : j.moist4.toFixed(1);

    // Update Card 1: Sistem Air (tanpa pembacaan sensor)
    const card1 = document.getElementById('card1');
    const p1 = document.getElementById('p1');
    const a1 = document.getElementById('a1');
    
    // ====== LOGIKA DIPERBARUI ======
    // Cek apakah SEMUA sensor tidak terhubung
    const noSensors = j.moist1 < 0 && j.moist2 < 0 && j.moist3 < 0 && j.moist4 < 0;

    if (noSensors) {
      p1.textContent = 'DISABLE';
      a1.textContent = 'DISABLE';
      card1.classList.add('disabled');
      card1.querySelectorAll('button').forEach(b => b.disabled = true);
    } else {
      p1.textContent = j.pump ? 'ON' : 'OFF';
      a1.textContent = j.auto ? 'AUTO' : 'MANUAL';
      a1.className = 'badge ' + (j.auto ? 'ok' : 'warn');
      card1.classList.remove('disabled');
      card1.querySelectorAll('button').forEach(b => b.disabled = false);
    }

    // Update Lampu 1 & 2 (tanpa pembacaan sensor)
    document.getElementById('l1').textContent = j.lamp1 ? 'ON' : 'OFF';
    document.getElementById('l2').textContent = j.lamp2 ? 'ON' : 'OFF';

    // Update slider pengaturan
    document.getElementById('onSlider').value = j.on_thresh;
    document.getElementById('onValue').textContent = j.on_thresh.toFixed(0) + '%';
    document.getElementById('offSlider').value = j.off_thresh;
    document.getElementById('offValue').textContent = j.off_thresh.toFixed(0) + '%';

    if (j.ip) document.getElementById('ipBox').textContent = 'IP: ' + j.ip;
  }catch(e){ console.log(e); }
}

async function action(path, state){
  await fetch(path + '?state=' + state, {method:'POST'});
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

