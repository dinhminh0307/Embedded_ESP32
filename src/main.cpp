#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "5A1-8"; // Replace with your WiFi network name
const char* password = "sky25a18";  // Replace with your WiFi password

const char* serverName = "https://yourserver.com/path"; // Replace with your server's URL

void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){ 
    HTTPClient http;   
    http.begin(serverName); // Specify request destination
    http.addHeader("Content-Type", "text/plain");  // Specify content-type header

    // Send the request
    int httpResponseCode = http.GET();  

    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error on sending GET: ");
      Serial.println(httpResponseCode);
    }

    // Free resources
    http.end(); 
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  // Send a request every 10000 milliseconds
  delay(10000);  
}
