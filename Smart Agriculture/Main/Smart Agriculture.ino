#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define Relay D4
#define interval 1000
const char* ssid = "Galaxy F22E27E";
const char* password = "cpii2395";

// ThingSpeak Settings
const char* thingspeakHost = "api.thingspeak.com";
const char* writeAPIKey = "1KPITZUC7NJIH137"; // Replace with your ThingSpeak Write API Key

const int sensor_pin = A0;
WiFiServer server(80);

bool manual = false;

void setup() {
  Serial.begin(115200); // Use a common baud rate for ESP8266
  delay(100);
  
  // Setup relay and onboard LED
  pinMode(Relay, OUTPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(Relay, HIGH); // Ensure relay starts in the OFF position
  
  // Start WiFi connection
  Serial.println("\nConnecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Start server
  server.begin();
}

void loop() {
  float moisture_percentage = 100.00 - ((analogRead(sensor_pin) / 1023.00) * 100.00);
  Serial.print("Moisture Level: ");
  Serial.println(moisture_percentage);
  
  // Automatic control if not in manual mode
  if (!manual) {
    if (moisture_percentage < 7) {
      digitalWrite(Relay, LOW); // Turn relay ON
    } else {
      digitalWrite(Relay, HIGH); // Turn relay OFF
    }
  }

  // Send data to ThingSpeak
  sendToThingSpeak(moisture_percentage);

  // Handle manual control through HTTP
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        // Handle manual control commands
        if (currentLine.endsWith("GET /start-motor")) {
          Serial.println("Manual: Relay ON");
          digitalWrite(Relay, LOW);
          manual = true;
        } else if (currentLine.endsWith("GET /stop-motor")) {
          Serial.println("Manual: Relay OFF");
          digitalWrite(Relay, HIGH);
          manual = true;
        } else if (currentLine.endsWith("GET /auto-motor")) {
          Serial.println("Switched to AUTO mode");
          manual = false;
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected.");
  }

  delay(interval); // Delay for the interval
}

void sendToThingSpeak(float moisture) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(thingspeakHost, httpPort)) {
      Serial.println("Connection to ThingSpeak failed.");
      return;
    }

    // Construct the HTTP request
    String postStr = "api_key=" + String(writeAPIKey) + "&field1=" + String(moisture);
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: " + String(thingspeakHost) + "\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: " + String(postStr.length()) + "\n\n");
    client.print(postStr);

    // Wait for response
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println("ThingSpeak response timeout.");
        client.stop();
        return;
      }
    }

    // Read and print the response
    while (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }

    client.stop();
    Serial.println("Data sent to ThingSpeak.");
  } else {
    Serial.println("WiFi not connected, skipping ThingSpeak update.");
  }
}
