#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>

// Initialize all sensors
void initSensors();

// Read every sensor
void readSensors();

// Individual getters
float getTemperature();
float getHumidity();
int getWaterLevel();

// Returns true if DHT11 is working
bool isDHTConnected();

#endif