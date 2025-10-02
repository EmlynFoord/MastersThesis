#include <Wire.h>
#include <Adafruit_VEML7700.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1  // No reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_VEML7700 veml = Adafruit_VEML7700();

float LuxReading[15];
  char j;
  float LuxAverage;

void setup() {

  // Initialize VEML7700
  if (!veml.begin()) {
    while (1);
  }
  veml.setGain(VEML7700_GAIN_1_8);
  veml.setIntegrationTime(VEML7700_IT_800MS);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Default I2C address
        while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Light Sensor");
  display.display();
  delay(2000); // Splash screen delay
}

void loop() {
  
 for (j = 0; j < 15; j++) {
    LuxReading[j] = veml.readLux();
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Light: ");
    display.print(LuxReading[j]);
    display.print(" lx");
    display.display();
    delay(1000);
  }
  LuxAverage = 0;
  for (j = 0; j < 15; j++) {
    LuxAverage = LuxAverage + LuxReading[j];
  }
  LuxAverage = LuxAverage / 15;
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("15s Average: ");
  display.print(LuxAverage);
  display.println(" lx");
  display.display();
  delay(2000);
}