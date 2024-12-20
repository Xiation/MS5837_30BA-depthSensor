#include <Wire.h>

// Define your I2C pins if using custom pins (for ESP32)
#define SCL_PIN 21
#define SDA_PIN 22

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);  // Initialize I2C with custom pins
  Serial.println("I2C Scanner starting...");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Scanning for I2C devices...");
  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found");
  } else {
    Serial.println("Scan complete");
  }

  delay(5000); // Wait 5 seconds before the next scan
}
