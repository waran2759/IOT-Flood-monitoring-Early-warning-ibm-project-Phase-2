#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Server details
const char* serverAddress = "your_server_address";
const String endpoint = "/api/data"; // API endpoint to send data

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Call function to send data
  sendDataToServer();
}

void loop() {
  // Nothing to do here
}

void sendDataToServer() {
  // Create HTTP client object
  HTTPClient http;

  // Your server URL with port and endpoint
  String serverURL = "http://" + String(serverAddress) + endpoint;

  // Add your data to send
  String data = "sensor_data=example_data";

  // Send HTTP POST request
  http.begin(serverURL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(data);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Server response: " + response);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  // Close connection
  http.end();
}
