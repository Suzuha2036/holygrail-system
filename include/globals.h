#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>

//
// ===========================
// Sensor Data
// ===========================
//

extern float temperature;
extern float humidity;
extern int waterLevel;

//
// ===========================
// Relay States
// ===========================
//

extern bool fan1State;
extern bool fan2State;
extern bool pumpState;
extern bool solenoid1State;
extern bool solenoid2State;

//
// ===========================
// System Status
// ===========================
//

extern bool wifiConnected;
extern bool firebaseConnected;

extern bool manualOverride;
extern bool maintenanceMode;

//
// ===========================
// Device Status
// ===========================
//

extern String deviceStatus;
extern String firmwareVersion;
extern long uptime;

//
// ===========================
// Sensor Status
// ===========================
//

extern String sensorStatus;

//
// ===========================
// Thresholds
// (Loaded from Firebase later)
// ===========================
//

extern float maxTemperature;
extern float minHumidity;
extern int minimumWaterLevel;

extern int wateringDuration;
extern int fanDelay;

#endif