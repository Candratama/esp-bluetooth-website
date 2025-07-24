#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <ArduinoJson.h>

// BLE UUIDs
#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-cba987654321"

// LED pin
const int LED_PIN = 2;

// Variables for sensor simulation
float temperature = 25.0;
float humidity = 60.0;
bool ledState = false;

// Timing variables
unsigned long lastSensorUpdate = 0;
const unsigned long SENSOR_INTERVAL = 3000; // Update every 3 seconds

// BLE variables
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

// Function to update sensor values
void updateSensorValues() {
  // Simulate temperature (20-35°C)
  temperature = 20.0 + random(0, 1500) / 100.0;
  
  // Simulate humidity (40-80%)
  humidity = 40.0 + random(0, 4000) / 100.0;
}

// Function to send sensor data
void sendSensorData() {
  if (!deviceConnected) return;
  
  // Create JSON object for sensor data
  JsonDocument doc;
  doc["type"] = "sensor";
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["led"] = ledState;
  
  String jsonString;
  serializeJson(doc, jsonString);
  
  pCharacteristic->setValue(jsonString.c_str());
  pCharacteristic->notify();
  
  Serial.println("Sent: " + jsonString);
}

// Function to handle Bluetooth commands
void handleBluetoothCommand(String command) {
  Serial.println("Processing: " + command);
  
  // Parse JSON command
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, command);
  
  if (error) {
    Serial.println("Failed to parse JSON: " + String(error.c_str()));
    return;
  }
  
  String type = doc["type"];
  
  if (type == "led") {
    String action = doc["action"];
    if (action == "on") {
      ledState = true;
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED turned ON");
    } else if (action == "off") {
      ledState = false;
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED turned OFF");
    }
    
    // Send confirmation
    JsonDocument response;
    response["type"] = "led_response";
    response["state"] = ledState;
    
    String responseString;
    serializeJson(response, responseString);
    
    if (deviceConnected) {
      pCharacteristic->setValue(responseString.c_str());
      pCharacteristic->notify();
      Serial.println("LED response sent: " + responseString);
    }
  }
  else if (type == "ping") {
    // Respond to ping with current status
    JsonDocument response;
    response["type"] = "pong";
    response["temperature"] = temperature;
    response["humidity"] = humidity;
    response["led"] = ledState;
    
    String responseString;
    serializeJson(response, responseString);
    
    if (deviceConnected) {
      pCharacteristic->setValue(responseString.c_str());
      pCharacteristic->notify();
      Serial.println("Pong response sent: " + responseString);
    }
  }
}

// BLE Server Callbacks
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Device connected");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("Device disconnected");
    }
};

// BLE Characteristic Callbacks
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        String receivedData = String(rxValue.c_str());
        Serial.println("Received: " + receivedData);
        handleBluetoothCommand(receivedData);
      }
    }
};

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize LED pin
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Initialize BLE
  BLEDevice::init("ESP32-WebControl");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);
  BLEDevice::startAdvertising();
  
  Serial.println("BLE device started, waiting for connections...");
  Serial.println("Device name: ESP32-WebControl");
  
  // Seed random number generator
  randomSeed(analogRead(0));
}

void loop() {
  // Handle BLE connection changes
  if (!deviceConnected && oldDeviceConnected) {
    delay(500);
    pServer->startAdvertising();
    Serial.println("Start advertising");
    oldDeviceConnected = deviceConnected;
  }
  
  if (deviceConnected && !oldDeviceConnected) {
    oldDeviceConnected = deviceConnected;
  }
  
  // Update and send sensor values periodically when connected
  if (deviceConnected && (millis() - lastSensorUpdate >= SENSOR_INTERVAL)) {
    updateSensorValues();
    sendSensorData();
    lastSensorUpdate = millis();
  }
  
  delay(100);
}