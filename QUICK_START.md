# 📱 Quick Start Guide

## Langkah Cepat untuk Memulai

### 1. ⚡ Upload ke ESP32
1. Buka VS Code dengan PlatformIO extension
2. Buka folder proyek ini
3. Tekan `Ctrl+Shift+P` → ketik "PlatformIO: Upload"
4. Pilih port ESP32 Anda
5. Tunggu hingga upload selesai

### 2. 🌐 Buka Website
1. Klik kanan pada `index.html` → "Open with Live Server" (jika ada extension Live Server)
2. Atau double-click `index.html` untuk buka di browser
3. **PENTING**: Gunakan Chrome, Edge, atau Opera (Firefox tidak support Web Bluetooth)

### 3. 🔗 Koneksi
1. Pastikan Bluetooth aktif di komputer/smartphone
2. Klik tombol "Connect" di website
3. Pilih "ESP32-WebControl" dari daftar device
4. Tunggu hingga status berubah menjadi "Connected" ✅

### 4. 🎮 Mulai Mengontrol
- **Sensor Data**: Otomatis muncul setiap 3 detik
- **LED Control**: Klik toggle untuk nyalakan/matikan LED
- **Log**: Lihat komunikasi real-time di panel bawah

## 🚨 Jika Ada Masalah

### ESP32 tidak muncul di daftar:
```
1. Reset ESP32 dengan menekan tombol RST
2. Periksa Serial Monitor (Ctrl+Shift+P → "PlatformIO: Serial Monitor")
3. Pastikan muncul pesan "BLE device started, waiting for connections..."
```

### Website tidak bisa connect:
```
1. Refresh halaman (F5)
2. Pastikan Bluetooth aktif
3. Coba di browser yang berbeda (Chrome/Edge/Opera)
4. Clear browser cache jika perlu
```

### LED tidak nyala:
```
1. Periksa apakah ESP32 Anda memiliki LED built-in di GPIO 2
2. Beberapa board ESP32 menggunakan GPIO yang berbeda
3. Ganti LED_PIN di main.cpp jika perlu (misal ke GPIO 13 atau 5)
```

## 🎯 Tips Penggunaan

- **Jarak Optimal**: Maksimal 10 meter dari ESP32
- **Battery Life**: BLE sangat hemat daya
- **Multiple Connections**: Satu ESP32 bisa connect ke satu browser saja
- **Mobile Support**: Website juga bekerja di smartphone dengan Chrome

## 🔧 Customization

### Ganti Nama Device:
```cpp
// Di main.cpp, line ~74
BLEDevice::init("ESP32-WebControl");  // Ganti nama di sini
```

### Ganti Pin LED:
```cpp
// Di main.cpp, line ~9
const int LED_PIN = 2;  // Ganti ke pin yang Anda inginkan
```

### Ganti Interval Sensor:
```cpp
// Di main.cpp, line ~17
const unsigned long SENSOR_INTERVAL = 3000;  // dalam milliseconds
```

## 🏆 Selamat Mencoba!

Jika semuanya berjalan lancar, Anda akan melihat:
- ✅ Data temperature dan humidity yang berubah-ubah
- ✅ LED yang bisa dikontrol dari website
- ✅ Log komunikasi yang real-time
- ✅ Interface yang responsive dan modern

Happy coding! 🚀
