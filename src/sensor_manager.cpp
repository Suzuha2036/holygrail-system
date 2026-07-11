#include "sensor_manager.h"
#include "pins.h"
#include "globals.h"

#include <Arduino.h>
#include <DHT.h>

#define DHTTYPE DHT11

DHT dht(DHT_PIN, DHTTYPE);

void initSensors()
{
    dht.begin();
}

void readSensors()
{
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (!isnan(temp))
        temperature = temp;

    if (!isnan(hum))
        humidity = hum;

    waterLevel = analogRead(WATER_SENSOR_PIN);
}

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