#include <Wire.h>
#include <Adafruit_VEML7700.h>

Adafruit_VEML7700 veml = Adafruit_VEML7700();

void setup() {
  Serial.begin(9600);
  // Wait for serial port to connect
  while (!Serial) { delay(10); }

  // Initialize the VEML7700 sensor
  if (!veml.begin()) {
    Serial.println("Failed to initialize VEML7700");

    while (1);
  }
  Serial.println("VEML7700 Found");
  
  // Configure the sensor
  veml.setGain(VEML7700_GAIN_1_8);
  veml.setIntegrationTime(VEML7700_IT_800MS);
}

void loop() {
  // Read ambient light
  float lux = veml.readLux();
  Serial.print("Ambient light: ");
  Serial.print(lux);
  Serial.println(" lx");
  
  delay(1000); // Wait for 1 second before next reading
}
