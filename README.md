# ESP32 Bluetooth Web Control

Proyek ini memungkinkan Anda mengontrol ESP32 melalui website menggunakan Bluetooth Low Energy (BLE). ESP32 akan mengirim data sensor simulasi (temperature dan humidity) dan dapat dikontrol untuk menyalakan/mematikan LED di GPIO 2.

## 🚀 Fitur

- **Bluetooth Low Energy (BLE)** - Komunikasi wireless dengan ESP32
- **Web Interface** - Interface yang modern dan responsif
- **Real-time Data** - Monitoring temperature dan humidity secara real-time
- **LED Control** - Toggle switch untuk mengontrol LED di GPIO 2
- **Cross-platform** - Bekerja di Chrome, Edge, dan Opera

## 📋 Requirements

### Hardware:
- ESP32 Development Board
- LED built-in di GPIO 2 (biasanya sudah ada di board ESP32)

### Software:
- PlatformIO IDE atau Arduino IDE
- Browser yang mendukung Web Bluetooth API (Chrome, Edge, Opera)

## 🔧 Instalasi dan Setup

### 1. Setup ESP32

1. Clone atau download proyek ini
2. Buka folder proyek di PlatformIO
3. Upload kode ke ESP32:
   ```bash
   pio run --target upload
   ```

### 2. Setup Website

1. Buka file `index.html` di browser yang mendukung Web Bluetooth
2. Pastikan Bluetooth di device Anda aktif

## 📱 Cara Penggunaan

### 1. Upload Kode ke ESP32
- Upload `main.cpp` ke ESP32 menggunakan PlatformIO
- Monitor Serial untuk melihat status: `pio device monitor`
- ESP32 akan mulai advertising dengan nama "ESP32-WebControl"

### 2. Buka Website
- Buka `index.html` di browser (Chrome/Edge/Opera)
- Klik tombol "Connect"
- Pilih device "ESP32-WebControl" dari daftar
- Tunggu hingga koneksi berhasil

### 3. Menggunakan Interface
- **Sensor Data**: Temperature dan humidity akan update otomatis setiap 3 detik
- **LED Control**: Klik toggle switch untuk menyalakan/mematikan LED
- **Connection Status**: Indicator di atas menunjukkan status koneksi
- **Log**: Panel bawah menampilkan log komunikasi

## 🛠 Struktur Proyek

```
esp-bluetooth-website/
├── src/
│   └── main.cpp              # Kode ESP32 (BLE Server)
├── platformio.ini            # Konfigurasi PlatformIO
├── index.html               # Website interface
└── README.md               # Dokumentasi ini
```

## 📊 Protokol Komunikasi

### ESP32 → Website (Notifications):
```json
{
  "type": "sensor",
  "temperature": 25.5,
  "humidity": 60.2,
  "led": false
}
```

### Website → ESP32 (Commands):
```json
// LED Control
{
  "type": "led",
  "action": "on"  // atau "off"
}

// Ping
{
  "type": "ping"
}
```

### ESP32 → Website (Responses):
```json
// LED Response
{
  "type": "led_response",
  "state": true
}

// Pong Response
{
  "type": "pong",
  "temperature": 25.5,
  "humidity": 60.2,
  "led": true
}
```

## 🔍 Troubleshooting

### ESP32 tidak terdeteksi:
- Pastikan ESP32 sudah di-upload dengan kode yang benar
- Restart ESP32 jika perlu
- Periksa Serial Monitor untuk error

### Website tidak bisa connect:
- Pastikan menggunakan browser yang mendukung (Chrome/Edge/Opera)
- Aktifkan Bluetooth di device
- Refresh halaman dan coba lagi
- Pastikan ESP32 dalam jangkauan

### LED tidak menyala:
- Periksa apakah ESP32 memiliki LED built-in di GPIO 2
- Monitor Serial untuk melihat command yang diterima
- Pastikan koneksi BLE stabil

## 🎯 Pengembangan Lebih Lanjut

Anda bisa mengembangkan proyek ini dengan:

1. **Sensor Real**: Ganti simulasi dengan sensor DHT22/BME280
2. **More Controls**: Tambah kontrol servo, relay, atau sensor lain
3. **Data Logging**: Simpan data sensor ke database
4. **Multiple Devices**: Support multiple ESP32 dalam satu interface
5. **Authentication**: Tambah password atau pairing security

## 📄 Lisensi

Proyek ini bersifat open source dan dapat digunakan untuk pembelajaran dan pengembangan.

## 🙋‍♂️ Support

Jika mengalami masalah atau punya pertanyaan, silakan check:
1. Serial Monitor ESP32 untuk debug
2. Browser Console untuk error JavaScript
3. Pastikan semua requirement sudah terpenuhi

Happy coding! 🚀
