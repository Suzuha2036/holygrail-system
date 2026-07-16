#include "sensor_manager.h"
#include "pins.h"
#include "globals.h"

#include <DHT.h>

#define DHTTYPE DHT11

// =========================================
// DHT11 Object
// =========================================
DHT dht(DHT_PIN, DHTTYPE);

// =========================================
// Sensor Initialization
// =========================================
void initSensors()
{
    dht.begin();

    pinMode(WATER_SENSOR_PIN, INPUT);

    Serial.println("=================================");
    Serial.println("Initializing Sensors...");
    Serial.println("DHT11 Initialized");
    Serial.println("Water Sensor Initialized");
    Serial.println("=================================");
}

// =========================================
// Read All Sensors
// =========================================
void readSensors()
{
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    // Update only if readings are valid
    if (!isnan(temp))
    {
        temperature = temp;
    }

    if (!isnan(hum))
    {
        humidity = hum;
    }

    // Raw Analog Reading
    waterLevel = analogRead(WATER_SENSOR_PIN);

    // Sensor Status
    if (isnan(temp) || isnan(hum))
    {
        sensorStatus = "ERROR";
    }
    else
    {
        sensorStatus = "NORMAL";
    }

    // Uptime
    uptime = millis() / 1000;
}

// =========================================
// Getters
// =========================================
float getTemperature()
{
    return temperature;
}

float getHumidity()
{
    return humidity;
}

int getWaterLevel()
{
    return waterLevel;
}

// =========================================
// DHT Status
// =========================================
bool isDHTConnected()
{
    float t = dht.readTemperature();

    return !isnan(t);
}