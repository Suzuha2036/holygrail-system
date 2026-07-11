#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

void initSensors();

void readSensors();

float getTemperature();

float getHumidity();

int getWaterLevel();

#endif