#include <Arduino.h>
#include <LittleFS.h>   // For LittleFS
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "USER";
const char* password = "PASS";

#define RELAY_PIN D1  // D1 is GPIO5 on ESP8266

ESP8266WebServer server(8080);

void listFiles() {
    Dir dir = LittleFS.openDir("/");
    while (dir.next()) {
        Serial.println("Found file: " + dir.fileName());
    }
}

// Read file from filesystem
String readFile(const char* path) {
    File file = LittleFS.open(path, "r");
    if (!file) return "File Not Found";
    String content = file.readString();
    file.close();
    return content;
}

// Serve HTML
void handleRoot() {
    server.send(200, "text/html", readFile("/index.html"));
}

void setup() {
    Serial.begin(921600);

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);  // Start with relay off (adjust depending on module logic)
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConnected! IP address: " + WiFi.localIP().toString());
    
    if (!LittleFS.begin()) {
        Serial.println("LittleFS Mount Failed!");
        return;
    } else {
        Serial.println("LittleFS Mounted Successfully.");
    }
    listFiles();
    
    server.on("/", handleRoot);

    server.on("/relay", []() {
        String state = server.arg("state");
        if (state == "on") {
            digitalWrite(RELAY_PIN, LOW);
            server.send(200, "text/plain", "Relay ON");
        } else if (state == "off") {
            digitalWrite(RELAY_PIN, HIGH);
            server.send(200, "text/plain", "Relay OFF");
        } else {
            server.send(400, "text/plain", "Invalid state");
        }
    });
    
    server.begin();

    Serial.println("HTTP server started. Visit http://" + WiFi.localIP().toString());

}

void loop() {
    server.handleClient();
}