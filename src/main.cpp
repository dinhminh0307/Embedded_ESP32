#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
const char* ssid = "5A1-8";
const char* password = "sky25a18";
const int ledPin = 32; // Use your actual LED pin

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  WiFi.begin(ssid, password);

  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setInsecure();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(client, "https://esp-32-web-server-di6l-fn8vc7d6w-dinhminh0307s-projects.vercel.app/"); // Replace with your actual Vercel deployment URL
    int httpCode = http.GET();
    if (httpCode == 200) {
      String payload = http.getString();
      if (payload.indexOf("\"message\":\"done\"") != -1) {
        // Signal to blink received
        // digitalWrite(ledPin, HIGH);
        // delay(500);
        // digitalWrite(ledPin, LOW);
        Serial.println("Receive data");
      }
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end();
  }
  delay(50); // Poll every 10 seconds
}
