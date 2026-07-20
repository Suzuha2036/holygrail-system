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
// Actuator Status
// ===========================
//

extern String fan1Reason;
extern String fan2Reason;
extern String pumpReason;
extern String solenoid1Reason;
extern String solenoid2Reason;

//
// ===========================
// System Status
// ===========================
//

extern bool wifiConnected;
extern bool firebaseConnected;


extern bool manualOverride;
extern bool maintenanceMode;

extern bool automationEnabled;
extern String automationMode;

//
// ===========================
// Device Status
// ===========================
//

extern String deviceStatus;
extern String firmwareVersion;
extern unsigned long uptime;

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
extern int coolingLockoutDuration;

//
// ===========================
// Cooling System
// ===========================
//

extern bool coolingActive;
extern bool coolingLockout;

extern unsigned long coolingStartedAt;
extern unsigned long coolingLockoutUntil;

//
// ===========================
// Scheduler
// ===========================
//

extern bool scheduleRunning;
extern String currentSchedule;

//
// ===========================
// Current Process
// ===========================
//

extern String currentProcess;

#endif