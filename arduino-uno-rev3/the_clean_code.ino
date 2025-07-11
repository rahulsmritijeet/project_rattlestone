#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define MQ135_PIN A0
#define DHTPIN 4
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  dht.begin();
}

void loop() {
  int airValue = analogRead(MQ135_PIN);
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  String statusText = (airValue > 300) ? "BAD" : "GOOD";

  lcd.setCursor(0, 0);
  lcd.print("A:"); lcd.print(airValue);
  lcd.print(" T:"); lcd.print(temp);

  lcd.setCursor(0, 1);
  lcd.print("H:"); lcd.print(hum);
  lcd.print(" % "); lcd.print(statusText);

  delay(2000);
}
