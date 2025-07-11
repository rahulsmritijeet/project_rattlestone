// 🌍 Rattlestone - Offline Air & Weather Monitor (Arduino Uno Version)
// 📦 Components: MQ135 + DHT11 + 16x2 I2C LCD

#include <Wire.h>                 // I2C communication
#include <LiquidCrystal_I2C.h>    // LCD I2C library
#include <DHT.h>                  // DHT sensor library

// --- Pin & Sensor Setup ---
#define MQ135_PIN A0             // Analog input from MQ135
#define DHTPIN 4                 // DHT11 data pin
#define DHTTYPE DHT11            // Sensor type

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD I2C address and size
DHT dht(DHTPIN, DHTTYPE);          // DHT sensor object

void setup() {
  Serial.begin(9600);     // Start Serial Monitor (optional)
  Wire.begin();           // Begin I2C
  lcd.init();             // Initialize LCD
  lcd.backlight();        // Turn on backlight
  dht.begin();            // Start DHT sensor
}

void loop() {
  int airValue = analogRead(MQ135_PIN);      // Read MQ135 value
  float temp = dht.readTemperature();        // Get temperature
  float hum = dht.readHumidity();            // Get humidity
  String statusText = (airValue > 300) ? "BAD" : "GOOD";  // Basic air quality logic

  // Display values on LCD
  lcd.setCursor(0, 0);
  lcd.print("A:"); lcd.print(airValue);
  lcd.print(" T:"); lcd.print(temp);

  lcd.setCursor(0, 1);
  lcd.print("H:"); lcd.print(hum);
  lcd.print(" % "); lcd.print(statusText);

  delay(2000); // Update every 2 seconds
}
