#include <Wire.h>
#include <MS5837.h>

MS5837 sensor;

#define SCL_PIN 21
#define SDA_PIN 22

void setup() {
  Serial.begin(115200);
  Serial.println("starting");
  Wire.begin(SCL_PIN, SDA_PIN);

  // initializing pressure sensor
  while(!sensor.init()){
    Serial.println("Init failed");
    Serial.println("Are SDA/SCL connected correctly?");
    Serial.println("Blue Robotics Bar30: White=SDA, Green=SCL");
    Serial.println("\n\n\n");
    delay(1000);
    
    
  }
  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(997); // kg/m^3 (freshwater density)
}

void loop() {
  sensor.read();

  float calibrationOffset = 17.54;
  // sensor zero point is at -17 cm
  float readPressure = (sensor.pressure()) / 1000;
  float readDepth = ((sensor.depth()) * 100) + calibrationOffset;

  // pressure value
  Serial.print("pressure: ");
  Serial.print(readPressure);
  Serial.println(" bar");
  
  // depth value in cm
  Serial.print("Depth: ");
  Serial.print(readDepth);
  Serial.println(" cm");

  delay(500);
}
