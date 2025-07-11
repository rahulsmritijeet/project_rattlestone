// 🌍 Project: Rattlestone - Environmental Monitor (Air + Temp + Humidity)
// 🧠 Devices Used: ESP32 + MQ135 + DHT11 + 16x2 I2C LCD + ESP32 Web Server

// --- 📦 Include Required Libraries ---
#include <Wire.h>                // For I2C communication (LCD)
#include <LiquidCrystal_I2C.h>  // For 16x2 I2C LCD display
#include <WiFi.h>               // For ESP32 Wi-Fi functions
#include <DHT.h>                // For DHT11 temperature & humidity sensor

// --- 🧾 Define Pins and Sensor Types ---
#define MQ135_PIN 35           // Analog pin for MQ135 air quality sensor (AOUT)
#define DHTPIN 4               // Digital pin for DHT11
#define DHTTYPE DHT11          // DHT11 sensor type

// --- 📺 LCD Setup (I2C address: 0x27, size: 16 columns x 2 rows) ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- 🌡️ DHT Sensor Setup ---
DHT dht(DHTPIN, DHTTYPE);

// --- 📶 Wi-Fi Credentials ---
const char* ssid = "YOUR_SSID";          // Replace with your Wi-Fi name
const char* password = "YOUR_PASSWORD";  // Replace with your Wi-Fi password

// --- 🌐 Setup Web Server on Port 80 ---
WiFiServer server(80);

// --- ⚙️ Setup Function ---
void setup() {
  Serial.begin(115200);       // Start Serial Monitor for debugging
  Wire.begin();               // Start I2C communication
  lcd.init();                 // Initialize LCD
  lcd.backlight();            // Turn on LCD backlight
  dht.begin();                // Initialize DHT11 sensor

  // --- Connect to Wi-Fi ---
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // --- Wi-Fi Connected ---
  Serial.println("\n✅ WiFi connected!");
  Serial.print("🔗 IP Address: ");
  Serial.println(WiFi.localIP());  // Shows the IP to access the dashboard
  server.begin();                 // Start web server
}

// --- 🔁 Loop Function ---
void loop() {
  // --- Read Sensor Data ---
  int airValue = analogRead(MQ135_PIN);       // Read air quality (higher = worse)
  float temp = dht.readTemperature();         // Read temperature (°C)
  float hum = dht.readHumidity();             // Read humidity (%)
  String statusText = (airValue > 300) ? "BAD" : "GOOD";  // Simple air quality status

  // --- Update LCD Display ---
  lcd.setCursor(0, 0);  // Top row
  lcd.print("A:"); lcd.print(airValue);
  lcd.print(" T:"); lcd.print(temp);

  lcd.setCursor(0, 1);  // Bottom row
  lcd.print("H:"); lcd.print(hum);
  lcd.print(" % "); lcd.print(statusText);

  // --- Handle Web Server Client ---
  WiFiClient client = server.available();  // Wait for client connection
  if (client) {
    String header = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c == '\n') break;  // End of HTTP request
      }
    }

    // --- Send HTTP Response ---
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

    // --- HTML Web Dashboard ---
    client.println("<html><head><meta http-equiv='refresh' content='2'></head><body style='font-family:Arial;'>");
    client.println("<h2>🌍 Project Rattlestone - Env Monitor</h2>");
    client.println("<p><b>Air Value:</b> " + String(airValue) + "</p>");
    client.println("<p><b>Status:</b> " + statusText + "</p>");
    client.println("<p><b>Temperature:</b> " + String(temp) + " °C</p>");
    client.println("<p><b>Humidity:</b> " + String(hum) + " %</p>");
    client.println("</body></html>");
    client.println();

    client.stop();  // Close the connection
  }

  delay(2000);  // Refresh every 2 seconds
}
