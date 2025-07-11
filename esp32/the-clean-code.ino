// Project: Rattlestone - Env Monitor (Air + Temp + Humidity)
// Devices: ESP32 + MQ135 + DHT11 + LCD + Web Server

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <DHT.h>

#define MQ135_PIN 35
#define DHTPIN 4
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.init();
  lcd.backlight();
  dht.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
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

  WiFiClient client = server.available();
  if (client) {
    String header = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') break;
      }
    }

    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<html><head><meta http-equiv='refresh' content='2'></head><body style='font-family:Arial;'>");
    client.println("<h2>Project Rattlestone - Env Monitor</h2>");
    client.println("<p><b>Air Value:</b> " + String(airValue) + "</p>");
    client.println("<p><b>Status:</b> " + statusText + "</p>");
    client.println("<p><b>Temperature:</b> " + String(temp) + " °C</p>");
    client.println("<p><b>Humidity:</b> " + String(hum) + " %</p>");
    client.println("</body></html>");
    client.println();

    client.stop();
  }

  delay(2000);
}
