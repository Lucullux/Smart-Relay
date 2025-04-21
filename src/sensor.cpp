#include "sensor.h"

DHT dht(DHTPIN, DHTTYPE);  // Define the DHT sensor object

void setupSensor() {  
    Serial.println("Sensor initialized!");
    dht.begin();  // Initialize the DHT sensor
}

void readSensor() {
    float tempC = dht.readTemperature();
    float tempF = dht.readTemperature(true);
    float hum = dht.readHumidity();

    if (isnan(tempC) || isnan(tempF) || isnan(hum)) {
        Serial.println("Sensor read failed. Check wiring.");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(tempF);
    Serial.print(" °F | Humidity: ");
    Serial.print(hum);
    Serial.println(" %");

    delay(2000);
}