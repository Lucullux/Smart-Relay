#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 4       // Define the GPIO pin for DHT
#define DHTTYPE DHT11  // Define the sensor type

extern DHT dht;  // Declare the DHT object so it's shared across files

void setupSensor();
void readSensor();

#endif
